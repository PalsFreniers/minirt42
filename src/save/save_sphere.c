/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:01:23 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:01:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_sphere(struct s_sphere *self, int fd)
{
	write(fd, "sp ", 3);
	if (!save_vec3(self->base.position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->diameter, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_color(self->base.color, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
