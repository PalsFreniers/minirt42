/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:01:16 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:01:16 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <save/save.h>
#include <strings/dstring.h>
#include <unistd.h>

bool	save_float(float f, int fd)
{
	struct s_string	s;

	s = string_from_float(f, 4);
	if (string_error(false, 0) != STRING_SUCCESS)
	{
		string_destroy(&s);
		return (false);
	}
	write(fd, s.ptr, s.len);
	string_destroy(&s);
	return (true);
}
