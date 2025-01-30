/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:57:26 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 21:44:29 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/mmlx.h>

#define AXIS_CENTER_X 20
#define AXIS_CENTER_Y 500
#define AXIS_SIZE 10
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

t_mat3	axes_init()
{
	return ((t_mat3){
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
}

static void	swap_sort(float *should_be_small, float *should_be_large)
{
	float	tmp;

	if (*should_be_small > *should_be_large)
	{
		tmp = *should_be_small;
		*should_be_small = *should_be_large;
		*should_be_large = tmp;
	}
}

static void	axis_draw(struct s_mlx *mlx, t_vec3 origin, t_vec3 axis, mlx_color color)
{
	int	dx;
	int	dy;
	int	D;
	int	x;
	int	y;

	swap_sort(&origin.x, &axis.x);
	swap_sort(&origin.y, &axis.y);
	dx = axis.x - origin.x;
	dy = axis.y - origin.y;
	D = 2 * dy - dx;
	y = origin.y;
	x = origin.x;
	while (x < axis.x)
	{
		mlx_pixel_put(mlx->context, mlx->ui.win, x, y, color);
		if (D > 0)
		{
			y++;
			D -= 2 * dx;
		}
		D += 2 * dy;
		x++;
	}
}

void	axes_draw(struct s_mlx *mlx)
{
	t_mat3	axes;
	t_vec3	origin;

	axes = mat3_scal_mul(mat3_mul(mlx->scene.camera.transform, axes_init()), AXIS_SIZE);
	origin = mat3_apply(mlx->scene.camera.transform, vec3_new_from_one(-1.0f / 6.0f));
	origin = vec3_scal_mul(origin, AXIS_SIZE);
	origin.x += AXIS_CENTER_X;
	origin.y += AXIS_CENTER_Y;
	axis_draw(mlx, origin, vec3_new(axes.m00, axes.m01, 0.0f), RED);
	axis_draw(mlx, origin, vec3_new(axes.m10, axes.m11, 0.0f), GREEN);
	axis_draw(mlx, origin, vec3_new(axes.m20, axes.m21, 0.0f), BLUE);
}
