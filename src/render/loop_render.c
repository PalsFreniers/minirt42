/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2025/01/25 19:45:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "libft.h"
#include "mlx.h"
#include "render.h"
#include <math.h>
#include <math/la.h>
#include <minirt.h>
#include <mlx/hooks.h>
#include <ui/window.h>

/**
 * 	loop through x, y:
 * 		shoot_ray_from_camera
 * 		get_collision			--> gets the nearest collision
 *
 * 	shoot_ray_from_camera:
 * 		(FOV, x, y) --> ray
 * 		ray --> rotate from camera referential to world referential
 *
 * 	get_collision:
 * 		loop through objects:
 * 			if check_collision and nearest and valid:
 * 				collision = tmp_collision
 */

// Some constants to know here...
//
// tan (FOV / 2) = (CAMERA_X / 2) / CAMERA_Z = CAMERA_X / (2 * CAMERA_Z)
// CAMERA_X = 2 * CAMERA_Z * arctan(FOV / 2)
//
// ray.x	= (pix.x / SCREEN_X) * CAMERA_X
// 			= pix.x * 2 * CAMERA_Z * arctan(FOV / 2) / SCREEN_X
//
// CAMERA_X / SCREEN_X = CAMERA_Y / SCREEN_Y
//
// ray.y	= (pix.y / SCREEN_Y) * CAMERA_Y
// 			= pix.y * CAMERA_X / SCREEN_X
// 			= pix.y * 2 * CAMERA_Z * arctan(FOV / 2) / SCREEN_X
//
// We should save that as a camera constant:
// 		screen_to_camera_factor = 2 * CAMERA_Z * arctan(FOV / 2) / SCREEN_X
//
// look at src/math/la.h to know all the matrix and vector operations
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

void	get_collision(struct s_mlx *mlx, struct s_ray *ray,
		t_collision *collision)
{
	t_collision	tmp_collision;
	size_t		i_obj;

	collision->object = NULL;
	collision->dist = INFINITY;
	i_obj = 0;
	while (i_obj < mlx->scene.len)
	{
		if (test_collision(mlx, mlx->scene.map_objects[i_obj], ray,
				&tmp_collision))
			if (tmp_collision.dist > 0 && tmp_collision.dist < collision->dist)
				*collision = tmp_collision;
		i_obj++;
	}
}

static bool	is_float_on_grad(float f, float step, float precision)	// DEBUG
{
	float	mod;

	if (f < step && f > -step)
		return (f < 2 * precision && f > -2 * precision);
	mod = fmod(f, step);
	return (mod < precision || mod > (step - precision));
}

static mlx_color	draw_graduation(struct s_mlx *mlx, t_collision *collision,
		float step, float precision)											// DEBUG
{
	mlx_color	color;
	t_vec3		global_position;
	bool		x_bool;
	bool		y_bool;
	bool		z_bool;

	global_position = unmap_vec3(collision->position,
		mlx->scene.camera.position, mlx->scene.camera.inverse_transform);
	x_bool = is_float_on_grad(fabs(global_position.x), step, precision);
	y_bool = is_float_on_grad(fabs(global_position.y), step, precision);
	z_bool = is_float_on_grad(fabs(global_position.z), step, precision);
	color.rgba = 0X000000FF;
	color.r = x_bool * 0XFF;
	color.g = y_bool * 0XFF;
	color.b = z_bool * 0XFF;
	return (color);
}

static void	set_pixel(struct s_mlx *mlx, int x, int y, mlx_color color)
{
	if (mlx->down_sizing == 1)
	{
		mlx_pixel_put(mlx->context, mlx->render.win, x, y, color);
		mlx_set_image_pixel(mlx->context, mlx->img, x, y, color);
		return ;
	}
	for (int yi = y; yi < WIN_HEIGHT && yi < y + mlx->down_sizing; yi++)
	{
		for (int xi = x; yi < WIN_WIDTH && xi < x + mlx->down_sizing; xi++)
		{
			mlx_pixel_put(mlx->context, mlx->render.win, x, y, color);
			mlx_set_image_pixel(mlx->context, mlx->img, x, y, color);
		}
	}
}

void	draw_pixel(struct s_mlx *mlx, int x, int y, t_collision *collision)
{
	mlx_color	color;
	mlx_color	light;
	mlx_color	ambient;

	light = get_light_color(mlx);
	ambient = rgb_to_rgba(mlx->scene.ambient.color);
	if (collision->object)
	{
		// draw RGB lines on object,	DEBUG ONLY
		if (g_debug_show_grid)
		{
			color = draw_graduation(mlx, collision, 1.0f, 0.02f);
			if (color.rgba != 0X000000FF)
			{
				set_pixel(mlx, x, y, color);
				return ;
			}
		}
		// Normal program
		if (mlx->scene.objects[0]->type == OBJ_LIGHT
			&& collision->dist < 25000.0f)
			color = filter_acolor(light, lit_color(mlx, collision));
		else
			color.rgba = 0X000000FF;
		color = blend_color(color, ambient);
		set_pixel(mlx, x, y, color);
	}
	else
		set_pixel(mlx, x, y, ambient);
}

void	loop_render(struct s_mlx *mlx)
{
	t_ray		ray;
	t_collision	collision;

	loop_draw_ui(mlx);
	mlx_clear_window(mlx->context, mlx->render.win, (mlx_color) 0xFF000000);
	ft_bzero(&collision, sizeof (collision));
	ft_bzero(&ray, sizeof (ray));
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			if (x % mlx->down_sizing == 0 && y % mlx->down_sizing == 0)
			{
				ray = shoot_ray_from_camera(mlx, x, y);
				get_collision(mlx, &ray, &collision);
				draw_pixel(mlx, x, y, &collision);
			}
		}
	}
}
