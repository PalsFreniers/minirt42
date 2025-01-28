/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:15:05 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:36:11 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx/mmlx.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>

static bool	collide(int a[4], int b[4])
{
	if (a[0] + a[2] < b[0])
		return (false);
	if (a[0] > b[0] + b[2])
		return (false);
	if (a[1] + a[3] < b[1])
		return (false);
	if (a[1] > b[1] + b[3])
		return (false);
	return (true);
}

void	button_update(void *mlx, struct s_button *b)
{
	int	x;
	int	y;

	if (b->is_clicked)
		return ;
	mlx_mouse_get_pos(mlx, &x, &y);
	if (b->on_click && collide((int [4]){x, y, 0, 0}, (int *)b))
	{
		b->is_clicked = true;
		if (b->has_idx)
			b->on_click_idx(b->data, b->data_index);
		else
			b->on_click(b->data);
	}
}

void	button_draw(struct s_mlx *mlx, struct s_button *b)
{
	int			x;
	int			y;
	mlx_color	color;

	color = (mlx_color)BORDERC;
	mlx_mouse_get_pos(mlx->context, &x, &y);
	if (collide((int [4]){x, y, 0, 0}, (int *)b))
		color = (mlx_color)(uint32_t)BORDER2C;
	x = b->x + b->width / 2 - ((ft_strlen(b->text) * PPC) / 2);
	y = b->y + b->height / 2 - (PPC / 2) + PPC - 2;
	mlx_string_put(mlx->context, mlx->ui.win, x, y, (mlx_color)TEXTC, b->text);
	vline_print(mlx, (struct s_vline){b->x, b->y, b->y + b->height}, color);
	vline_print(mlx, (struct s_vline){b->x + b->width, b->y, b->y + b->height},
		color);
	hline_print(mlx, (struct s_vline){b->y, b->x, b->x + b->width}, color);
	hline_print(mlx, (struct s_vline){b->y + b->height, b->x, b->x + b->width},
		color);
}

struct s_button	button_new(int x, int y, int width, int height)
{
	return ((struct s_button){
		.x = x,
		.y = y,
		.width = width,
		.height = height,
		.text = NULL,
		.on_click = NULL,
		.is_clicked = false,
		.data_index = 0,
		.has_idx = false,
	});
}

void	button_set(struct s_button *self, char *text, void *data,
		t_button_f func)
{
	self->data = data;
	self->text = text;
	self->on_click = func;
}
