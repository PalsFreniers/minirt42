/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:23:06 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 01:13:03 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_ambient_light(struct s_string *parts, size_t count, struct s_ambient *light)
{
	if (light->exist)
	{
		logger_error("only one ambient light is able to exist at one time");
		return (false);
	}
	if (count != 3)
	{
		logger_error("unable to parse ambient light");
		return (false);
	}
	if (!parse_range(parts[1], &(light->ratio), 1, 0))
		return (false);
	if (!parse_color(parts[2], &(light->color)))
		return (false);
	light->exist = true;
	return (true);
}
