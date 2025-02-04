/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:14:23 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 23:29:50 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <ui/vline.h>
#include <ui/window.h>

void	vline_print(struct s_mlx *mlx, struct s_vline v, mlx_color color)
{
	int	tmp;
	int	i;

	if (v.y1 > v.y2)
	{
		tmp = v.y1;
		v.y1 = v.y2;
		v.y2 = tmp;
	}
	i = v.y1;
	while (i < v.y2)
	{
		if (i < WIN_HEIGHT && i >= 0)
			mlx_pixel_put(mlx->context, mlx->ui.window.win, v.x, i, color);
		i++;
	}
}

void	hline_print(struct s_mlx *mlx, struct s_vline v, mlx_color color)
{
	int	tmp;
	int	i;

	if (v.y1 > v.y2)
	{
		tmp = v.y1;
		v.y1 = v.y2;
		v.y2 = tmp;
	}
	i = v.y1;
	while (i < v.y2)
	{
		if (i < WIN_WIDTH && i >= 0)
			mlx_pixel_put(mlx->context, mlx->ui.window.win, i, v.x, color);
		i++;
	}
}
