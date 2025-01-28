/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:50 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:22:09 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <stdio.h>

void	print_sphere(struct s_sphere *sphere)
{
	printf("\t\tsphere => {\n");
	print_vec3("\t\t\t", "position", sphere->base.position);
	print_color("\t\t\t", sphere->base.color);
	print_float("\t\t\t", "diameter", sphere->diameter);
	printf("\t\t}\n");
}
