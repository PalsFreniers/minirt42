#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_ambient_light(struct s_string *parts, size_t count,
		struct s_ambient *light)
{
	if (count != 3)
	{
		logger_error("unable to parse ambient light");
		ft_free("p", parts);
		return (false);
	}
	if (!parse_range(parts[1], &(light->ratio), 1, 0))
	{
		ft_free("p", parts);
		return (false);
	}
	if (!parse_color(parts[2], &(light->color)))
	{
		ft_free("p", parts);
		return (false);
	}
	ft_free("p", parts);
	return (true);
}
