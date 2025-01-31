/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:23:52 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/31 17:24:35 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene/scene.h"
#include "strings/dstring.h"
#include <logger/logger.h>
#include <math.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <ui/window.h>

void	camera_create_transform(struct s_camera *camera)
{
	t_vec3	t_x;
	t_vec3	t_y;

	t_x = vec3_normalise(vec3_cross(vec3_normalise(vec3_new(camera->direction.x,
						camera->direction.y, 0)), vec3_new(0, 0, 1)));
	t_y = vec3_normalise(vec3_cross(vec3_normalise(camera->direction), t_x));
	camera->transform.m00 = t_x.x;
	camera->transform.m01 = t_x.y;
	camera->transform.m02 = t_x.z;
	camera->transform.m10 = t_y.x;
	camera->transform.m11 = t_y.y;
	camera->transform.m12 = t_y.z;
	camera->transform.m20 = camera->direction.x;
	camera->transform.m21 = camera->direction.y;
	camera->transform.m22 = camera->direction.z;
	camera->inverse_transform = mat3_inverse(camera->transform);
}

static bool	parse_camera_impl(struct s_camera *camera, struct s_string *parts)
{
	if (!parse_position(parts[1], &(camera->position)))
		return (false);
	if (!parse_ranged_vector(parts[2], &(camera->direction), 1, -1))
		return (false);
	if (!parse_range(parts[3], &(camera->fov), 180, 0))
		return (false);
	if (camera->direction.x == 0)
		camera->direction.x += 0.1;
	if (camera->direction.y == 0)
		camera->direction.y -= 0.1;
	camera->direction = vec3_normalise(camera->direction);
	camera_create_transform(camera);
	camera->screen_to_cam_factor = (2 * sinf(camera->fov * DEG2RAD / 2)) / WIN_WIDTH;
	return (true);
}

bool	parse_camera(struct s_string *parts, size_t count,
		struct s_camera *camera)
{
	if (camera->exist)
	{
		logger_error("only one camera is able to exist at one time");
		return (false);
	}
	ft_bzero(camera, sizeof(struct s_camera));
	if (count != 4)
	{
		logger_error("unable to parse camera");
		return (false);
	}
	if (!parse_camera_impl(camera, parts))
		return (false);
	camera->exist = true;
	return (true);
}
