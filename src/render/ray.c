/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:58:01 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/29 18:37:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

struct s_ray	shoot_ray(int x, int y, float screen_to_cam_factor)
{
	struct s_ray	ray;

	ray.origin = vec3_zero();
	ray.direction.x = (x - (float)WIN_WIDTH / 2) * screen_to_cam_factor;
	ray.direction.y = (y - (float)WIN_HEIGHT / 2) * screen_to_cam_factor;
	ray.direction.z = 1;
	ray.direction = vec3_normalise(ray.direction);
	return (ray);
}
