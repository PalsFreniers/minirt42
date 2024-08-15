/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/05 01:25:48 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <files/files.h>
#include <libft.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings/dstring.h>
#include <structs.h>

bool	float_obey(char c)
{
	return (ft_isdigit(c) || c == '.');
}

bool	parse_ambient_light(struct s_string *parts, size_t count,
		struct s_ambient *light)
{
	if (count != 3)
	{
		printf("[ERROR] => unable to parse ambient light\n");
		ft_free("p", parts);
		return (false);
	}
	if (!string_obey(parts[1], float_obey) || string_count_of(parts[1],
			'.') > 1)
	{
		printf("[ERROR] => unable to parse ambient light brightness ratio\n");
		ft_free("p", parts);
		return (false);
	}
	light->ratio = string_to_float(parts[1]);
	ft_free("p", parts);
	return (true);
}

bool	parse_line(struct s_string line, struct s_scene *scene)
{
	size_t			count;
	struct s_string	*parts;

	parts = string_split(line, string_new_u_from_cstr(" "), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (false);
	if (string_equal(parts[0], string_new_u_from_cstr("A")))
		return (parse_ambient_light(parts, count, &(scene->ambient)));
	return (true);
}

bool	get_file(struct s_string *file, const char *arg)
{
	*file = fmap(arg);
	if (file->ptr == NULL || string_error(false, 0) != STRING_SUCCESS)
	{
		printf("[ERROR] => unable to access file %s\n", arg);
		ft_free("s", file);
		return (false);
	}
	return (true);
}

void	print_scene(struct s_scene scene)
{
	printf("struct scene => {\n");
	printf("\tambient light => {\n");
	printf("\t\tbritness => %.10f;\n", scene.ambient.ratio);
	printf("\t\tcolor => 0x%x {%d, %d, %d};\n", scene.ambient.color.rgb,
		scene.ambient.color.r, scene.ambient.color.g, scene.ambient.color.b);
	printf("\t}\n");
	printf("}\n");
}

int	main(int c, char **args)
{
	struct s_string	file;
	size_t			count;
	struct s_string	*lines;
	size_t			i;
	struct s_scene	scene;

	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	if (c != 2)
	{
		printf("USAGE: %s <path/to/file.rt>\n", args[0]);
		return (1);
	}
	if (!ft_strsufix(args[1], ".rt"))
	{
		printf("USAGE: %s <path/to/file.rt>\n", args[0]);
		return (1);
	}
	if (!get_file(&file, args[1]))
		return (1);
	i = 0;
	lines = string_split(file, string_new_u_from_cstr("\n"), &count);
	if (string_error(false, 0) != STRING_SUCCESS)
	{
		printf("[ERROR] => unable to allocate file split\n");
		ft_free("s", &file);
		return (0);
	}
	while (i < count)
	{
		if (!parse_line(lines[i++], &scene))
		{
			ft_free("sp", &file, lines);
			return (1);
		}
	}
	ft_free("sp", &file, lines);
	print_scene(scene);
	return (0);
}
