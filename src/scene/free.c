/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:02:19 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:02:20 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <scene/scene.h>
#include <stddef.h>

void	free_scene(struct s_scene *scene)
{
	size_t	i;

	if (!scene->objects)
	{
		ft_bzero(scene, sizeof(struct s_scene));
		return ;
	}
	i = 0;
	while (i < scene->len)
	{
		ft_free("p", scene->objects[i]);
		ft_free("p", scene->map_objects[i]);
		i++;
	}
	ft_free("pp", scene->objects, scene->map_objects);
	ft_bzero(scene, sizeof(struct s_scene));
}
