#ifndef COLLISION_H
# define COLLISION_H


# include <mlx/mmlx.h>

# include <math/ray.h>
# include <stdbool.h>

typedef struct s_matrices
{
	t_mat3	rotation;
	t_vec3	translation;
}			t_matrices;

typedef struct s_collision
{
        float dist;
	struct s_vec3	position;
	struct s_vec3	normal;
	struct s_object	*object;
}					t_collision;

int		next_object(struct s_object **objects, int i);

int		test_collision(struct s_mlx *mlx, struct s_object *object,
			struct s_ray ray, t_collision *collision);

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
			t_collision *collision, t_matrices *mats);

#endif // COLLISION_H
