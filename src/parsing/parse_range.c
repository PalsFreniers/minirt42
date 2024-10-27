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
