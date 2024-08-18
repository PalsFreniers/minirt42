#include "strings/dstring.h"
#include <logger/logger.h>
#include <parsing/parse.h>

static bool	parse_line_impl(struct s_string *parts, size_t count,
		struct s_scene *scene)
{
	if (string_equal(parts[0], string_new_u_from_cstr("A")))
		return (parse_ambient_light(parts, count, &(scene->ambient)));
	if (string_equal(parts[0], string_new_u_from_cstr("C")))
		return (parse_camera(parts, count, &(scene->camera)));
	if (string_equal(parts[0], string_new_u_from_cstr("L")))
		return (parse_light(parts, count, scene));
	if (string_equal(parts[0], string_new_u_from_cstr("sp")))
		return (parse_sphere(parts, count, scene));
	if (string_equal(parts[0], string_new_u_from_cstr("pl")))
		return (parse_plane(parts, count, scene));
	if (string_equal(parts[0], string_new_u_from_cstr("cy")))
		return (parse_cylinder(parts, count, scene));
	logger_error("unable to find object");
	return (false);
}

bool	parse_line(struct s_string line, struct s_scene *scene)
{
	size_t			count;
	struct s_string	*parts;
	bool			ret;

	parts = string_split(line, string_new_u_from_cstr(" "), &count);
	if (string_error(false, 0) != STRING_SUCCESS || count <= 0)
	{
		logger_error("malloc error");
		return (false);
	}
	ret = parse_line_impl(parts, count, scene);
	ft_free("p", parts);
	return (ret);
}
