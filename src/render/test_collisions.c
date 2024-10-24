/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwan <marwan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by marwan            #+#    #+#             */
/*   Updated: 2024/10/24 13:18:00 by marwan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

// Maybe put this in the object folder ?
int	next_object(struct s_object **objects, int i)
{
	if (i >= -1 && objects[i + 1])
		return (i + 1);
	return (-1);
}

// is_front_side() would test if the collision occurs on the front side of the camera
bool	test_collision(struct s_mlx *mlx, struct s_object *object,
	struct s_ray ray, t_collision *collision)
{
	bool	is_collide;

	if (object->type == OBJ_SPHERE)
		is_collide = sphere_collide_function(ray, object,
			&collision->position, &collision->normal);
	// else if (object->type == OBJ_PLANE)
	// 	is_collide = plane_collide_function(ray, object,
	// 		&collision->position, &collision->normal);
	// else if (object->type == OBJ_CYLINDER)
	// 	is_collide = cylinder_collide_function(ray, object,
	// 		&collision->position, &collision->normal);
	else
		is_collide = false;
	// return (is_collide && is_front_side(mlx, collision->position));
	return (is_collide);
}