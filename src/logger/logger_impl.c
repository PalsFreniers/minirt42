#include <logger/logger.h>
#include <stdio.h>

static const char	*logger_preamble(enum e_logger_level lvl)
{
	if (lvl == LOG_DEBUG)
		return ("[DEBUG] => ");
	if (lvl == LOG_INFO)
		return ("[INFO] => ");
	if (lvl == LOG_WARNING)
		return ("[WARNING] => ");
	if (lvl == LOG_ERROR)
		return ("[ERROR] => ");
	return ("[LOG] => ");
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
	printf("%s", logger_preamble(lvl));
	vprintf(fmt, ap);
	printf("\n");
}
