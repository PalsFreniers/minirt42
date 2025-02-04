/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:04:35 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:49:30 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	map_scene(struct s_scene *scene, t_vec3 translation, t_mat3 transform)
{
	for (size_t i = 0; i < scene->len; i++)
		map_object(scene->map_objects[i], scene->objects[i], translation, transform);
}
