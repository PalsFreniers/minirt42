#ifndef LOGGER_H
# define LOGGER_H

# include <stdarg.h>

enum	e_logger_level
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
};

void	logger_debug(const char *fmt, ...);
void	logger_info(const char *fmt, ...);
void	logger_warning(const char *fmt, ...);
void	logger_error(const char *fmt, ...);
void	logger_debug_v(const char *fmt, va_list ap);
void	logger_info_v(const char *fmt, va_list ap);
void	logger_warning_v(const char *fmt, va_list ap);
void	logger_error_v(const char *fmt, va_list ap);
void	logger_log(enum e_logger_level lvl, const char *fmt, ...);
void	logger_log_v(enum e_logger_level lvl, const char *fmt, va_list ap);

#endif // LOGGER_H
