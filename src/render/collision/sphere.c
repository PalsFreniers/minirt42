#include <math.h>
#include <math/la.h>
#include <render/collision.h>

/**
 * float x = t - sqrtf(radius * radius - p * p);
 * if(x <= 0) return false;
 * return (true);
 * 
 * Même logique :
 * return (t * t <= (radius * radius - p * p));
*/

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
		struct s_vec3 *position, struct s_vec3 *normal)
{
	const float	radius = sphere->diameter / 2;

        *position = vec3_zero();
        *normal = vec3_zero();
        t_vec3 c = vec3_sub(sphere->base.position, ray.origin);
        float t = vec3_dot(c, ray.direction);
        float p = vec3_lenght(vec3_sub(c, vec3_mul(ray.direction, vec3_new_from_one(t))));
        if(p > radius)
                return false;
        float x = t - sqrtf(radius * radius - p * p);
        if(x <= 0) return false;
	return (true);
}
