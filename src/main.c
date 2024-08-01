/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 05:54:01 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings/dstring.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	struct s_string	s;
	size_t			len;
	struct s_string	*strings;
	size_t			i;

	s = string_copy(string_new_u_from_cstr("  ///   Heo 123W"));
	string_erase(&s, 12, 3);
	string_append(&s, string_new_u_from_cstr("orld!    iii  "));
	string_trim(&s, string_new_u_from_cstr(" /i"));
	string_insert(&s, string_new_u_from_cstr("ll"), 2);
	printf("%.*s\n", (int)s.len, s.ptr);
	string_destroy(&s);
	s = string_new_u_from_cstr("::::Hello=How:Are=:Yo");
	len = 0;
	strings = string_split(s, string_new_u_from_cstr(":="), &len);
	i = 0;
	while (i < len)
	{
		printf("%.*s\n", (int)strings[i].len, strings[i].ptr);
		i++;
	}
	free(strings);
	return (0);
}
