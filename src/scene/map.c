/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:04:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 20:11:55 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
	ft_llist_destroy(&scene->map_lights, NULL);
	scene->map_lights = get_map_lights(scene);
}
