#include "libft.h"
#include "scene/scene.h"
#include "strings/dstring.h"
#include <files/files.h>
#include <logger/logger.h>
#include <parsing/parse.h>

static bool	parse_file_error_split(struct s_string *file)
{
	logger_error("unable to allocate file split");
	ft_free("s", &file);
	return (false);
}

static bool	parse_file_lines(struct s_string *lines, size_t count,
		struct s_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < count)
		if (!parse_line(lines[i++], scene))
			return (false);
	return (true);
}

bool	parse_file(const char *path, struct s_scene *scene, const char *prog)
{
	struct s_string	file;
	size_t			count;
	struct s_string	*lines;
	bool			ret;

	ret = true;
	ft_bzero(scene, sizeof(struct s_scene));
	if (!ft_strsufix((char *)path, ".rt"))
	{
		logger_info("usage: %s <path/to/file.rt>", prog);
		return (false);
	}
	if (!get_file(&file, path))
		return (false);
	lines = string_split(file, string_new_u_from_cstr("\n"), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (parse_file_error_split(&file));
	if (!parse_file_lines(lines, count, scene))
		ret = false;
	ft_free("sp", &file, lines);
	return (ret);
}
