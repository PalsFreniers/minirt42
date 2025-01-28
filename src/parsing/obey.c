/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obey.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:23:40 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:24:04 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing/obey.h>
#include <libft.h>

bool	float_obey(char c)
{
	return (ft_isdigit(c) || c == '.' || c == '-');
}

bool	float_vec_obey(char c)
{
	return (float_obey(c) || c == ',');
}

bool	color_obey(char c)
{
	return (ft_isdigit(c) || c == ',');
}
