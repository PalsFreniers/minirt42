/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:02:23 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 04:09:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/objects.h"
#include <libft.h>
#include <scene/scene.h>

static bool		scene_grow(struct s_scene *scene)
{
	if (scene->capacity == 0)
	{
		scene->objects = ft_calloc(1, sizeof(struct s_object *));
		scene->map_objects = ft_calloc(1, sizeof(struct s_object *));
		if (!scene->objects || !scene->map_objects)
			return (false);
		scene->capacity = 1;
		return (true);
	}
	scene->capacity *= 2;
	scene->objects = (void *)ft_realloc(
			(char *)scene->objects,
			(scene->capacity / 2) * sizeof(struct s_object *),
			scene->capacity * sizeof(struct s_object *));
	scene->map_objects = (void *)ft_realloc(
			(char *)scene->map_objects,
			(scene->capacity / 2) * sizeof(struct s_object *),
			scene->capacity * sizeof(struct s_object *));
	if (!scene->objects || !scene->map_objects)
	{
		scene->capacity = 0;
		return (false);
	}
	return (true);
}

struct s_object	*scene_dup_zero(struct s_object *o)
{
	switch (o->type)
	{
	case OBJ_LIGHT:		return (ft_calloc(1, sizeof(struct s_light)));
	case OBJ_SPHERE:	return (ft_calloc(1, sizeof(struct s_sphere)));
	case OBJ_PLANE:		return (ft_calloc(1, sizeof(struct s_plane)));
	case OBJ_CYLINDER:	return (ft_calloc(1, sizeof(struct s_cylinder)));
	default:			return (NULL);
	}
}

bool	scene_append(struct s_scene *scene, struct s_object *obj)
{
	if (scene->capacity <= scene->len && !scene_grow(scene))
		return (false);
	scene->objects[scene->len] = obj;
	scene->map_objects[scene->len] = scene_dup_zero(obj);
	scene->map_objects[scene->len]->type = scene->objects[scene->len]->type;
	scene->len++;
	return (true);
}
