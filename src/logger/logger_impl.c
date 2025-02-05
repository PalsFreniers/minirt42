/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:59:45 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 04:03:25 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>
#include <ft_printf.h>
#include <stdio.h>

static const char	*logger_preamble(enum e_logger_level lvl)
{
	switch (lvl)
	{
	case LOG_DEBUG:		return ("[DEBUG] => ");
	case LOG_INFO:		return ("[INFO] => ");
	case LOG_WARNING:	return ("[WARNING] => ");
	case LOG_ERROR:		return ("[ERROR] => ");
	default:			return ("[LOG] => ");
	}
}

void	logger_log(enum e_logger_level lvl, const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	logger_log_v(lvl, fmt, ap);
	va_end(ap);
}

void	logger_log_v(enum e_logger_level lvl, const char *fmt, va_list ap)
{
	if (lvl == LOG_ERROR)
		printf("Error\n");
	ft_printf("%s", logger_preamble(lvl));
	ft_vprintf(fmt, ap);
	ft_printf("\n");
}
