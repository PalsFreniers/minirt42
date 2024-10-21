/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/10/21 02:59:22 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene.h"
#include <files/files.h>
#include <libft.h>
#include <logger/logger.h>
#include <mlx.h>
#include <mlx/hooks.h>
#include <mlx/mmlx.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings/dstring.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>
#include <render/render.h>

void	register_free_funcs(void)
{
	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	ft_free_register('c', (t_free_function)free_scene);
	ft_free_register('m', (t_free_function)free_mlx);
}

void	register_mlx_hooks(struct s_mlx *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->ray, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN,
		(t_mlx_e_f)update_buttons_click, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP,
		(t_mlx_e_f)update_buttons_unclick, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
	mlx_on_event(mlx->mlx, mlx->ray, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
// 	mlx_loop_hook(mlx->mlx, (t_mlx_l_f)loop_draw_ui, mlx);
	mlx_loop_hook(mlx->mlx, (t_mlx_l_f)loop_render, mlx);
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
	if (!parse_file(args[1], &mlx.scene, args[0]))
	{
		logger_error("during file parsing", args[0]);
		ft_free("c", &mlx.scene);
		return (1);
	}
	if (!init_mlx(&mlx))
	{
		logger_error("during mlx initialisation", args[0]);
		ft_free("m", &mlx);
		return (1);
	}
	register_mlx_hooks(&mlx);
	mlx_loop(mlx.mlx);
	ft_free("m", &mlx);
	return (0);
}
