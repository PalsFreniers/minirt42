/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:59:50 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 01:59:55 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>

void	logger_debug(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	logger_log_v(LOG_DEBUG, fmt, ap);
	va_end(ap);
}

void	logger_info(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	logger_log_v(LOG_INFO, fmt, ap);
	va_end(ap);
}

void	logger_warning(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	logger_log_v(LOG_WARNING, fmt, ap);
	va_end(ap);
}

void	logger_error(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	logger_log_v(LOG_ERROR, fmt, ap);
	va_end(ap);
}
