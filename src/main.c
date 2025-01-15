/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/13 18:07:46 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene.h"
#include <files/files.h>
#include <libft.h>
#include <logger/logger.h>
#include <mlx.h>
#include <mlx/hooks.h>
#include <mlx/mmlx.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <render/render.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings/dstring.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>

/**
 * @brief test brief
 */
void	register_free_funcs(void)
{
	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	ft_free_register('c', (t_free_function)free_scene);
	ft_free_register('m', (t_free_function)free_mlx);
}

static size_t	object_size(struct s_object *object)
{
	if (object->type == OBJ_LIGHT)
	{
		return (sizeof(struct s_light));
	}
	else if (object->type == OBJ_SPHERE)
	{
		return (sizeof(struct s_sphere));
	}
	else if (object->type == OBJ_PLANE)
	{
		return (sizeof(struct s_plane));
	}
	else if (object->type == OBJ_CYLINDER)
	{
		return (sizeof(struct s_cylinder));
	}
	else
	{
		return (0);
	}
}

static bool	dup_objects(struct s_scene *scene)
{
	size_t	obj_size;
	size_t	i;
	size_t	x;

	scene->map_objects = ft_calloc(scene->len, sizeof(struct s_object *));
	if (!scene->map_objects)
		return (false);
	i = 0;
	while (i < scene->len)
	{
		obj_size = object_size(scene->objects[i]);
		scene->map_objects[i] = malloc(obj_size);
		if (!scene->map_objects[i])
		{
			x = 0;
			while (x < i)
				ft_free("p", scene->map_objects[x++]);
			ft_free("p", scene->map_objects);
			return (false);
		}
		ft_memcpy(scene->map_objects[i], scene->objects[i], obj_size);
		i++;
	}
	return (true);
}

t_vec3	map_vec3(t_vec3 vec, t_vec3 translation, t_mat3 transform)
{
	vec = vec3_sub(vec, translation);
	vec = mat3_apply(transform, vec);
	return (vec);
}

t_vec3	unmap_vec3(t_vec3 vec, t_vec3 translation, t_mat3 inverse_transform)
{
	vec = mat3_apply(inverse_transform, vec);
	vec = vec3_add(vec, translation);
	return (vec);
}

static void	map_object(struct s_object *target, struct s_object *src,
		t_vec3 translation, t_mat3 transform)
{
	target->position = map_vec3(src->position, translation, transform);
	if (src->type == OBJ_PLANE)
	{
		((struct s_plane *)target)->normal = mat3_apply(transform,
			((struct s_plane *)src)->normal);
	}
	else if (src->type == OBJ_CYLINDER)
	{
		((struct s_cylinder *)target)->axis = mat3_apply(transform,
			((struct s_cylinder *)src)->axis);
	}
}

void	map_scene(struct s_scene *scene, t_vec3 translation, t_mat3 transform)
{
	size_t	i;

	i = 0;
	while (i < scene->len)
	{
		map_object(scene->map_objects[i], scene->objects[i], translation,
			transform);
		i++;
	}
}

void	register_mlx_hooks(struct s_mlx *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win.win, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->ray.win, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->win.win, MLX_MOUSEDOWN,
		(t_mlx_e_f)update_buttons_click, mlx);
	mlx_on_event(mlx->mlx, mlx->win.win, MLX_MOUSEUP,
		(t_mlx_e_f)update_buttons_unclick, mlx);
	mlx_on_event(mlx->mlx, mlx->win.win, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
	mlx_on_event(mlx->mlx, mlx->ray.win, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
	// 	mlx_loop_hook(mlx->mlx, (t_mlx_l_f)loop_draw_ui, mlx);
	mlx_add_loop_hook(mlx->mlx, (t_mlx_l_f)loop_render, mlx);
}

#include <stdio.h> //

void	printf_vec3(t_vec3 vec) //
{
	printf("(% f, % f, % f)\n", vec.x, vec.y, vec.z);
}

void	printf_obj_type(struct s_object *obj) //
{
	if (!obj)
		printf("(void)");
	else if (obj->type == OBJ_LIGHT)
		printf("light");
	else if (obj->type == OBJ_SPHERE)
		printf("sphere");
	else if (obj->type == OBJ_PLANE)
		printf("plane");
	else if (obj->type == OBJ_CYLINDER)
		printf("cylinder");
	else
		printf("wat.");
}

void	printf_mat3(t_mat3 mat) //
{
	printf(" /% f % f % f\\\n", mat.m00, mat.m01, mat.m02);
	printf("| % f % f % f |\n", mat.m10, mat.m11, mat.m12);
	printf(" \\% f % f % f/\n", mat.m20, mat.m21, mat.m22);
}

bool			g_debug_show_grid = false;

int	main(int c, char **args)
{
	struct s_mlx	mlx;

	register_free_funcs();
	if (c != 2)
	{
		logger_error("usage: %s <path/to/file.rt>", args[0]);
		return (1);
	}
	if (!init_mlx(&mlx))
	{
		logger_error("during mlx initialisation", args[0]);
		ft_free("m", &mlx);
		return (1);
	}
	if (!parse_file(args[1], &mlx.scene, args[0]) || !dup_objects(&mlx.scene))
	{
		ft_free("mc", &mlx, &mlx.scene);
		return (1);
	}
	map_scene(&mlx.scene, mlx.scene.camera.position,
		mlx.scene.camera.transform);
	register_mlx_hooks(&mlx);
	mlx_loop(mlx.mlx);
	ft_free("m", &mlx);
	return (0);
}
