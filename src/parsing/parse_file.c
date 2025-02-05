/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:54 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 02:21:14 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "object/objects.h"
#include "scene/scene.h"
#include "strings/dstring.h"
#include <files/files.h>
#include <logger/logger.h>
#include <parsing/parse.h>

static bool	parse_file_error_split(struct s_string *file)
{
	logger_error("unable to allocate file split");
	ft_free("s", file);
	return (false);
}

static bool	parse_file_lines(struct s_string *lines, size_t count, struct s_scene *scene)
{
	for (size_t i = 0; i < count; i++)
		if (!parse_line(lines[i], scene))
			return (false);
	return (true);
}

static bool	check_scene(struct s_scene *scene)
{
	if (!scene->ambient.exist || !scene->camera.exist)
	{
		logger_error("missing camera or ambient light");
		return (false);
	}
	return (true);
}

bool	parse_file(const char *path, struct s_scene *scene)
{
	struct s_string		file;
	size_t				count;
	struct s_string		*lines;
	bool				ret;

	count = 0;
	ret = true;
	if (!ft_strsufix((char *)path, ".rt"))
		return (false);
	if (!get_file(&file, path))
		return (false);
	lines = string_split(file, string_new_u_from_cstr("\n"), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (parse_file_error_split(&file));
	if (!parse_file_lines(lines, count, scene))
		ret = false;
	ft_free("sp", &file, lines);
	if (ret && !check_scene(scene))
		ret = false;
	return (ret);
}
