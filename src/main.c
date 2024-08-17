/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/15 13:12:33 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <files/files.h>
#include <libft.h>
#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings/dstring.h>

int	main(int c, char **args)
{
	struct s_scene	scene;

	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	if (c != 2)
	{
		printf("USAGE: %s <path/to/file.rt>\n", args[0]);
		return (1);
	}
	if (!parse_file(args[1], &scene, args[0]))
		return (1);
	print_scene(scene);
	return (0);
}
