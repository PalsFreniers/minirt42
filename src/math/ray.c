/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:58:01 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:58:32 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

struct s_ray	shoot_ray_from_camera(struct s_mlx *mlx, int x, int y)
{
	struct s_ray	ray;

	ray.origin = vec3_zero();
	ray.direction.x = (x - (float)WIN_WIDTH / 2)
		* mlx->scene.camera.screen_to_camera_factor;
	ray.direction.y = (y - (float)WIN_HEIGHT / 2)
		* mlx->scene.camera.screen_to_camera_factor;
	ray.direction.z = 1;
	ray.direction = vec3_normalise(ray.direction);
	return (ray);
}
