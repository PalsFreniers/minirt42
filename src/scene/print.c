#include <object/objects.h>
#include <scene/scene.h>
#include <stdio.h>

static void	print_objects(struct s_scene scene)
{
	size_t	i;

	i = 0;
	while (i < scene.len)
	{
		if (scene.objects[i]->type == OBJ_LIGHT)
			print_light((void *)scene.objects[i]);
		if (scene.objects[i]->type == OBJ_SPHERE)
			print_sphere((void *)scene.objects[i]);
		if (scene.objects[i]->type == OBJ_PLANE)
			print_plane((void *)scene.objects[i]);
		if (scene.objects[i]->type == OBJ_CYLINDER)
			print_cylinder((void *)scene.objects[i]);
		i++;
	}
}

void	print_scene(struct s_scene *scene)
{
	printf("struct scene => {\n");
	printf("\tambient light => {\n");
	print_float("\t\t", "brigtness", scene->ambient.ratio);
	print_color("\t\t", scene->ambient.color);
	printf("\t}\n");
	printf("\tcamera => {\n");
	print_float("\t\t", "fov", scene->camera.fov);
	print_vec3("\t\t", "direction", scene->camera.direction);
	print_vec3("\t\t", "position", scene->camera.position);
	printf("\t}\n");
	printf("\tobjects => [\n");
	print_objects(*scene);
	printf("\t]\n");
	printf("}\n");
}
