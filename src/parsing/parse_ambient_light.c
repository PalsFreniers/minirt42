#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_ambient_light(struct s_string *parts, size_t count,
		struct s_ambient *light)
{
	if (light->exist)
	{
		logger_error("only one ambient light is able to exist at one time");
		return (false);
	}
	if (count != 3)
	{
		logger_error("unable to parse ambient light");
		return (false);
	}
	if (!parse_range(parts[1], &(light->ratio), 1, 0))
		return (false);
	if (!parse_color(parts[2], &(light->color)))
		return (false);
	light->exist = true;
	return (true);
}
