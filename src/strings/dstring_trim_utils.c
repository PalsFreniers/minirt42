/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_trim_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:26 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 04:50:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring_utils.h"

bool	string_contain(char c, struct s_string chars)
{
	size_t	i;

	i = 0;
	while (i < chars.len)
	{
		if (chars.ptr[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*calculate_trim(struct s_string self, struct s_string chars)
{
	size_t	len;

	len = 0;
	while (len < self.len && string_contain(self.ptr[len], chars))
		len++;
	return (self.ptr + len);
}

size_t	calculate_trim_len(struct s_string self, struct s_string chars)
{
	size_t	i;

	i = 0;
	while (i < self.len && string_contain(self.ptr[self.len - i - 1], chars))
		i++;
	return (self.len - i);
}
