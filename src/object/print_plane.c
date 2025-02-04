/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:31 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:26:54 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <stdio.h>

void	print_plane(struct s_plane *plane)
{
	printf("\t\tplane => {\n");
	print_vec3("\t\t\t",	"position",	plane->base.position);
	print_color("\t\t\t",				plane->base.color);
	print_vec3("\t\t\t",	"normal",	plane->normal);
	printf("\t\t}\n");
}
