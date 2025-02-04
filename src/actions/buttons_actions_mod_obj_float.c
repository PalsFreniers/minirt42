/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_mod_obj_float.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:48 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 00:14:55 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui/buttons.h"
#include "ui/numpad.h"
#include <actions/buttons_actions.h>

void	float_inc_1(float *ptr, bool is_left_click);

void	float_inc_full(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, POSITIVE);
}

void	ufloat_dec_full(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, NEGATIVE);
}

void	float_dec_1(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, NEGATIVE);
	if (*ptr < -1)
		*ptr = -1.0f;
}

void	button_scene_modify_float_full(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->ui.interface_buttons[mlx->ui.btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count]), "+", data, (t_button_f)float_inc_full);
	mlx->ui.interface_buttons[mlx->ui.btn_count + 1]
		= button_new(pos.x + 20, pos.y, 80, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count + 1]), text, NULL, NULL);
	mlx->ui.interface_buttons[mlx->ui.btn_count + 2]
		= button_new(pos.x + 100, pos.y, 20, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count + 2]), "-", data, (t_button_f)ufloat_dec_full);
	mlx->ui.interface_numpad[mlx->ui.pad_count]
		= numpad_new(data, false, pos.x + 30, pos.y + 40);
	mlx->ui.btn_count += 3;
	mlx->ui.pad_count += 1;
}

void	button_scene_modify_float_1_1(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->ui.interface_buttons[mlx->ui.btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count]), "+", data, (t_button_f)float_inc_1);
	mlx->ui.interface_buttons[mlx->ui.btn_count + 1]
		= button_new(pos.x + 20, pos.y, 80, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count + 1]), text, NULL, NULL);
	mlx->ui.interface_buttons[mlx->ui.btn_count + 2]
		= button_new(pos.x + 100, pos.y, 20, 20);
	button_set(&(mlx->ui.interface_buttons[mlx->ui.btn_count + 2]), "-", data, (t_button_f)float_dec_1);
	mlx->ui.interface_numpad[mlx->ui.pad_count]
		= numpad_new(data, false, pos.x + 30, pos.y + 40);
	mlx->ui.btn_count += 3;
	mlx->ui.pad_count += 1;
}
