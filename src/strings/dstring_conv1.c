/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_conv1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:03:33 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 03:53:21 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dstring.h"
#include "dstring_utils.h"

uint64_t	string_to_uqword_ovf(struct s_string self, uint64_t ovf)
{
	uint64_t	ret;
	size_t		last;

	ret = 0;
	last = 0;
	for (size_t i = 0; i < self.len && ft_isdigit(self.ptr[i]) && ret >= last; i++)
	{
		last = ret;
		ret *= 10;
		ret += self.ptr[i] - '0';
		if (ovf > 0)
			ret %= ovf;
	}
	if (ret < last)
		string_error(true, STRING_CONVERSION_OVERFLOW);
	return (ret);
}

size_t	string_conv_trimspaces(struct s_string self)
{
	size_t	off;

	for (off = 0; off < self.len && ft_isspace(self.ptr[off]); off++)
		;
	return (off);
}

bool	string_is_negative(struct s_string self, size_t *off)
{
	bool	negative;

	negative = false;
	if (self.ptr[*off] == '-')
		negative = true;
	if (self.ptr[*off] == '-' || self.ptr[*off] == '+')
		(*off)++;
	return (negative);
}

int8_t	string_to_sbyte(struct s_string self)
{
	size_t		off;
	bool		negative;
	uint8_t		ret;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	negative = string_is_negative(self, &off);
	ret = string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off), MAX_U8 + 1);
	if (string_error(false, 0) == STRING_CONVERSION_OVERFLOW)
		return (ret);
	if (ret > MAX_I8 + negative)
	{
		string_error(true, STRING_CONVERSION_OVERFLOW);
		return (ret);
	}
	if (negative)
		return (-ret);
	else
		return (ret);
}

uint8_t	string_to_ubyte(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	return (string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off), MAX_U8 + 1));
}
