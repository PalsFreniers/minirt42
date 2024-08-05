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
#include <stdio.h>

int	main(int c, char **args)
{
	struct s_string	file;

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
	file = fmap(args[1]);
	if (file.ptr == NULL || string_error(false, 0))
	{
		printf("[ERROR] => unable to access file %s\n", args[1]);
		string_destroy(&file);
		return (0);
	}
	string_destroy(&file);
	return (0);
}
