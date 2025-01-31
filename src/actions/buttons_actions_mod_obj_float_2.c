/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_mod_obj_float_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:45 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 17:53:07 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui/buttons.h"
#include "ui/numpad.h"
#include <actions/buttons_actions.h>

void	float_inc(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, POSITIVE);
}

void	float_inc_1(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, POSITIVE);
	if (*ptr > 1)
		*ptr = 1.0f;
}

static void	ufloat_dec_01(float *ptr, bool is_left_click)
{
	*ptr = float_step(*ptr, is_left_click, NEGATIVE);
	if (*ptr < 0.0001f)
		*ptr = 0.0001f;
}

void	button_scene_modify_float(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)float_inc);
	mlx->interface_buttons[mlx->btn_count + 1]
		= button_new(pos.x + 20, pos.y, 80, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2]
		= button_new(pos.x + 100, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)ufloat_dec_01);
	mlx->interface_numpad[mlx->pad_count]
		= numpad_new(data, false, pos.x + 30, pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}

void	button_scene_modify_float_0_1(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)float_inc_1);
	mlx->interface_buttons[mlx->btn_count + 1]
		= button_new(pos.x + 20, pos.y, 80, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2]
		= button_new(pos.x + 100, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)ufloat_dec);
	mlx->interface_numpad[mlx->pad_count]
		= numpad_new(data, false, pos.x + 30, pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}
