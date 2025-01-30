/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:01:25 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:01:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <save/save.h>
#include <unistd.h>

bool	save_vec3(struct s_vec3 vec, int fd)
{
	if (!save_float(vec.x, fd))
		return (false);
	write(fd, ",", 1);
	if (!save_float(vec.y, fd))
		return (false);
	write(fd, ",", 1);
	if (!save_float(vec.z, fd))
		return (false);
	return (true);
}
