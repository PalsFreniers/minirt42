#ifndef RAY_H
# define RAY_H

# include <mlx/mmlx.h>
# include <object/objects.h>

typedef struct s_ray
{
	struct s_vec3	direction;
	struct s_vec3	origin;
}					t_ray;

struct s_ray		shoot_ray_from_camera(struct s_mlx *mlx, int x, int y);

#endif // RAY_H
