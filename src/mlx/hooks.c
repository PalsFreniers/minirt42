/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:06:40 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 03:07:22 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math/la.h>
#include <mlx/hooks.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>
#include <scene/scene.h>
#include <minirt.h>

void	update_buttons_click(int e, struct s_mlx *mlx)
{
	button_update(mlx, &(mlx->ui.static_b[0]), e == MOUSE_LEFT);
	button_update(mlx, &(mlx->ui.static_b[1]), e == MOUSE_LEFT);
	button_update(mlx, &(mlx->ui.static_b[2]), e == MOUSE_LEFT);
	button_update(mlx, &(mlx->ui.static_b[3]), e == MOUSE_LEFT);
	button_update(mlx, &(mlx->ui.static_b[4]), e == MOUSE_LEFT);
	button_update(mlx, &(mlx->ui.static_b[5]), e == MOUSE_LEFT);
	for (int x = 0; x < mlx->ui.btn_count; x++)
		button_update(mlx, &(mlx->ui.interface_buttons[x]), e == MOUSE_LEFT);
}

void	update_buttons_unclick(int e, struct s_mlx *mlx)
{
	(void)e;
	mlx->ui.static_b[0].is_clicked = false;
	mlx->ui.static_b[1].is_clicked = false;
	mlx->ui.static_b[2].is_clicked = false;
	mlx->ui.static_b[3].is_clicked = false;
	mlx->ui.static_b[4].is_clicked = false;
	mlx->ui.static_b[5].is_clicked = false;
	for (int x = 0; x < mlx->ui.btn_count; x++)
		mlx->ui.interface_buttons[x].is_clicked = false;
}

int	win_close(int e, struct s_mlx *mlx)
{
	if (e == 0)
		mlx_loop_end(mlx->context);
	return (0);
}

void	loop_draw_ui(struct s_mlx *mlx)
{
	mlx_clear_window(mlx->context, mlx->ui.window.win, (mlx_color)(uint32_t) 0);
	button_draw(mlx, &(mlx->ui.static_b[0]));
	button_draw(mlx, &(mlx->ui.static_b[1]));
	button_draw(mlx, &(mlx->ui.static_b[2]));
	button_draw(mlx, &(mlx->ui.static_b[3]));
	button_draw(mlx, &(mlx->ui.static_b[4]));
	button_draw(mlx, &(mlx->ui.static_b[5]));
	for (int x = 0; x < mlx->ui.btn_count; x++)
		button_draw(mlx, &(mlx->ui.interface_buttons[x]));
	for (int x = 0; x < mlx->ui.btn_count; x++)
		numpad_draw(mlx, &(mlx->ui.interface_numpad[x]));
	axes_draw(mlx);
}

int	key_event(int key, struct s_mlx *mlx)
{
	switch (key)
	{
	case KEY_ESCAPE:
		return (win_close(0, mlx));

	case KEY_W:
	case KEY_A:
	case KEY_S:
	case KEY_D:
	case KEY_Q:
	case KEY_E:
		return (camera_move(key, mlx));

	case KEY_NUM_MINUS:
		if (mlx->renderer.down_sizing > 1)
			(mlx->renderer.down_sizing)--;
		break;

	case KEY_NUM_PLUS:
		(mlx->renderer.down_sizing)++;
		break;

	default:
		break;
	}
	map_scene(&mlx->scene, mlx->scene.camera.position, mlx->scene.camera.transform);
	return (0);
}
