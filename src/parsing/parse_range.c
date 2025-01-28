/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:23:23 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:23:24 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_range(struct s_string sratio, float *ratio, float up, float down)
{
	if (!parse_float(sratio, ratio))
		return (false);
	if (*ratio > up || *ratio < down)
	{
		logger_error("floating point value should be in range %f-%f", down, up);
		logger_info("floating point value is currently: %f%%", *ratio);
		return (false);
	}
	return (true);
}
