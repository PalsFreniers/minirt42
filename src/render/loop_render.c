/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2025/01/29 18:40:17 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>
#include <libft.h>
#include <math.h>
#include <math/la.h>
#include <minirt.h>
#include <mlx.h>
#include <mlx/hooks.h>
#include <render/render.h>
#include <ui/window.h>

void	get_collision(struct s_scene *scene, struct s_ray *ray,
		t_collision *collision)
{
	t_collision	tmp_collision;
	size_t		i_obj;

	collision->object = NULL;
	collision->dist = INFINITY;
	i_obj = 0;
	while (i_obj < scene->len)
	{
		if (test_collision(scene->map_objects[i_obj], ray, &tmp_collision))
			if (tmp_collision.dist > 0 && tmp_collision.dist < collision->dist)
				*collision = tmp_collision;
		i_obj++;
	}
}

static void	set_pixel(struct s_mlx *mlx, int x, int y, mlx_color color)
{
	int	xi;
	int	yi;

	yi = y;
	if (mlx->down_sizing == 1)
	{
		mlx_pixel_put(mlx->context, mlx->render.win, x, y, color);
		mlx_set_image_pixel(mlx->context, mlx->img, x, y, color);
		return ;
	}
	while (yi < WIN_HEIGHT && yi < y + mlx->down_sizing)
	{
		xi = x;
		while (xi < WIN_WIDTH && xi < x + mlx->down_sizing)
		{
			mlx_pixel_put(mlx->context, mlx->render.win, xi, yi, color);
			mlx_set_image_pixel(mlx->context, mlx->img, xi, yi, color);
			xi++;
		}
		yi++;
	}
}

mlx_color	get_pixel_color(struct s_mlx *mlx, t_collision *collision)
{
	struct s_light	*o_light;
	t_render_color	ambient;
	struct s_light	dum_light;

	dum_light = (struct s_light){.base = {.type = OBJ_LIGHT, .position = {0},
		.color = {.rgb = 0xFFFFFFFF}}, .ratio = 0};
	o_light = (struct s_light *)get_real_light(&mlx->scene);
	if (o_light == NULL)
		o_light = &dum_light;
	if (mlx->scene.ambient.ratio + o_light->ratio > 0)
	{
		ambient = rgb_to_render_color(mlx->scene.ambient.color);
		ambient = color_scal_mul(ambient, mlx->scene.ambient.ratio);
		return (render_to_mlx_color(filter_color(color_add(ambient,
						color_scal_mul(lit_color(mlx, collision),
							o_light->ratio)),
					rgb_to_render_color(collision->object->color))));
	}
	else
		return (rgb_to_mlx_color((union u_color){.rgb = 0}));
}

void	draw_pixel(struct s_mlx *mlx, int x, int y, t_collision *collision)
{
	mlx_color	color;

	if (collision->object && collision->dist < 25000.0f)
	{
		color = get_pixel_color(mlx, collision);
		set_pixel(mlx, x, y, color);
	}
	else
		set_pixel(mlx, x, y, rgb_to_mlx_color(mlx->scene.ambient.color));
}

void	loop_render(struct s_mlx *mlx)
{
	t_ray		ray;
	t_collision	collision;
	int			x;
	int			y;

	loop_draw_ui(mlx);
	mlx_clear_window(mlx->context, mlx->render.win, (mlx_color)0xFF000000);
	ft_bzero(&collision, sizeof(collision));
	ft_bzero(&ray, sizeof(ray));
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (x % mlx->down_sizing == 0 && y % mlx->down_sizing == 0)
			{
				ray = shoot_ray(x, y, mlx->scene.camera.screen_to_cam_factor);
				get_collision(&mlx->scene, &ray, &collision);
				draw_pixel(mlx, x, y, &collision);
			}
			++x;
		}
		++y;
	}
	set_pixel(mlx, 14, 15, render_to_mlx_color(render_color_black()));
}
