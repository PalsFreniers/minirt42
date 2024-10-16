#ifndef LA_H
#define LA_H

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef float t_mat4[4][4];

t_vec3 vec3_new(float x, float y, float z);
t_vec3 vec3_new_from_one(float v);

t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, t_vec3 b);
t_vec3 vec3_div(t_vec3 a, t_vec3 b);

float vec3_distance(t_vec3 a, t_vec3 b);
float vec3_dot(t_vec3 a, t_vec3 b);
float vec3_sum(t_vec3 a);

#endif // LA_H
