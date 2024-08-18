#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

static bool	get_float(struct s_string sratio, float *ratio,
		struct s_string *parts)
{
	if (!parse_float(sratio, ratio))
	{
		ft_free("p", parts);
		return (false);
	}
	return (true);
}

bool	parse_position(struct s_string spos, struct s_vec3 *pos)
{
	struct s_string	*parts;
	size_t			count;

	parts = string_split(spos, string_new_u_from_cstr(","), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (false);
	if (!string_obey(spos, float_vec_obey) || count != 3)
	{
		logger_error("unable to parse position");
		ft_free("p", parts);
		return (false);
	}
	if (!get_float(parts[0], &(pos->x), parts))
		return (false);
	if (!get_float(parts[1], &(pos->y), parts))
		return (false);
	if (!get_float(parts[2], &(pos->z), parts))
		return (false);
	ft_free("p", parts);
	return (true);
}
