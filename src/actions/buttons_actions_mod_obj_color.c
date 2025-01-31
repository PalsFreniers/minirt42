/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_mod_obj_color.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:42 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 17:52:52 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/objects.h"
#include <actions/buttons_actions.h>

static void	char_inc(unsigned char *ptr, bool is_left_click)
{
	int	step;

	if (*ptr == UINT8_MAX)
	{
		*ptr = 0;
		return ;
	}
	step = ((1 - is_left_click) + 10 * is_left_click);
	if (*ptr > UINT8_MAX - step)
		*ptr = UINT8_MAX;
	else
		*ptr += step;
}

static void	char_dec(unsigned char *ptr, bool is_left_click)
{
	int	step;

	if (*ptr == 0)
	{
		*ptr = UINT8_MAX;
		return ;
	}
	step = ((1 - is_left_click) + 10 * is_left_click);
	if (*ptr < step)
		*ptr = 0;
	else
		*ptr -= step;
}

static void	button_scene_modify_uchar(struct s_mlx *mlx, struct s_vec2i pos,
		unsigned char *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)char_inc);
	mlx->interface_buttons[mlx->btn_count + 1]
		= button_new(pos.x + 20, pos.y, 80, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2]
		= button_new(pos.x + 100, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)char_dec);
	mlx->interface_numpad[mlx->pad_count]
		= numpad_new(data, true, pos.x + 50, pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}

void	button_scene_modify_color(struct s_mlx *mlx, struct s_vec2i pos,
		union u_color *color)
{
	button_scene_modify_uchar(mlx, pos, &(color->r), "red");
	pos.y += 50;
	button_scene_modify_uchar(mlx, pos, &(color->g), "green");
	pos.y += 50;
	button_scene_modify_uchar(mlx, pos, &(color->b), "blue");
}
