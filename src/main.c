/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 13:38:37 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/collision.h"
#include <minirt.h>

void	register_free_funcs(void)
{
	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	ft_free_register('c', (t_free_function)free_scene);
	ft_free_register('m', (t_free_function)free_mlx);
}

void	register_mlx_hooks(struct s_mlx *mlx)
{
	mlx_on_event(mlx->context, mlx->ui.win, MLX_WINDOW_EVENT,
		(t_mlx_e_f)win_close, mlx);
	mlx_on_event(mlx->context, mlx->render.win, MLX_WINDOW_EVENT,
		(t_mlx_e_f)win_close, mlx);
	mlx_on_event(mlx->context, mlx->ui.win, MLX_MOUSEDOWN,
		(t_mlx_e_f)update_buttons_click, mlx);
	mlx_on_event(mlx->context, mlx->ui.win, MLX_MOUSEUP,
		(t_mlx_e_f)update_buttons_unclick, mlx);
	mlx_on_event(mlx->context, mlx->ui.win, MLX_KEYDOWN, (t_mlx_e_f)key_event,
		mlx);
	mlx_on_event(mlx->context, mlx->render.win, MLX_KEYDOWN,
		(t_mlx_e_f)key_event, mlx);
	mlx_add_loop_hook(mlx->context, (t_mlx_l_f)loop_render, mlx);
}

int	main(int c, char **args)
{
	struct s_mlx	mlx;

	register_free_funcs();
	if (c != 2)
	{
		logger_error("usage: %s <path/to/file.rt>", args[0]);
		return (1);
	}
	if (!init_mlx(&mlx))
	{
		logger_error("during mlx initialisation", args[0]);
		ft_free("m", &mlx);
		return (1);
	}
	if (!parse_file(args[1], &mlx.scene, args[0]) || !dup_objects(&mlx.scene))
	{
		ft_free("mc", &mlx, &mlx.scene);
		return (1);
	}
	map_scene(&mlx.scene, mlx.scene.camera.position,
		mlx.scene.camera.transform);
// 	t_ray		ray;
// 	t_collision	collision;
// 	int			x = 20;
// 	int			y = 20;
//         ft_bzero(&ray, sizeof(t_ray));
//         ft_bzero(&collision, sizeof(t_collision));
// 
// 	mlx.scene.camera.position = vec3_add(mlx.scene.camera.position,
// 			vec3_scal_mul(mlx.scene.camera.position, +0.5f));
// 	camera_create_transform(&mlx.scene.camera);
// 	map_scene(&mlx.scene, mlx.scene.camera.position, mlx.scene.camera.transform);
// 
// 	ray = shoot_ray_from_camera(&mlx, x, y);
// 	get_collision(&mlx, &ray, &collision);
// 	draw_pixel(&mlx, x, y, &collision);
// 
//         ft_bzero(&ray, sizeof(t_ray));
//         ft_bzero(&collision, sizeof(t_collision));
// 
// 	mlx.scene.camera.position = vec3_add(mlx.scene.camera.position,
// 			vec3_scal_mul(mlx.scene.camera.position, -0.5f));
// 	camera_create_transform(&mlx.scene.camera);
// 	map_scene(&mlx.scene, mlx.scene.camera.position, mlx.scene.camera.transform);
// 
// 	ray = shoot_ray_from_camera(&mlx, x, y);
// 	get_collision(&mlx, &ray, &collision);
// 	draw_pixel(&mlx, x, y, &collision);
//         return 0;
	register_mlx_hooks(&mlx);
	mlx_loop(mlx.context);
	ft_free("m", &mlx);
	return (0);
}
