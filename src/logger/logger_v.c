/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:59:47 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 01:59:56 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <logger/logger.h>

void	logger_debug_v(const char *fmt, va_list ap)
{
	logger_log_v(LOG_DEBUG, fmt, ap);
}

void	logger_info_v(const char *fmt, va_list ap)
{
	logger_log_v(LOG_INFO, fmt, ap);
}

void	logger_warning_v(const char *fmt, va_list ap)
{
	logger_log_v(LOG_WARNING, fmt, ap);
}

void	logger_error_v(const char *fmt, va_list ap)
{
	logger_log_v(LOG_ERROR, fmt, ap);
}
