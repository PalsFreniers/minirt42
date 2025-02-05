/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:07:00 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 01:44:18 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ui/buttons.h"
#include <actions/buttons_actions.h>
#include <libft.h>
#include <mlx/mmlx.h>
#include <scene/scene.h>
#include <ui/window.h>

void	mlx_init_static_button(struct s_mlx *mlx)
{
	mlx->ui.static_b[0] = button_new(0, 0, 100, 50);
	button_set(&(mlx->ui.static_b[0]), "quit", mlx, (t_button_f)button_quit);
	mlx->ui.static_b[1] = button_new(100, 0, 100, 50);
	button_set(&(mlx->ui.static_b[1]), "print scene", &(mlx->scene), (t_button_f)print_scene);
	mlx->ui.static_b[2] = button_new(200, 0, 100, 50);
	button_set(&(mlx->ui.static_b[2]), "add", mlx, (t_button_f)button_add_scene);
	mlx->ui.static_b[3] = button_new(300, 0, 100, 50);
	button_set(&(mlx->ui.static_b[3]), "save", &(mlx->scene), (t_button_f)button_save);
	mlx->ui.static_b[4] = button_new(400, 0, 100, 50);
	button_set(&(mlx->ui.static_b[4]), "list", mlx, (t_button_f)button_list);
	mlx->ui.static_b[5] = button_new(500, 0, 100, 50);
	button_set(&(mlx->ui.static_b[5]), "screen", mlx, (t_button_f)button_screen);
}

void	set_window_position(struct s_mlx *mlx)
{
	int		w;
	int		h;

	mlx_get_screen_size(mlx->context, mlx->ui.window.win, &w, &h);
	w /= 2;
	h = (h - WIN_HEIGHT) / 2;
	mlx_set_window_position(mlx->context, mlx->renderer.window.win, w - WIN_WIDTH, h);
	mlx_set_window_position(mlx->context, mlx->ui.window.win, w, h);
}

mlx_window_create_info	create_info(mlx_image render_target, const char *title)
{
	mlx_window_create_info	info;

	info = (mlx_window_create_info){0};
	if (render_target)
		info.render_target = render_target;
	if (title)
		info.title = title;
	info.width = WIN_WIDTH;
	info.height = WIN_HEIGHT;
	return (info);
}

bool	init_mlx(struct s_mlx *mlx)
{
	mlx->context = mlx_init();
	if (!mlx->context)
		return (false);
	mlx->renderer.window.info = create_info(0x0, "minirt render");
	mlx->renderer.window.win = mlx_new_window(mlx->context, &mlx->renderer.window.info);
	if (!mlx->renderer.window.win)
		return (false);
	mlx->ui.window.info = create_info(0x0, "minirt panel");
	mlx->ui.window.win = mlx_new_window(mlx->context, &mlx->ui.window.info);
	if (!mlx->ui.window.win)
		return (false);
	mlx->renderer.img = mlx_new_image(mlx->context, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->renderer.img)
		return (false);
	set_window_position(mlx);
	mlx_init_static_button(mlx);
	mlx->renderer.down_sizing = 4;
	return (true);
}

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->context)
		return ;
	if (mlx->renderer.window.win)
		mlx_destroy_window(mlx->context, mlx->renderer.window.win);
	if (mlx->ui.window.win)
		mlx_destroy_window(mlx->context, mlx->ui.window.win);
	if (mlx->renderer.img)
		mlx_destroy_image(mlx->context, mlx->renderer.img);
	mlx_destroy_context(mlx->context);
}
