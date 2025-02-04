/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:25:26 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 17:47:32 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>
#include <object/objects.h>
#include <parsing/parse.h>

bool	parse_plane(struct s_string *parts, size_t count, struct s_scene *scene)
{
	struct s_plane	*plane;

	if (count != 4)
	{
		logger_error("unable to parse plane");
		return (false);
	}
	plane = (void *)object_new(sizeof(struct s_plane), OBJ_PLANE);
	if (!scene_append(scene, (struct s_object *)plane))
		return (false);
	if (!parse_position(parts[1], &(plane->base.position)))
		return (false);
	if (!parse_ranged_vector(parts[2], &(plane->normal), 1, -1))
		return (false);
	if (!parse_color(parts[3], &(plane->base.color)))
		return (false);
	plane->normal.z += 0.00001f;
	return (true);
}
