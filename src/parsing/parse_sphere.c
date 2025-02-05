/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:25:50 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 01:18:55 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <logger/logger.h>
#include <parsing/parse.h>

bool	parse_sphere(struct s_string *parts, size_t count, struct s_scene *scene)
{
	struct s_sphere		*sphere;

	if (count != 4)
	{
		logger_error("unable to parse sphere");
		return (false);
	}
	sphere = (struct s_sphere *)object_new(sizeof (*sphere), OBJ_SPHERE);
	if (!scene_append(scene, (struct s_object *)sphere))
		return (false);
	if (!parse_position(parts[1], &(sphere->base.position)))
		return (false);
	if (!parse_float(parts[2], &(sphere->diameter)))
		return (false);
	if (sphere->diameter <= 0)
	{
		logger_error("spheres diameter can't be zero or negative");
		return (false);
	}
	if (!parse_color(parts[3], &(sphere->base.color)))
		return (false);
	return (true);
}
