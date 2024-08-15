#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_range(struct s_string sratio, float *ratio, float up, float down)
{
	if (!string_obey(sratio, float_obey) || string_count_of(sratio, '.') > 1)
	{
		logger_error("unable to parse floating point number");
		return (false);
	}
	*ratio = string_to_float(sratio);
	if (string_error(true, 0) != SUCCESS)
	{
		logger_error("unable to parse floating point number");
		return (false);
	}
	if (*ratio > up || *ratio < down)
	{
		logger_error("floating point value should be in range %f-%f", down, up);
		logger_info("floating point value is currently: %f%%", *ratio);
		return (false);
	}
	return (true);
}
