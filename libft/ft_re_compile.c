/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:42:49 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 03:18:43 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex.h"
#include "libft.h"

void			re_b_slash(const char *pattern, int *i,
					struct s_regex *re_compiled, int j);

int	cc_check_inv(const char *pattern, int *i, struct s_regex *re_compiled,
		int j)
{
	if (pattern[*i + 1] == '^')
	{
		re_compiled[j].type = INV_CHAR_CLASS;
		(*i)++;
		if (!pattern[*i + 1])
			return (0);
	}
	else
		re_compiled[j].type = CHAR_CLASS;
	return (1);
}

int	cc_parse_b_slash(const char *pattern, int *i, int *bfix,
		unsigned char *ccl_buf)
{
	if (pattern[*i] == '\\')
	{
		if (*bfix >= FT_MAX_CHAR_CLASS_LEN - 1 || !pattern[*i + 1])
			return (0);
		ccl_buf[(*bfix)++] = pattern[(*i)++];
	}
	return (1);
}

int	cc_parse(const char *pattern, struct s_double d,
		struct s_regex *re_compiled, struct s_double d2)
{
	int				*i;
	size_t			j;
	int				*bfix;
	int				buf_begin;
	unsigned char	*ccl_buf;

	ccl_buf = (unsigned char *)d2.a;
	i = (int *)d.a;
	bfix = (int *)d.b;
	buf_begin = *bfix;
	j = (size_t)d2.b;
	if (!cc_check_inv(pattern, i, re_compiled, j))
		return (0);
	while (pattern[++(*i)] != ']' && pattern[*i])
	{
		if (!cc_parse_b_slash(pattern, i, bfix, ccl_buf)
			|| *bfix >= FT_MAX_CHAR_CLASS_LEN)
			return (0);
		ccl_buf[(*bfix)++] = pattern[*i];
	}
	if (*bfix >= FT_MAX_CHAR_CLASS_LEN)
		return (0);
	ccl_buf[(*bfix)++] = 0;
	re_compiled[j].ccl = &ccl_buf[buf_begin];
	return (1);
}

int	ft_regex_parse_pattern(const char *pattern, struct s_double d,
		struct s_regex *re_compiled, struct s_double d2)
{
	size_t	j;

	j = (size_t)d2.b;
	if (pattern[*((int *)d.a)] == '^')
		re_compiled[j].type = BEGIN;
	else if (pattern[*((int *)d.a)] == '$')
		re_compiled[j].type = END;
	else if (pattern[*((int *)d.a)] == '.')
		re_compiled[j].type = DOT;
	else if (pattern[*((int *)d.a)] == '*')
		re_compiled[j].type = STAR;
	else if (pattern[*((int *)d.a)] == '+')
		re_compiled[j].type = PLUS;
	else if (pattern[*((int *)d.a)] == '?')
		re_compiled[j].type = QUESTIONMARK;
	else if (pattern[*((int *)d.a)] == FT_REGEX_TYPE_CHARACTER)
		re_b_slash(pattern, (int *)d.a, re_compiled, j);
	else if (pattern[*((int *)d.a)] == '[')
		return (cc_parse(pattern, d, re_compiled, d2));
	else
	{
		re_compiled[j].type = CHAR;
		re_compiled[j].ch = pattern[*((int *)d.a)];
	}
	return (1);
}

struct s_regex	*ft_re_compile(const char *pattern)
{
	static struct s_regex	re_compiled[FT_MAX_REGEX_OBJECT];
	static unsigned char	ccl_buf[FT_MAX_CHAR_CLASS_LEN];
	int						ccls_bufidx;
	int						i;
	size_t					j;

	ccls_bufidx = 1;
	i = 0;
	j = 0;
	while (pattern[i] && (j + 1 < FT_MAX_REGEX_OBJECT))
	{
		if (!ft_regex_parse_pattern(pattern, (struct s_double){&i,
				&ccls_bufidx}, re_compiled, (struct s_double){ccl_buf,
			(void *)j}))
			return (NULL);
		if (!pattern[i])
			return (NULL);
		i++;
		j++;
	}
	re_compiled[j].type = UNUSED;
	return (re_compiled);
}
