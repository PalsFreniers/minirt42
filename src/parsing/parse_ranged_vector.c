#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

static bool	get_range(struct s_string sratio, float *ratio,
		struct s_string *parts, float range[2])
{
	if (!parse_range(sratio, ratio, range[0], range[1]))
	{
		ft_free("p", parts);
		return (false);
	}
	return (true);
}

bool	parse_ranged_vector(struct s_string rgb, struct s_vec3 *pos, float up,
		float down)
{
	struct s_string	*parts;
	size_t			count;

	parts = string_split(rgb, string_new_u_from_cstr(","), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (false);
	if (!string_obey(rgb, float_vec_obey) || count != 3)
	{
		logger_error("unable to parse position");
		ft_free("p", parts);
		return (false);
	}
	if (!get_range(parts[0], &(pos->x), parts, (float [2]){up, down}))
		return (false);
	if (!get_range(parts[1], &(pos->y), parts, (float [2]){up, down}))
		return (false);
	if (!get_range(parts[2], &(pos->z), parts, (float [2]){up, down}))
		return (false);
	ft_free("p", parts);
	return (true);
}
