/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_nc_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:50:26 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 02:19:16 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_regex.h"

struct s_stringv	ft_re_nc_match(const char *pattern, char *text)
{
	return (ft_re_match(ft_re_compile(pattern), text));
}
