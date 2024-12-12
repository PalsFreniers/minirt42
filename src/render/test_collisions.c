/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by marwan            #+#    #+#             */
/*   Updated: 2024/12/12 18:52:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math/la.h"
#include <render/collision.h>

// Maybe put this in the object folder ?
int	next_object(struct s_object **objects, int i)
{	// To delete?
	if (i >= -1 && objects[i + 1])
		return (i + 1);
	return (-1);
}

bool	test_collision(struct s_mlx *mlx, struct s_object *object,
	struct s_ray ray, t_collision *collision)
{
	bool	is_collide;

	t_matrices mats = {0};
	(void)mlx;
	// mats.rotation = get_rotation_matrix((t_vec3){1, 0, 0});

	if (object->type == OBJ_SPHERE)
	{
		is_collide = sphere_collide_function(ray, (struct s_sphere*) object,
			collision, &mats);
	}
	else
		is_collide = false;
	return (is_collide);
}

// bool	lit_collision(struct s_mlx *mlx, t_collision collision)
// {
// 	t_ray	ray;
// 	size_t	i;

// 	ray.origin = collision.position;
// 	ray.direction = vec3_sub(mlx->scene.objects[0]->position, collision.position);
// 	i = 1;
// 	while (i < mlx->scene.len)
// 	{
// 		if (mlx->scene.objects[i] != collision.object)
// 			if (test_collision(mlx, mlx->scene.objects[i], ray, NULL))
// 				return (false);
// 		i++;
// 	}
// 	return (true);
// }
