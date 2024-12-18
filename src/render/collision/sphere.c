#include "object/objects.h"
#include <libft.h>
#include <math.h>
#include <math/la.h>
#include <render/collision.h>

float	ft_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

// #include <stdio.h>	//
// Marwan's workaround for testing purposes
bool	sphere_collide_function(struct s_ray *ray, struct s_sphere *sphere,
		t_collision *coll)
{
	const float	radius = sphere->diameter / 2;
	float		determinant;
	t_vec3		ray_to_sphere;
	float		rtSp_norm_squarred;
	float		ray_dot_rtSp;

	ray_to_sphere = vec3_sub(ray->origin, sphere->base.position);
	ray_dot_rtSp = vec3_dot(ray->direction, ray_to_sphere);
	rtSp_norm_squarred = vec3_lenght_sq(ray_to_sphere);
	determinant = ray_dot_rtSp * ray_dot_rtSp - (rtSp_norm_squarred - radius * radius);
	if (determinant < 0)
		return (false);
	if (coll)
	{
		coll->dist = -(ray_dot_rtSp) - sqrtf(determinant);
		// if (coll->dist < 0.0f)
		// 	coll->dist = -(ray_dot_rtSp) + sqrtf(determinant);
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction, coll->dist));
		coll->normal = vec3_normalise(vec3_sub(coll->position, sphere->base.position));
	}
	return (true);
}

// // Tidian's work
// bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
// 		t_collision *coll, t_matrices *m)
// {
// 	const float	radius = sphere->diameter / 2;
// 	t_vec3		position;
// 	float		t;
// 	t_vec3		p;
// 	float		y;
// 	float		x;
// 
// 	(void)m;
// 	ft_bzero(coll, sizeof(t_collision));
// 	// position = mat3_apply(m->rotation, sphere->base.position);
// 	(void) m;
// 	position = sphere->base.position;
// 	t = vec3_dot(vec3_sub(position, ray.origin), ray.direction);
// 	p = vec3_add(ray.origin, vec3_mul(ray.direction, vec3_new_from_one(t)));
// 	y = vec3_lenght(vec3_sub(position, p));
// 	if (ft_abs(y) > ft_abs(radius))
// 		return (false);
// 	x = sqrtf(radius * radius - y * y);
// 	coll->dist = t - x;
// 	coll->object = (struct s_object *)sphere;
// 	coll->position = vec3_add(ray.origin, vec3_mul(ray.direction,
// 			vec3_new_from_one(coll->dist)));
// 	coll->normal = vec3_normalise(vec3_sub(coll->position,
// 			sphere->base.position));
// 	return (true);
// }
