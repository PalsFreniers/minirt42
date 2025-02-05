/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:55:14 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 02:53:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>

static size_t	object_size(struct s_object *object)
{
	switch (object->type)
	{
	case OBJ_LIGHT:		return (sizeof (struct s_light));
	case OBJ_SPHERE:	return (sizeof (struct s_sphere));
	case OBJ_PLANE:		return (sizeof (struct s_plane));
	case OBJ_CYLINDER:	return (sizeof (struct s_cylinder));
	default:			return (0);
	}
}

bool	dup_objects(struct s_scene *scene)
{
	if (!scene->map_objects)
		return (false);
	for (size_t i = 0; i < scene->len; i++)
	{
		size_t	obj_size = object_size(scene->objects[i]);

		if (!scene->map_objects[i])
		{
			for (size_t x = 0; x < i; x++)
				ft_free("p", scene->map_objects[x]);
			ft_free("p", scene->map_objects);
			return (false);
		}
		ft_memcpy(scene->map_objects[i], scene->objects[i], obj_size);
	}
	return (true);
}

void	map_object(struct s_object *target, struct s_object *src, t_vec3 translation, t_mat3 transform)
{
	size_t	obj_size;

	if (target->type != src->type)
		return ;
	obj_size = object_size(target);
	ft_memcpy(target, src, obj_size);
	target->position = map_vec3(src->position, translation, transform);
	if (src->type == OBJ_PLANE)
		((struct s_plane *)target)->normal
			= mat3_apply(transform, vec3_normalise(((struct s_plane *)src)->normal));
	else if (src->type == OBJ_CYLINDER)
		((struct s_cylinder *)target)->axis
			= mat3_apply(transform, vec3_normalise(((struct s_cylinder *)src)->axis));
}
