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

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
		t_collision *coll, t_matrices *m)
{
	const float	radius = sphere->diameter / 2;
	t_vec3		position;
	float		t;
	t_vec3		p;
	float		y;
	float		x;

	(void)m;
	position = mat3_apply(m->rotation, sphere->base.position);
	ft_bzero(coll, sizeof(t_collision));
	t = vec3_dot(vec3_sub(position, ray.origin), ray.direction);
	p = vec3_add(ray.origin, vec3_mul(ray.direction, vec3_new_from_one(t)));
	y = vec3_lenght(vec3_sub(position, p));
	if (ft_abs(y) > ft_abs(radius))
		return (false);
	x = sqrtf(radius * radius - y * y);
	coll->dist = t - x;
	return (true);
}
