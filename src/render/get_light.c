/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:27:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:29:55 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

struct s_object	*get_map_light(struct s_scene *scene)
{
	size_t	x;

	x = 0;
	while (x < scene->len)
	{
		if (scene->map_objects[x]->type == OBJ_LIGHT)
			return (scene->map_objects[x]);
		x++;
	}
	return (NULL);
}

struct s_object	*get_real_light(struct s_scene *scene)
{
	size_t	x;

	x = 0;
	while (x < scene->len)
	{
		if (scene->objects[x]->type == OBJ_LIGHT)
			return (scene->objects[x]);
		x++;
	}
	return (NULL);
}

mlx_color	get_light_color(struct s_mlx *mlx)
{
	return (rgb_to_mlx_color(get_real_light(&mlx->scene)->color));
}
