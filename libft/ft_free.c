/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:23:50 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/08 21:22:26 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

void	ft_free(const char *free_pattern, ...)
{
	int		i;
	char	c;
	va_list	ap;

	i = -1;
	va_start(ap, free_pattern);
	while (free_pattern[++i])
	{
		c = free_pattern[i];
		if (c == 'p')
			free(va_arg(ap, void *));
		else if (c == 'a')
			ft_arena_destroy(va_arg(ap, struct s_arena *));
	}
	va_end(ap);
}
