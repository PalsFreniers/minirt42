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
