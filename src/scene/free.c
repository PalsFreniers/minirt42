/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:02:19 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 03:08:03 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <scene/scene.h>
#include <stddef.h>

void	free_scene(struct s_scene *scene)
{
	if (!scene->objects)
	{
		ft_bzero(scene, sizeof(struct s_scene));
		return ;
	}
	for (size_t i = 0; i < scene->len; i++)
		ft_free("pp", scene->objects[i], scene->map_objects[i]);
	ft_free("pp", scene->objects, scene->map_objects);
	ft_bzero(scene, sizeof(struct s_scene));
}
