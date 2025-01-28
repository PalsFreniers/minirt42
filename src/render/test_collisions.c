/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by marwan            #+#    #+#             */
/*   Updated: 2025/01/28 06:26:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <render/collision.h>

bool	test_collision(struct s_mlx *mlx, struct s_object *object,
		struct s_ray *ray, t_collision *collision)
{
	bool	is_collide;

	is_collide = false;
	(void)mlx;
	if (!object)
		return (false);
	if (object->type == OBJ_SPHERE)
		is_collide = sphere_collide_function(ray, (struct s_sphere *)object,
				collision);
	else if (object->type == OBJ_PLANE)
		is_collide = plane_collide_function(ray, (struct s_plane *)object,
				collision);
	else if (object->type == OBJ_CYLINDER)
		is_collide = cylinder_collide_function(ray, (struct s_cylinder *)object,
				collision);
	else
		return (false);
	if (is_collide)
	{
		collision->object = object;
		collision->ray = *ray;
	}
	return (is_collide);
}
