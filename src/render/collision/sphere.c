#include <math.h>
#include <math/la.h>
#include <render/collision.h>

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
		struct s_vec3 *position, struct s_vec3 *normal)
{
	t_vec3		l;
	float		tca;
	const float	radius = sphere->diameter / 2;
	float		d2;
	float		thc;
	float		t0;
	float		t1;
	float		tmp;

	*position = vec3_zero();
	*normal = vec3_zero();
	l = vec3_sub(sphere->base.position, ray.origin);
	tca = vec3_dot(l, ray.direction);
	if (tca < 0)
		return (false);
	d2 = vec3_dot(l, l) - tca * tca;
	if (d2 > radius * radius)
		return (false);
	thc = sqrtf(radius * radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (false);
	}
	return (true);
}
