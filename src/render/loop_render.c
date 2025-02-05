/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 02:46:57 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mlx.h>
#include <mlx/hooks.h>
#include <render/render.h>
#include <ui/window.h>

void	print_obj(struct s_object *obj)
{
	switch (obj->type)
	{
	case OBJ_LIGHT:		printf("\tlight\n");
		break;
	case OBJ_SPHERE:	printf("\tsphere\n");
		break;
	case OBJ_PLANE:		printf("\tplane\n");
		break;
	case OBJ_CYLINDER:	printf("\tcylinder\n");
		break;
	default:			printf("\tnothing\n");
		break;
	}
}

void	get_collision(struct s_scene *scene, struct s_ray *ray, t_collision *collision)
{
	t_collision		tmp_collision;

	collision->object = NULL;
	collision->dist = INFINITY;
	for (size_t i_obj = 0; i_obj < scene->len; i_obj++)
	{
		if (test_collision(scene->map_objects[i_obj], ray, &tmp_collision)
		&& (tmp_collision.dist > 0 && tmp_collision.dist < collision->dist))
			*collision = tmp_collision;
	}
}

static void	set_pixel(struct s_mlx *mlx, int x, int y, mlx_color color)
{
	if (mlx->renderer.down_sizing == 1)
	{
		mlx_pixel_put(mlx->context, mlx->renderer.window.win, x, y, color);
		mlx_set_image_pixel(mlx->context, mlx->renderer.img, x, y, color);
		return ;
	}
	for (int yi = y; yi < WIN_HEIGHT && yi < y + mlx->renderer.down_sizing; yi++)
		for (int xi = x; xi < WIN_WIDTH && xi < x + mlx->renderer.down_sizing; xi++)
		{
			mlx_pixel_put(mlx->context, mlx->renderer.window.win, xi, yi, color);
			mlx_set_image_pixel(mlx->context, mlx->renderer.img, xi, yi, color);
		}
}

mlx_color	get_pixel_color(struct s_mlx *mlx, t_collision *collision)
{
	t_render_color	ambient;

	if (mlx->scene.ambient.ratio + get_lights_ratio(mlx) > 0)
	{
		ambient = color_scal_mul(rgb_to_render_color(mlx->scene.ambient.color), mlx->scene.ambient.ratio);
		return (render_to_mlx_color(
				filter_color(
					color_add(
						ambient,
						get_lit_color(mlx, collision)),
					rgb_to_render_color(collision->object->color))));
	}
	else
		return (rgb_to_mlx_color((union u_color){.rgb = 0}));
}

void	draw_pixel(struct s_mlx *mlx, int x, int y, t_collision *collision)
{
	mlx_color	color;

	if (collision->object && collision->dist < MAX_DEPTH)
	{
		color = get_pixel_color(mlx, collision);
		set_pixel(mlx, x, y, color);
	}
	else
		set_pixel(mlx, x, y, rgb_to_mlx_color(mlx->scene.ambient.color));
}

void	loop_render(struct s_mlx *mlx)
{
	t_ray			ray;
	t_collision		collision;

	loop_draw_ui(mlx);
	mlx_clear_window(mlx->context, mlx->renderer.window.win, (mlx_color)0xFF000000);
	ft_bzero(&collision, sizeof(collision));
	ft_bzero(&ray, sizeof(ray));
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			if (x % mlx->renderer.down_sizing == 0 && y % mlx->renderer.down_sizing == 0)
			{
				ray = shoot_ray(x, y, mlx->scene.camera.screen_to_cam_factor);
				get_collision(&mlx->scene, &ray, &collision);
				draw_pixel(mlx, x, y, &collision);
			}
}
