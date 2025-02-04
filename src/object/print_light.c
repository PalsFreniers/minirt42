/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:21:06 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 00:26:45 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <stdio.h>

void	print_light(struct s_light *light)
{
	printf("\t\tlight => {\n");
	print_vec3("\t\t\t",	"position",	light->base.position);
	print_color("\t\t\t",				light->base.color);
	print_float("\t\t\t",	"britness",	light->ratio);
	printf("\t\t}\n");
}
