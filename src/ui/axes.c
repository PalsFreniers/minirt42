/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:57:26 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 15:16:17 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mmlx.h>

#define AXIS_CENTER_X 100
#define AXIS_CENTER_Y 500
#define AXIS_SIZE 50
#define RED (mlx_color){.rgba = 0xFF0000FF}
#define GREEN (mlx_color){.rgba = 0x00FF00FF}
#define BLUE (mlx_color){.rgba = 0x0000FFFF}

/**
 * |
 * |
 * |_____
 *  \
 *   \
 * 
 * Ox, Oy, Oz (3 axis)
 * C = center of the 3 axis
 * 	= 1/6 * (Ox + Oy + Oz)
 * 	= 1/6 * (1, 1, 1)
 * 
 * Once O, Ox, Oy, Oz and C have been through the transorm, unset them by C.
 * Then draw Ox, Oy, Oz.
 * 
 * Matrix `axes` is Identity unset by C, then T * A = apparent axes.
 * 
 * 	/	 5/6	-1/6	-1/6	\
 * 	|	-1/6	 5/6	-1/6	|
 * 	\	-1/6	-1/6	 5/6	/
 */

#include <stdio.h>	// 
static void	line_low_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis, mlx_color color)
{
	int	dy;
	int	y_step;
	int	D;
	int	x;
	int	y;

	// printf("line_low_draw((%d, %d), (%d, %d))\n", (int)origin.x, (int)origin.y, (int)axis.x, (int)axis.y);
	dy = axis.y - origin.y;
	y_step = 1;
	if (dy < 0)
	{
		y_step = -1;
		dy = -dy;
	}
	D = 2 * dy - (axis.x - origin.x);
	y = origin.y;
	x = origin.x;
	while (x < axis.x)
	{
		// printf("%d, %d\n", x, y);
		mlx_pixel_put(mlx->context, mlx->ui.win, x, y, color);
		if (D > 0)
			y += y_step;
		D += (2 * dy) - ((D > 0) * 2 * (axis.x - origin.x));
		x++;
	}
}

static void	line_high_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis, mlx_color color)
{
	int	dx;
	int	x_step;
	int	D;
	int	x;
	int	y;

	// printf("line_high_draw((%d, %d), (%d, %d))\n", (int)origin.x, (int)origin.y, (int)axis.x, (int)axis.y);
	dx = axis.x - origin.x;
	x_step = 1;
	if (dx < 0)
	{
		x_step = -1;
		dx = -dx;
	}
	D = 2 * dx - (axis.y - origin.y);
	x = origin.x;
	y = origin.y;
	while (y < axis.y)
	{
		// printf("%d, %d\n", x, y);
		mlx_pixel_put(mlx->context, mlx->ui.win, x, y, color);
		if (D > 0)
			x += x_step;
		D += (2 * dx) - ((D > 0) * 2 * (axis.y - origin.y));
		y++;
	}
}

static void	axis_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis, mlx_color color)
{
	if (fabsf(axis.y - origin.y) < fabsf(axis.x - origin.x))
	{
		if (origin.x > axis.x)
			line_low_draw(mlx, axis, origin, color);
		else
			line_low_draw(mlx ,origin, axis, color);
	}
	else
	{
		if (origin.y > axis.y)
			line_high_draw(mlx, axis, origin, color);
		else
			line_high_draw(mlx, origin, axis, color);
	}
}

#include <ui/vline.h>

void	axes_draw(struct s_mlx *mlx)
{
	t_mat3	axes;
	t_vec3	origin;

	axes = mat3_mul(mlx->scene.camera.transform, (t_mat3){
		.m00 = 5.0f / 6.0f,
		.m01 = -1.0f / 6.0f,
		.m02 = -1.0f / 6.0f,
		.m10 = -1.0f / 6.0f,
		.m11 = 5.0f / 6.0f,
		.m12 = -1.0f / 6.0f,
		.m20 = -1.0f / 6.0f,
		.m21 = -1.0f / 6.0f,
		.m22 = 5.0f / 6.0f,
	});
	// axes = mlx->scene.camera.transform;
	origin = mat3_apply(mlx->scene.camera.transform, vec3_new_from_one(-1.0f / 6.0f));
	origin = vec3_scal_mul(origin, AXIS_SIZE);
	origin.x += AXIS_CENTER_X;
	origin.y += AXIS_CENTER_Y;
	// axis_draw(mlx, origin, vec3_new(axes.m00 * AXIS_SIZE + AXIS_CENTER_X, axes.m01 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), RED);
	// axis_draw(mlx, origin, vec3_new(axes.m10 * AXIS_SIZE + AXIS_CENTER_X, axes.m11 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), GREEN);
	// axis_draw(mlx, origin, vec3_new(axes.m20 * AXIS_SIZE + AXIS_CENTER_X, axes.m21 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), BLUE);
	axis_draw(mlx, origin, vec3_new(axes.m00 * AXIS_SIZE + AXIS_CENTER_X, axes.m01 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), RED);
	axis_draw(mlx, origin, vec3_new(axes.m10 * AXIS_SIZE + AXIS_CENTER_X, axes.m11 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), GREEN);
	axis_draw(mlx, origin, vec3_new(axes.m20 * AXIS_SIZE + AXIS_CENTER_X, axes.m21 * AXIS_SIZE + AXIS_CENTER_Y, 0.0f), BLUE);
	// origin = vec3_new(AXIS_CENTER_X, AXIS_CENTER_Y, 0.0f);
	// axis_draw(mlx, origin, vec3_new(AXIS_CENTER_X - (AXIS_SIZE / 3), AXIS_CENTER_Y + (AXIS_SIZE / 3), 0.0f), RED);
	// axis_draw(mlx, origin, vec3_new(AXIS_CENTER_X + AXIS_SIZE, AXIS_CENTER_Y, 0.0f), GREEN);
	// axis_draw(mlx, origin, vec3_new(AXIS_CENTER_X, AXIS_CENTER_Y - AXIS_SIZE, 0.0f), BLUE);
	// // printf("over\n");
}
