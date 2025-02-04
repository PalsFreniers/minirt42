/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:57:26 by maamine           #+#    #+#             */
/*   Updated: 2025/02/04 16:42:19 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ui/axes.h>

static void	line_low_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis,
		mlx_color color)
{
	int	dy;
	int	y_step;
	int	d;
	int	x;
	int	y;

	dy = axis.y - origin.y;
	y_step = 1;
	if (dy < 0)
	{
		y_step = -1;
		dy = -dy;
	}
	d = 2 * dy - (axis.x - origin.x);
	y = origin.y;
	x = origin.x;
	while (x < axis.x)
	{
		mlx_pixel_put(mlx->context, mlx->ui.win, x, y, color);
		if (d > 0)
			y += y_step;
		d += (2 * dy) - ((d > 0) * 2 * (axis.x - origin.x));
		x++;
	}
}

static void	line_high_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis,
		mlx_color color)
{
	int	dx;
	int	x_step;
	int	d;
	int	x;
	int	y;

	dx = axis.x - origin.x;
	x_step = 1;
	if (dx < 0)
	{
		x_step = -1;
		dx = -dx;
	}
	d = 2 * dx - (axis.y - origin.y);
	x = origin.x;
	y = origin.y;
	while (y < axis.y)
	{
		mlx_pixel_put(mlx->context, mlx->ui.win, x, y, color);
		if (d > 0)
			x += x_step;
		d += (2 * dx) - ((d > 0) * 2 * (axis.y - origin.y));
		y++;
	}
}

static void	line_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis,
		mlx_color color)
{
	if (fabsf(axis.y - origin.y) < fabsf(axis.x - origin.x))
	{
		if (origin.x > axis.x)
			line_low_draw(mlx, axis, origin, color);
		else
			line_low_draw(mlx, origin, axis, color);
	}
	else
	{
		if (origin.y > axis.y)
			line_high_draw(mlx, axis, origin, color);
		else
			line_high_draw(mlx, origin, axis, color);
	}
}

void	axes_draw(struct s_mlx *mlx)
{
	t_mat3	axes;
	t_vec3	origin;
	t_vec3	axis;

	axes = mat3_mul(mlx->scene.camera.inverse_transform, mat3_identity());
	origin = mat3_apply(mlx->scene.camera.inverse_transform, vec3_zero());
	origin = vec3_scal_mul(origin, AXIS_SIZE);
	origin.x += AXIS_CENTER_X;
	origin.y += AXIS_CENTER_Y;
	axis = vec3_new(axes.m00 * AXIS_SIZE + AXIS_CENTER_X, axes.m01 * AXIS_SIZE
			+ AXIS_CENTER_Y, 0.0f);
	line_draw(mlx, origin, axis, (mlx_color)RED);
	axis = vec3_new(axes.m10 * AXIS_SIZE + AXIS_CENTER_X, axes.m11 * AXIS_SIZE
			+ AXIS_CENTER_Y, 0.0f);
	line_draw(mlx, origin, axis, (mlx_color)GREEN);
	axis = vec3_new(axes.m20 * AXIS_SIZE + AXIS_CENTER_X, axes.m21 * AXIS_SIZE
			+ AXIS_CENTER_Y, 0.0f);
	line_draw(mlx, origin, axis, (mlx_color)BLUE);
}
