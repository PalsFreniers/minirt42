/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:55:14 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:03:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>

static size_t	object_size(struct s_object *object)
{
	if (object->type == OBJ_LIGHT)
	{
		return (sizeof(struct s_light));
	}
	else if (object->type == OBJ_SPHERE)
	{
		return (sizeof(struct s_sphere));
	}
	else if (object->type == OBJ_PLANE)
	{
		return (sizeof(struct s_plane));
	}
	else if (object->type == OBJ_CYLINDER)
	{
		return (sizeof(struct s_cylinder));
	}
	else
	{
		return (0);
	}
}

bool	dup_objects(struct s_scene *scene)
{
	size_t	obj_size;
	size_t	i;
	size_t	x;

	if (!scene->map_objects)
		return (false);
	i = 0;
	while (i < scene->len)
	{
		obj_size = object_size(scene->objects[i]);
		if (!scene->map_objects[i])
		{
			x = 0;
			while (x < i)
				ft_free("p", scene->map_objects[x++]);
			ft_free("p", scene->map_objects);
			return (false);
		}
		ft_memcpy(scene->map_objects[i], scene->objects[i], obj_size);
		i++;
	}
	return (true);
}

void	map_object(struct s_object *target, struct s_object *src,
		t_vec3 translation, t_mat3 transform)
{
	target->position = map_vec3(src->position, translation, transform);
	if (src->type == OBJ_PLANE)
	{
		((struct s_plane *)target)->normal = mat3_apply(transform,
				((struct s_plane *)src)->normal);
	}
	else if (src->type == OBJ_CYLINDER)
	{
		((struct s_cylinder *)target)->axis = mat3_apply(transform,
				((struct s_cylinder *)src)->axis);
	}
}
