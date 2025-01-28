#include "la.h"
#include <math/la.h>
#include <object/objects.h>

t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){
		.x = x,
		.y = y,
		.z = z,
	});
}

t_vec3	vec3_new_from_one(float v)
{
	return (vec3_new(v, v, v));
}

t_vec3	vec3_zero(void)
{
	return ((t_vec3){0});
}

t_vec3	vec3_scal_mul(t_vec3 a, float f)
{
	return (vec3_new(f * a.x, f * a.y, f * a.z));
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x / b.x, a.y / b.y, a.z / b.z));
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x));
}

t_vec3	vec3_normalise(t_vec3 a)
{
        float len = vec3_lenght(a);
        if(len == 0)
                return vec3_new_from_one(0);
	return (vec3_div(a, vec3_new_from_one(len)));
}

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp = vec3_sub(a, b);
	return (vec3_lenght(tmp));
}

float	vec3_lenght(t_vec3 a)
{
	const t_vec3	tmp = vec3_mul(a, a);

	return (sqrtf(tmp.x + tmp.y + tmp.z));
}

float	vec3_lenght_sq(t_vec3 a)
{
	return (vec3_sum(vec3_mul(a, a)));
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (vec3_sum(vec3_mul(a, b)));
}

float	vec3_sum(t_vec3 a)
{
	return (a.x + a.y + a.z);
}

t_vec3	vec3_map_2pi(t_vec3 a)
{
	t_vec3	tmp;

	tmp = vec3_new_from_one(M_PI);
	return (vec3_add(vec3_mul(a, tmp), tmp));
}

t_vec3	map_vec3(t_vec3 vec, t_vec3 translation, t_mat3 transform)
{
	vec = vec3_sub(vec, translation);
	vec = mat3_apply(transform, vec);
	return (vec);
}

t_vec3	unmap_vec3(t_vec3 vec, t_vec3 translation, t_mat3 inverse_transform)
{
	vec = mat3_apply(inverse_transform, vec);
	vec = vec3_add(vec, translation);
	return (vec);
}

t_mat3	mat3_zero(void)
{
	return ((t_mat3){0});
}

t_mat3	mat3_identity(void)
{
	return ((t_mat3){
		.m00 = 1,
		.m01 = 0,
		.m02 = 0,
		.m10 = 0,
		.m11 = 1,
		.m12 = 0,
		.m20 = 0,
		.m21 = 0,
		.m22 = 1,
	});
}

t_mat3	mat3_scal_mul(t_mat3 a, float f)
{
	return ((t_mat3){
		.m00 = a.m00 * f,
		.m01 = a.m01 * f,
		.m02 = a.m02 * f,
		.m10 = a.m10 * f,
		.m11 = a.m11 * f,
		.m12 = a.m12 * f,
		.m20 = a.m20 * f,
		.m21 = a.m21 * f,
		.m22 = a.m22 * f,
	});
}

t_mat3	mat3_inverse(t_mat3 a)
{
	t_mat3	inverse;
	float	inv_determinant;

	inv_determinant = a.m00 * a.m11 * a.m22 + a.m01 * a.m12 * a.m20 + a.m02
		* a.m10 * a.m21 - a.m02 * a.m11 * a.m20 - a.m12 * a.m21 * a.m00 - a.m22
		* a.m01 * a.m10;
        print_vec3("", "mat[0]", vec3_new(a.m00, a.m01, a.m02));
        print_vec3("", "mat[1]", vec3_new(a.m10, a.m11, a.m12));
        print_vec3("", "mat[2]", vec3_new(a.m20, a.m21, a.m22));
	if (inv_determinant != 0)
		inv_determinant = 1 / inv_determinant;
	inverse.m00 = (a.m11 * a.m22 - a.m12 * a.m21) * inv_determinant;
	inverse.m01 = (a.m02 * a.m21 - a.m01 * a.m22) * inv_determinant;
	inverse.m02 = (a.m01 * a.m12 - a.m02 * a.m11) * inv_determinant;
	inverse.m10 = (a.m12 * a.m20 - a.m10 * a.m22) * inv_determinant;
	inverse.m11 = (a.m00 * a.m22 - a.m02 * a.m20) * inv_determinant;
	inverse.m12 = (a.m02 * a.m10 - a.m00 * a.m12) * inv_determinant;
	inverse.m20 = (a.m10 * a.m21 - a.m11 * a.m20) * inv_determinant;
	inverse.m21 = (a.m01 * a.m20 - a.m00 * a.m21) * inv_determinant;
	inverse.m22 = (a.m00 * a.m11 - a.m01 * a.m10) * inv_determinant;
	return (inverse);
}

t_mat3	mat3_add(t_mat3 a, t_mat3 b)
{
	return ((t_mat3){
		.m00 = a.m00 + b.m00,
		.m01 = a.m01 + b.m01,
		.m02 = a.m02 + b.m02,
		.m10 = a.m10 + b.m10,
		.m11 = a.m11 + b.m11,
		.m12 = a.m12 + b.m12,
		.m20 = a.m20 + b.m20,
		.m21 = a.m21 + b.m21,
		.m22 = a.m22 + b.m22,
	});
}

t_mat3	mat3_mul(t_mat3 a, t_mat3 b)
{
	return ((t_mat3){
		.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
		.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
		.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,
		.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
		.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
		.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,
		.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
		.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
		.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22,
	});
}

t_vec3	mat3_apply(t_mat3 a, t_vec3 b)
{
	t_vec3 test = ((t_vec3){
		.x = a.m00 * b.x + a.m01 * b.y + a.m02 * b.z,
		.y = a.m10 * b.x + a.m11 * b.y + a.m12 * b.z,
		.z = a.m20 * b.x + a.m21 * b.y + a.m22 * b.z,
	});
        return test;
}

t_mat3	rotation_matrix_x(float angle)
{
	return ((t_mat3){
		.m00 = 1,
		.m01 = 0,
		.m02 = 0,
		.m10 = 0,
		.m11 = cosf(angle),
		.m12 = -sinf(angle),
		.m20 = 0,
		.m21 = sinf(angle),
		.m22 = cosf(angle),
	});
}

t_mat3	rotation_matrix_y(float angle)
{
	return ((t_mat3){
		.m00 = cosf(angle),
		.m01 = 0,
		.m02 = sinf(angle),
		.m10 = 0,
		.m11 = 1,
		.m12 = 0,
		.m20 = -sinf(angle),
		.m21 = 0,
		.m22 = cosf(angle),
	});
}

t_mat3	rotation_matrix_z(float angle)
{
	return ((t_mat3){
		.m00 = cosf(angle),
		.m01 = -sinf(angle),
		.m02 = 0,
		.m10 = sinf(angle),
		.m11 = cosf(angle),
		.m12 = 0,
		.m20 = 0,
		.m21 = 0,
		.m22 = 1,
	});
}

t_mat3	get_rotation_matrix(t_vec3 angle)
{
	t_mat3	ret;

	ret = mat3_identity();
	ret = mat3_mul(ret, rotation_matrix_z(angle.z));
	ret = mat3_mul(ret, rotation_matrix_y(angle.y));
	ret = mat3_mul(ret, rotation_matrix_x(angle.x));
	return (ret);
}
