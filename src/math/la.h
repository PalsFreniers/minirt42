#ifndef LA_H
# define LA_H

# include <math.h>


# define DEG2RAD 0.0174533f
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

# define MAT3_LEN 3

typedef struct s_mat3
{
	union
	{
		struct
		{
			float	m00;
			float	m01;
			float	m02;
			float	m10;
			float	m11;
			float	m12;
			float	m20;
			float	m21;
			float	m22;
		};
		float		m[9];
		// float		m[3][3];
	};
}					t_mat3;

t_vec3				vec3_new(float x, float y, float z);
t_vec3				vec3_new_from_one(float v);
t_vec3				vec3_zero(void);
t_vec3				vec3_scal_mul(t_vec3 a, float f);

t_vec3				vec3_add(t_vec3 a, t_vec3 b);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
t_vec3				vec3_mul(t_vec3 a, t_vec3 b);
t_vec3				vec3_div(t_vec3 a, t_vec3 b);
t_vec3				vec3_cross(t_vec3 a, t_vec3 b);
t_vec3				vec3_normalise(t_vec3 a);

float				vec3_distance(t_vec3 a, t_vec3 b);
float				vec3_lenght(t_vec3 a);
float				vec3_lenght_sq(t_vec3 a);
float				vec3_dot(t_vec3 a, t_vec3 b);
float				vec3_sum(t_vec3 a);

t_vec3				vec3_map_2pi(t_vec3 a);

t_mat3				mat3_zero(void);
t_mat3				mat3_identity(void);
t_mat3				mat3_scal_mul(t_mat3 a, float f);
t_mat3				mat3_inverse(t_mat3 a);

t_mat3				mat3_add(t_mat3 a, t_mat3 b);
t_mat3				mat3_mul(t_mat3 a, t_mat3 b);
t_vec3				mat3_apply(t_mat3 a, t_vec3 b);

t_mat3				rotation_matrix_x(float angle);
t_mat3				rotation_matrix_y(float angle);
t_mat3				rotation_matrix_z(float angle);

t_mat3				get_rotation_matrix(t_vec3 angle);

#endif // LA_H
