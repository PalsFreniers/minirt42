/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:44 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:26:33 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <stdio.h>

void	print_cylinder(struct s_cylinder *cylinder)
{
	printf("\t\tcylinder => {\n");
	print_vec3("\t\t\t",	"position",	cylinder->base.position);
	print_color("\t\t\t", 				cylinder->base.color);
	print_vec3("\t\t\t",	"axis",		cylinder->axis);
	print_float("\t\t\t",	"diameter",	cylinder->diameter);
	print_float("\t\t\t",	"height",	cylinder->height);
	printf("\t\t}\n");
}
