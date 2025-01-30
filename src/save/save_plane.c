/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:01:20 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:01:21 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_plane(struct s_plane *self, int fd)
{
	write(fd, "pl ", 3);
	if (!save_vec3(self->base.position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_vec3(self->normal, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_color(self->base.color, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
