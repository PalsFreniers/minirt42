/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:14:05 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:14:06 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

char	*ft_realloc(char *ptr, size_t last, size_t new)
{
	char	*ret;

	ret = ft_calloc(new, sizeof(char));
	if (!ret)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		while (last > 0 && --last)
			ret[last] = ptr[last];
		ret[0] = ptr[0];
		free(ptr);
	}
	return (ret);
}
