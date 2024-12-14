/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/12/15 00:16:24 by maamine          ###   ########.fr       */
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
#include <stdint.h>
#include <stdlib.h>
#include <strings/dstring.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>
#include <render/render.h>

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
		return (sizeof (struct s_light));
	}
	else if (object->type == OBJ_SPHERE)
	{
		return (sizeof (struct s_sphere));
	}
	else if (object->type == OBJ_PLANE)
	{
		return (sizeof (struct s_plane));
	}
	else if (object->type == OBJ_CYLINDER)
	{
		return (sizeof (struct s_cylinder));
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

	scene->map_objects = ft_calloc(scene->len, sizeof (struct s_object *));
	if (!scene->map_objects)
		return (false);
	i = 0;
	while (i < scene->len)
	{
		obj_size = object_size(scene->objects[i]);
		scene->map_objects[i] = malloc(obj_size);
		if (!scene->map_objects[i])
		{
			// TODO: free everything ! (integrate into ft_free() ?)
			return (false);
		}
		ft_memcpy(scene->map_objects[i], scene->objects[i], obj_size);
		i++;
	}
	return (true);
}

static void	map_object(struct s_object *target, struct s_object *src,
	t_vec3 translation, t_mat3 transform)
{
	target->position = vec3_sub(src->position, translation);
	target->position = mat3_apply(transform, target->position);
	if (src->type == OBJ_PLANE)
	{
		((struct s_plane *) target)->normal
			= vec3_sub(((struct s_plane *) src)->normal, translation);
		((struct s_plane *) target)->normal
			= mat3_apply(transform, ((struct s_plane *) target)->normal);
	}
	else if (src->type == OBJ_CYLINDER)
	{
		((struct s_cylinder *) target)->axis
			= vec3_sub(((struct s_cylinder *) src)->axis, translation);
		((struct s_cylinder *) target)->axis
			= mat3_apply(transform, ((struct s_cylinder *) target)->axis);
	}
}

void	map_scene(struct s_scene *scene, t_vec3 translation, t_mat3 transform)
{
	size_t	i;

	i = 0;
	while (i < scene->len)
	{
		map_object(scene->map_objects[i], scene->objects[i],
			translation, transform);
		i++;
	}
}

void	register_mlx_hooks(struct s_mlx *mlx)
{
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->ray, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEDOWN,
		(t_mlx_e_f)update_buttons_click, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_MOUSEUP,
		(t_mlx_e_f)update_buttons_unclick, mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
	mlx_on_event(mlx->mlx, mlx->ray, MLX_KEYDOWN, (t_mlx_e_f)key_event, mlx);
// 	mlx_loop_hook(mlx->mlx, (t_mlx_l_f)loop_draw_ui, mlx);
	mlx_loop_hook(mlx->mlx, (t_mlx_l_f)loop_render, mlx);
}

#include <stdio.h>	//
void	printf_vec3(t_vec3 vec)	//
{
	printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
}

void	printf_obj_type(struct s_object *obj)	//
{
	if (obj->type == OBJ_LIGHT)
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

int	main(int c, char **args)
{
	struct s_mlx	mlx;

	register_free_funcs();
        // reg
	if (c != 2)
	{
		logger_error("usage: %s <path/to/file.rt>", args[0]);
		return (1);
	}
	if (!parse_file(args[1], &mlx.scene, args[0]) || !dup_objects(&mlx.scene))
	{
		ft_free("c", &mlx.scene);
		return (1);
	}
	if (!init_mlx(&mlx))
	{
		logger_error("during mlx initialisation", args[0]);
		ft_free("m", &mlx);
		return (1);
	}
	map_scene(&mlx.scene, mlx.scene.camera.position,
		mlx.scene.camera.transform);
	register_mlx_hooks(&mlx);
	mlx_loop(mlx.mlx);
	ft_free("m", &mlx);
	return (0);
}
