/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 01:50:55 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 03:56:18 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_match.h"

int	matchquestion(struct s_regex re, struct s_regex *regex, char *text,
		size_t *len)
{
	if (re.type == UNUSED)
		return (1);
	if (match_patern(regex, text, len))
		return (1);
	if (*text && matchone(re, *text++))
	{
		if (match_patern(regex, text, len))
		{
			(*len)++;
			return (1);
		}
	}
	return (0);
}

int	matchstar(struct s_regex re, struct s_regex *regex, char *text, size_t *len)
{
	size_t		prelen;
	const char	*pretext = text;

	prelen = *len;
	while (text[0] && matchone(re, *text))
	{
		text++;
		(*len)++;
	}
	while (text >= pretext)
	{
		if (match_patern(regex, text--, len))
			return (1);
		(*len)++;
	}
	*len = prelen;
	return (0);
}

int	matchplus(struct s_regex re, struct s_regex *regex, char *text, size_t *len)
{
	const char	*pretext = text;

	while (text[0] && matchone(re, *text))
	{
		text++;
		(*len)++;
	}
	while (text > pretext)
	{
		if (match_patern(regex, text--, len))
			return (1);
		(*len)--;
	}
	return (0);
}

int	matchone(struct s_regex re, char c)
{
	if (re.type == DOT)
		return (matchdot(c));
	else if (re.type == CHAR_CLASS)
		return (matchcharclass(c, (char *)re.ccl));
	else if (re.type == INV_CHAR_CLASS)
		return (!matchcharclass(c, (char *)re.ccl));
	else if (re.type == ALPHA)
		return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
	else if (re.type == NOT_ALPHA)
		return (!(c == '_' || ft_isalpha(c) || ft_isdigit(c)));
	else if (re.type == DIGIT)
		return (ft_isdigit(c));
	else if (re.type == NOT_DIGIT)
		return (!ft_isdigit(c));
	else if (re.type == WHITESPACE)
		return (ft_isspace(c));
	else if (re.type == NOT_WHITESPACE)
		return (!ft_isspace(c));
	else
		return (re.ch == c);
}

int	matchcharclass(char c, char *str)
{
	int	a;

	a = 1;
	while (a || *str)
	{
		if (a)
			a = 0;
		else
			++str;
		if (matchrange(c, str))
			return (1);
		else if (str[0] == FT_REGEX_TYPE_CHARACTER)
		{
			++str;
			if (matchmetachar(c, str) || (c == str[0] && !ismetachar(c)))
				return (1);
		}
		else if (c == str[0])
			return (matchcharclass_range(c, str));
	}
	return (0);
}
