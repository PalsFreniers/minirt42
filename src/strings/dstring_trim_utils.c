/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_trim_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:26 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 03:46:07 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring_utils.h"

bool	string_contain(char c, struct s_string chars)
{
	for (size_t i = 0; i < chars.len; i++)
		if (chars.ptr[i] == c)
			return (true);
	return (false);
}

char	*calculate_trim(struct s_string self, struct s_string chars)
{
	size_t	len;

	for (len = 0; len < self.len && string_contain(self.ptr[len], chars); len++)
		;
	return (self.ptr + len);
}

size_t	calculate_trim_len(struct s_string self, struct s_string chars)
{
	size_t	i;

	for (i = 0; i < self.len && string_contain(self.ptr[self.len - i - 1], chars); i++)
		;
	return (self.len - i);
}

struct s_string		string_substr(struct s_string self, size_t start, size_t len)
{
	if (!string_check(self))
		return ((struct s_string){0});
	if (start + len > self.len)
	{
		string_error(true, STRING_SUBSTR_OUT_OF_BOUND);
		return ((struct s_string){0});
	}
	return (string_new_u(self.ptr + start, len));
}
