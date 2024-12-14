#include "object/objects.h"
#include <libft.h>
#include <math.h>
#include <math/la.h>
#include <render/collision.h>

// #include <stdio.h>	//
// Marwan's workaround for testing purposes
bool	plane_collide_function(struct s_ray ray, struct s_plane *plane,
		t_collision *coll, t_matrices *m)
{
	t_vec3	norm;
	float	determinant;
	float	distance;

	(void)m;
	norm = vec3_normalise(plane->normal);
	determinant = vec3_dot(ray.direction, norm);
	if (determinant == 0)
		return (false);
	distance = vec3_dot(vec3_sub(plane->base.position, ray.origin), norm)
		/ determinant;
	if (distance < 0)
		return (false);
	if (coll)
	{
		coll->dist = distance;
		coll->position = vec3_add(ray.origin, vec3_scalar_mul(ray.direction,
					distance));
		coll->normal = norm;
		coll->object = (struct s_object *)plane;
	}
	return (true);
}
