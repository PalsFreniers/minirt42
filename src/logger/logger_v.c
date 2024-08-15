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
