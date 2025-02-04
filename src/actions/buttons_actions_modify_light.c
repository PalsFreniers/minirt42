/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_modify_light.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:33:03 by maamine           #+#    #+#             */
/*   Updated: 2025/02/04 20:38:51 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/objects.h"
#include "scene/scene.h"
#include <actions/buttons_actions.h>
#include <libft.h>
#include <mlx/mmlx.h>

void	button_scene_modify_light(struct s_mlx *mlx, int index)
{
	button_scene_reset(mlx);
	button_scene_modify_float_0_1(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(((struct s_light *)mlx->scene.objects[index])->ratio), "ratio");
	button_scene_modify_color(mlx, (struct s_vec2i){240, BASE_LINE_Y},
		&(mlx->scene.objects[index]->color));
	button_scene_modify_vec3(mlx, (struct s_vec2i){380, BASE_LINE_Y},
		&(mlx->scene.objects[index]->position));
}

void	button_add_light(struct s_mlx *mlx)
{
	struct s_object	*new;

	new = object_new(sizeof(struct s_light), OBJ_LIGHT);
	if (!new)
		return ;
	ft_llist_push(&mlx->scene.map_lights, ft_llist_node_create(new));
	scene_append(&(mlx->scene), new);
	button_scene_modify_light(mlx, mlx->scene.len - 1);
}
