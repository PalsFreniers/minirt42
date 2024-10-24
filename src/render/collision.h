#ifndef COLLISION_H
# define COLLISION_H


# include <mlx/mmlx.h>

# include <math/ray.h>
# include <stdbool.h>

typedef struct s_collision
{
	struct s_vec3	position;
	struct s_vec3	normal;
	struct s_object	*object;
}					t_collision;

int		next_object(struct s_object **objects, int i);

int		test_collision(struct s_mlx *mlx, struct s_object *object,
			struct s_ray ray, t_collision *collision);

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
			struct s_vec3 *position, struct s_vec3 *normal);

#endif // COLLISION_H
