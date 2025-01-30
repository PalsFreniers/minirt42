/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:01:09 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:01:10 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_camera(struct s_camera *self, int fd)
{
	write(fd, "C ", 2);
	if (!save_vec3(self->position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_vec3(self->direction, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->fov, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
