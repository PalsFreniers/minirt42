/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 17:21:16 by tdelage          ###   ########.fr       */
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
	mlx_loop(mlx->context);
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
		logger_error("during mlx initialisation");
		ft_free("m", &mlx);
		return (1);
	}
	if (!parse_file(args[1], &mlx.scene) || !dup_objects(&mlx.scene))
	{
		logger_error("during scene parsing");
		ft_free("mc", &mlx, &mlx.scene);
		return (1);
	}
	map_scene(&mlx.scene, mlx.scene.camera.position,
		mlx.scene.camera.transform);
	register_mlx_hooks(&mlx);
	ft_free("mc", &mlx, &mlx.scene);
	return (0);
}
