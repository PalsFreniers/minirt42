/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2024/12/14 23:37:16 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "mlx.h"
#include "render.h"
#include <math.h>
#include <math/la.h>
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

	ray.direction.x = (x - WIN_WIDTH / 2) * mlx->scene.camera.screen_to_camera_factor;
	ray.direction.y = (y - WIN_HEIGHT / 2) * mlx->scene.camera.screen_to_camera_factor;
	ray.direction.z = 1;
	// ray.direction = mat3_apply(mlx->scene.camera.transform, ray.direction);		// Magic, so simple yet I'm so proud of it!
	// ray.origin = mlx->scene.camera.position;
	// // // Should we normalise the ray ?
	// // // If we don't *need* to,
	// // we could use the not
	// // 	-normalised ray to easily determine if an object is inside the camera.return (ray);
	ray.direction = vec3_normalise(ray.direction);
	return (ray);
}

t_collision	get_collision(struct s_mlx *mlx, struct s_ray ray)
{
	t_collision		collision;
	t_collision		tmp_collision;
	size_t			i_obj;

	collision.object = NULL;
	collision.dist = INFINITY;
	i_obj = 0;
	while (i_obj < mlx->scene.len)
	{
		if (test_collision(mlx, mlx->scene.map_objects[i_obj], ray,
				&tmp_collision) == 1)
		{
			if (tmp_collision.dist > 0 && tmp_collision.dist < collision.dist)
			{
				collision = tmp_collision;
				collision.dist = tmp_collision.dist;
			}
		}
		i_obj++;
	}
	return (collision);
}

static bool	is_float_on_grad(float f, float step, float precision)
{
	float	mod;

	mod = fmod(f, step);
	return (mod < precision || mod > (step - precision));
}

// static bool	keep_black_dist(float dist, float step, float precision)
// {
// 	return (is_float_on_grad(dist, step, precision));
// }

// static bool	keep_black_grad(t_collision collision, float step, float precision)
// {
// 	bool		x_bool;
// 	bool		y_bool;
// 	bool		z_bool;

// 	x_bool = is_float_on_grad(collision.position.x, step, precision);
// 	y_bool = is_float_on_grad(collision.position.y, step, precision);
// 	z_bool = is_float_on_grad(collision.position.z, step, precision);
// 	return (x_bool && y_bool && z_bool);
// }

static t_acolor	draw_graduation(t_collision collision, float step, float precision)
{
	t_acolor	color;
	bool		x_bool;
	bool		y_bool;
	bool		z_bool;

	x_bool = is_float_on_grad(fabs(collision.position.x), step, precision);
	y_bool = is_float_on_grad(fabs(collision.position.y), step, precision);
	z_bool = is_float_on_grad(fabs(collision.position.z), step, precision);
	color.argb = 0XFF000000;
	color.r = x_bool * 0XFF;
	color.g = y_bool * 0XFF;
	color.b = z_bool * 0XFF;
	return (color);
}

void	draw_pixel(struct s_mlx *mlx, int x, int y, t_collision collision)
{
	t_acolor	color;
	t_acolor	light;
	t_acolor	ambient;

	light = get_light_acolor(mlx);
	ambient = rgb_to_rgba(mlx->scene.ambient.color);
	// if (collision.object && !keep_black_dist(collision.dist, 1.0f, 0.05f))
	// if (collision.object && !keep_black_grad(collision, 1.0f, 0.05f))
	if (collision.object)
	{
		// draw RGB lines on object,	DEBUG ONLY
		color = draw_graduation(collision, 1.0f, 0.02f);
		if (color.argb != 0XFF000000)
		{
			mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, color.argb);
			return ;
		}
		// Normal program
		if (mlx->scene.objects[0]->type == OBJ_LIGHT)
			color = filter_acolor(light, lit_color(mlx, collision));
		else
			color.argb = 0XFF000000;
		color = blend_acolor(color, ambient);
		mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, color.argb);
	}
	else
		mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, ambient.argb);
}

// // void	loop_render(struct s_mlx *mlx)
// {
// 	int				x;
// 	int				y;
// 	struct s_ray	ray;
// 	t_collision		collision;

// 	x = t * 255;
// 	return (0xFF << 24 | x << 16 | x << 8 | x);
// }

void	loop_render(struct s_mlx *mlx)
{
	// t_matrices	m;
	// t_vec3		pied;
	t_ray		ray;
	t_collision	collision;

	loop_draw_ui(mlx);
	// pied = vec3_add(vec3_mul(mlx->scene.camera.direction,
	// 			vec3_new_from_one(M_PI)), vec3_new_from_one(M_PI));
	// m.rotation = get_rotation_matrix(pied);
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			ray = shoot_ray_from_camera(mlx, x, y);
			collision = get_collision(mlx, ray);
			draw_pixel(mlx, x, y, collision);
		}
	}
	mlx_swap_ray_buffer(mlx);
}

// //#define DEG2RAD 0.0174533f
// // void loop_render(struct s_mlx *mlx) {
// //        struct s_sphere s = (struct s_sphere) {
// //                .base = (struct s_object) {
// //                        .color = (union u_color) {
// //                                .rgb = 0,
// //                        },
// //                        .position = vec3_new(100, 20, 0),
// //                        .type = OBJ_SPHERE,
// //                },
// //                .diameter = 10,
// //        };
// //        t_vec3 dum;
// //        float app = (70.f / WIN_HEIGHT) * DEG2RAD;
// //        loop_draw_ui(mlx);
// //        for(int y = 0; y < WIN_HEIGHT; y++) {
// //                for (int x = 0; x < WIN_WIDTH; ++x) {
// //                        t_mat3 rot = get_rotation_matrix(vec3_new(((WIN_WIDTH
// 					/ 2.f) - x) * app, 0, ((WIN_HEIGHT / 2.f) - y) * app));
// 					//                        t_ray r = (t_ray) {
// 					//                                .origin = vec3_zero(),
// 					//                                .direction = vec3_normalise(mat3_apply(rot,
// 			vec3_new(M_PI, 0, 0))),
// //                        };
// //                        if(sphere_collide_function(r, &s, &dum, &dum)) {
// //                                mlx_set_image_pixel(mlx->mlx, mlx->ray_back,
// 	x, y, 0xFFFFFFFF);
// 			//                        } else {
// 			//                                mlx_set_image_pixel(mlx->mlx,
// 				mlx->ray_back,
// 	x, y, 0xFF000000);
// 	//                        }
// 	//                }
// 	//        }
// 	//        mlx_swap_ray_buffer(mlx);
// //}
