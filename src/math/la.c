#include <math.h>
#include <math/la.h>

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

t_vec3	vec3_normalise(t_vec3 a)
{
	return (vec3_div(a, vec3_new_from_one(vec3_lenght(a))));
}

float	vec3_distance_sq(t_vec3 a, t_vec3 b)
{
	t_vec3	tmp;

	tmp = vec3_sub(a, b);
	return (vec3_dot(tmp, tmp));
	return (0);
}

float	vec3_lenght(t_vec3 a)
{
	const t_vec3	tmp = vec3_mul(a, a);

	return (sqrtf(tmp.x + tmp.y + tmp.z));
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (vec3_sum(vec3_mul(a, b)));
}

float	vec3_sum(t_vec3 a)
{
	return (a.x + a.y + a.z);
}
