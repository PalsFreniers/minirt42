/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:37 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:24:33 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <object/objects.h>

struct s_object		*object_new(size_t size, int type)
{
	struct s_object		*ret;

	ret = ft_calloc(1, size);
	if (!ret)
		return (NULL);
	ret->type = type;
	return (ret);
}
