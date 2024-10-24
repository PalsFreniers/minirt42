/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwan <marwan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2024/10/24 12:10:30 by marwan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/render.h>
#include <render/collision.h>
#include <math.h>
#include <math/la.h>
#include <ui/window.h>
#include <mlx/hooks.h>

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
//look at src/math/la.h to know all the matrix and vector operations
t_vec3	shoot_ray_from_camera(struct s_mlx *mlx, int x, int y)
{
	t_vec3	ray;

	ray.x = x * mlx->scene.camera.screen_to_camera_factor;
	ray.y = y * mlx->scene.camera.screen_to_camera_factor;
	// ray.z = CAMERA_Z;
	ray.z = 1;
	// ray = rotate(ray, camera);
	// // Should we normalise the ray ?
	// // If we don't *need* to, we could use the not-normalised ray to easily determine if an object is inside the camera.
	return (ray);
}

t_collision	get_collision(struct s_mlx *mlx, struct s_vec3 ray)
{
	t_collision		collision;
	t_collision		tmp_collision;
	int				i_obj;
	float			dist;
	float			tmp_dist;

	collision.object = NULL;
	i_obj = next_object(mlx->scene.objects, -1);
	// dist = +inf;
	while (i_obj >= 0)
	{
		if (test_collision(mlx->scene.objects[i_obj], ray, &tmp_collision) == 1)
			tmp_dist = get_dist(tmp_collision);
			if (tmp_dist < dist)
			{
				collision = tmp_collision;
				dist = tmp_dist;
			}
		i_obj = next_object(mlx->scene.objects, i_obj);
	}
	return (collision);
}

void	draw_pixel(struct s_mlx *mlx, int x, int y, t_collision collision)
{
	if (collision.object)
		mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, 0xFFFFFFFF);
	else
		mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, 0xFF000000);
}

void	loop_render(struct s_mlx *mlx)
{
	int			x;
	int			y;
	t_vec3		ray;
	t_collision	collision;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			ray = shoot_ray_from_camera(mlx, x, y);
			collision = get_collision(mlx, ray);
			draw_pixel(mlx, x, y, collision);
			x++;
		}
		y++;
	}
}

//#define DEG2RAD 0.0174533f
//void loop_render(struct s_mlx *mlx) {
//        struct s_sphere s = (struct s_sphere) {
//                .base = (struct s_object) {
//                        .color = (union u_color) {
//                                .rgb = 0,
//                        },
//                        .position = vec3_new(100, 20, 0),
//                        .type = OBJ_SPHERE,
//                },
//                .diameter = 10,
//        };
//        t_vec3 dum;
//        float app = (70.f / WIN_HEIGHT) * DEG2RAD;
//        loop_draw_ui(mlx);
//        for(int y = 0; y < WIN_HEIGHT; y++) {
//                for (int x = 0; x < WIN_WIDTH; ++x) {
//                        t_mat3 rot = get_rotation_matrix(vec3_new(((WIN_WIDTH / 2.f) - x) * app, 0, ((WIN_HEIGHT / 2.f) - y) * app));
//                        t_ray r = (t_ray) {
//                                .origin = vec3_zero(),
//                                .direction = vec3_normalise(mat3_apply(rot, vec3_new(M_PI, 0, 0))),
//                        };
//                        if(sphere_collide_function(r, &s, &dum, &dum)) {
//                                mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, 0xFFFFFFFF);
//                        } else {
//                                mlx_set_image_pixel(mlx->mlx, mlx->ray_back, x, y, 0xFF000000);
//                        }
//                }
//        }
//        mlx_swap_ray_buffer(mlx);
//}
