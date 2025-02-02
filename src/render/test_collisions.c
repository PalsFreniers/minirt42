/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by marwan            #+#    #+#             */
/*   Updated: 2025/01/29 18:27:57 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	test_collision(struct s_object *object, struct s_ray *ray,
		t_collision *collision)
{
	bool	colliding;

	if (!object)
		return (false);
	if (object->type == OBJ_SPHERE)
		colliding = sphere_collide(ray, (struct s_sphere *) object, collision);
	else if (object->type == OBJ_PLANE)
		colliding = plane_collide(ray, (struct s_plane *) object, collision);
	else if (object->type == OBJ_CYLINDER)
		colliding = cylinder_collide(ray, (struct s_cylinder *) object,
				collision);
	else
		return (false);
	if (colliding)
	{
		collision->object = object;
		collision->ray = *ray;
	}
	return (colliding);
}
