/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_collisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:33 by marwan            #+#    #+#             */
/*   Updated: 2025/02/05 02:49:39 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	test_collision(struct s_object *object, struct s_ray *ray, t_collision *collision)
{
	bool	colliding;

	if (!object)
		return (false);
	switch (object->type)
	{
	case OBJ_SPHERE:
		colliding = sphere_collide(ray, (struct s_sphere *) object, collision);
		break;
	case OBJ_PLANE:
		colliding = plane_collide(ray, (struct s_plane *) object, collision);
		break;
	case OBJ_CYLINDER:
		colliding = cylinder_collide(ray, (struct s_cylinder *) object, collision);
		break;
	default:
		return (false);
	}
	if (colliding)
	{
		collision->object = object;
		collision->ray = *ray;
	}
	return (colliding);
}
