/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:37 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:21:40 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <object/objects.h>

struct s_object	*object_new(size_t size, int type)
{
	struct s_object	*ret;

	ret = ft_calloc(1, size);
	if (!ret)
		return (NULL);
	ret->type = type;
	return (ret);
}
