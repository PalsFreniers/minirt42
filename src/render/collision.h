#ifndef COLLISION_H
# define COLLISION_H

# include <math/ray.h>
# include <stdbool.h>

bool	sphere_collide_function(struct s_ray ray, struct s_sphere *sphere,
			struct s_vec3 position, struct s_vec3 normal);

#endif // COLLISION_H
