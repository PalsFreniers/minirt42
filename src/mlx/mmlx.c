/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:07:00 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:09:59 by maamine          ###   ########.fr       */
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
	mlx->static_b[0] = button_new(0, 0, 100, 50);
	button_set(&(mlx->static_b[0]), "quit", mlx, (t_button_f)button_quit);
	mlx->static_b[1] = button_new(100, 0, 100, 50);
	button_set(&(mlx->static_b[1]), "print scene", &(mlx->scene),
		(t_button_f)print_scene);
	mlx->static_b[2] = button_new(200, 0, 100, 50);
	button_set(&(mlx->static_b[2]), "add", mlx, (t_button_f)button_add_scene);
	mlx->static_b[3] = button_new(300, 0, 100, 50);
	button_set(&(mlx->static_b[3]), "save", &(mlx->scene),
		(t_button_f)button_save);
	mlx->static_b[4] = button_new(400, 0, 100, 50);
	button_set(&(mlx->static_b[4]), "list", mlx, (t_button_f)button_list);
	mlx->static_b[5] = button_new(500, 0, 100, 50);
	button_set(&(mlx->static_b[5]), "screen", mlx, (t_button_f)button_screen);
}

void	set_window_position(struct s_mlx *mlx)
{
	int	w;
	int	h;

	mlx_get_screen_size(mlx->context, mlx->ui.win, &w, &h);
	w /= 2;
	h = (h - WIN_HEIGHT) / 2;
	mlx_set_window_position(mlx->context, mlx->render.win, w - WIN_WIDTH, h);
	mlx_set_window_position(mlx->context, mlx->ui.win, w, h);
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
	ft_bzero(mlx, sizeof(struct s_mlx));
	mlx->context = mlx_init();
	if (!mlx->context)
		return (false);
	mlx->render.info = create_info(0x0, "minirt render");
	mlx->render.win = mlx_new_window(mlx->context, &mlx->render.info);
	if (!mlx->render.win)
		return (false);
	mlx->ui.info = create_info(0x0, "minirt panel");
	mlx->ui.win = mlx_new_window(mlx->context, &mlx->ui.info);
	if (!mlx->ui.win)
		return (false);
	mlx->img = mlx_new_image(mlx->context, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		return (false);
	set_window_position(mlx);
	mlx_init_static_button(mlx);
	mlx->down_sizing = 1;
	return (true);
}

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->context)
		return ;
	if (mlx->render.win)
		mlx_destroy_window(mlx->context, mlx->render.win);
	if (mlx->ui.win)
		mlx_destroy_window(mlx->context, mlx->ui.win);
	if (mlx->img)
		mlx_destroy_image(mlx->context, mlx->img);
	mlx_destroy_context(mlx->context);
}
