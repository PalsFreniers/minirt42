/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_compile_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:48:55 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 03:11:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex.h"

void	re_b_slash(const char *pattern, int *i, struct s_regex *re_compiled,
		int j)
{
	if (pattern[(*i) + 1])
	{
		(*i) += 1;
		if (pattern[*i] == 'd')
			re_compiled[j].type = DIGIT;
		else if (pattern[*i] == 'D')
			re_compiled[j].type = NOT_DIGIT;
		else if (pattern[*i] == 'w')
			re_compiled[j].type = ALPHA;
		else if (pattern[*i] == 'W')
			re_compiled[j].type = NOT_ALPHA;
		else if (pattern[*i] == 's')
			re_compiled[j].type = WHITESPACE;
		else if (pattern[*i] == 'S')
			re_compiled[j].type = NOT_WHITESPACE;
		else
		{
			re_compiled[j].type = CHAR;
			re_compiled[j].ch = pattern[*i];
		}
	}
}
