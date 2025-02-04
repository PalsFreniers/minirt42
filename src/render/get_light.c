/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:27:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 20:24:48 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

struct s_llist	get_map_lights(struct s_scene *scene)
{
	struct s_llist		lst;
	struct s_llist_node	*node;
	size_t				x;

	lst = ft_llist_create();
	x = 0;
	while (x < scene->len)
	{
		if (scene->map_objects[x]->type == OBJ_LIGHT)
		{
			node = ft_llist_node_create(scene->map_objects[x]);
			ft_llist_push(&lst, node);
		}
		x++;
	}
	return (lst);
}

struct s_llist	get_real_lights(struct s_scene *scene)
{
	struct s_llist		lst;
	struct s_llist_node	*node;
	size_t	x;

	lst = ft_llist_create();
	x = 0;
	while (x < scene->len)
	{
		if (scene->objects[x]->type == OBJ_LIGHT)
		{
			node = ft_llist_node_create(scene->objects[x]);
			ft_llist_push(&lst, node);
		}
		x++;
	}
	return (lst);
}

mlx_color	get_light_color(struct s_light *light)
{
	return (rgb_to_mlx_color(light->base.color));
}

float	get_lights_ratio(struct s_llist lights)
{
	float				ratio;
	struct s_llist_node *node;

	ratio = 0.0f;
	node = lights.head;
	while (node)
	{
		ratio += ((struct s_light *)node->data)->ratio;
		node = node->next;
	}
	return (ratio);
}

t_render_color	get_lit_color(struct s_mlx *mlx, t_collision *coll,
		struct s_llist lights)
{
	t_render_color		color;
	struct s_llist_node *node;

	color = render_color_black();
	node = lights.head;
	while (node)
	{
		color = color_add(color_scal_mul(lit_color(mlx, coll, node->data),
					((struct s_light *)node->data)->ratio), color);
		node = node->next;
	}
	return (color);
}
