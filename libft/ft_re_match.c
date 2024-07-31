/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:50:26 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 04:22:04 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_match.h"
#include "ft_regex.h"

struct s_string	match_string(int condition, char *ptr, size_t len)
{
	if (condition)
		return (ft_string_create(ptr, len));
	else
		return ((struct s_string){0});
}

void	inc_re_text(char **text, struct s_regex **re)
{
	++(*re);
	++(*text);
}

int	match_patern(struct s_regex *re, char *text, size_t *len)
{
	size_t	pre;
	int		a;

	pre = *len;
	a = 1;
	while (a || (text[0] && matchone(*re, *text)))
	{
		if (a)
			a = 0;
		else
			inc_re_text(&text, &re);
		if (re[0].type == UNUSED || re[1].type == QUESTIONMARK)
			return (matchquestion(re[0], &re[2], text, len));
		else if (re[1].type == STAR)
			return (matchstar(re[0], &re[2], text, len));
		else if (re[1].type == PLUS)
			return (matchplus(re[0], &re[2], text, len));
		else if (re[0].type == END && re[1].type == UNUSED)
			return (text[0] == 0);
		++(*len);
	}
	*len = pre;
	return (0);
}

struct s_string	ft_re_match_exit(char *text, char *def, size_t len, int idx)
{
	if (text[0] == 0)
		return ((struct s_string){0});
	return (ft_string_create(idx + def, len));
}

struct s_string	ft_re_match(struct s_regex *re, char *text)
{
	size_t	len;
	int		idx;
	char	*def;

	def = text;
	len = 0;
	if (!re)
		return ((struct s_string){0});
	if (re[0].type == BEGIN)
		return (match_string(match_patern(&re[1], text, &len), text, len));
	idx = -1;
	while (idx == -1 || *text)
	{
		if (idx >= 0)
			++text;
		idx++;
		if (match_patern(re, text, &len))
			return (ft_re_match_exit(text, def, len, idx));
		else
			len = 0;
	}
	return ((struct s_string){0});
}
