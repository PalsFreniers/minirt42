/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 02:23:16 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 03:56:38 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_match.h"

int	matchmetachar(char c, char *str)
{
	if (str[0] == 'd')
		return (ft_isdigit(c));
	else if (str[0] == 'D')
		return (!ft_isdigit(c));
	else if (str[0] == 'w')
		return (c == '_' || ft_isalpha(c) || ft_isdigit(c));
	else if (str[0] == 'W')
		return (!(c == '_' || ft_isalpha(c) || ft_isdigit(c)));
	else if (str[0] == 's')
		return (ft_isspace(c));
	else if (str[0] == 'S')
		return (!ft_isspace(c));
	else
		return (c == str[0]);
}

int	matchrange(char c, char *str)
{
	return ((c != '-') && (str[0] != 0) && (str[0] != '-') && (str[1] == '-')
		&& (str[2] != 0) && ((c >= str[0]) && (c <= str[2])));
}

int	ismetachar(char c)
{
	return (c == 'd' || c == 'D' || c == 'w' || c == 'W' || c == 's'
		|| c == 'S');
}

#if defined(FT_REGEX_MATCH_DOT_NL) && (FT_REGEX_MATCH_DOT_NL == 1)

int	matchdot(char c)
{
	(void)c;
	return (1);
}
#else

int	matchdot(char c)
{
	(void)c;
	return (c != '\n' && c != '\r');
}
#endif
