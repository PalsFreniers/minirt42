#include "strings/dstring.h"
#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_float(struct s_string sratio, float *ratio)
{
	if (!string_obey(sratio, float_obey) || string_count_of(sratio, '.') > 1)
	{
		logger_error("unable to parse floating point number");
		return (false);
	}
	*ratio = string_to_float(sratio);
	if (string_error(false, 0) != STRING_SUCCESS)
	{
		logger_error("unable to parse floating point number");
		return (false);
	}
	return (true);
}
