/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:02:02 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 03:26:52 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object/objects.h>
#include <scene/scene.h>
#include <stdio.h>

static void	print_objects(struct s_scene scene)
{
	for (size_t i = 0; i < scene.len; i++)
	{
		switch (scene.objects[i]->type)
		{
		case OBJ_LIGHT:
			print_light((struct s_light *)scene.objects[i]);
			break;

		case OBJ_SPHERE:
			print_sphere((struct s_sphere *)scene.objects[i]);
			break;

		case OBJ_PLANE:
			print_plane((struct s_plane *)scene.objects[i]);
			break;

		case OBJ_CYLINDER:
			print_cylinder((struct s_cylinder *)scene.objects[i]);
			break;

		default:
			break;
		}
	}
}

void	print_scene(struct s_scene *scene)
{
	printf("struct scene => {\n");
	printf("\tambient light => {\n");
	print_float("\t\t",	"brigtness",	scene->ambient.ratio);
	print_color("\t\t",					scene->ambient.color);
	printf("\t}\n");
	printf("\tcamera => {\n");
	print_float("\t\t",	"fov",			scene->camera.fov);
	print_vec3("\t\t",	"direction",	scene->camera.direction);
	print_vec3("\t\t",	"position",		scene->camera.position);
	printf("\t}\n");
	printf("\tobjects => [\n");
	print_objects(*scene);
	printf("\t]\n");
	printf("}\n");
}
