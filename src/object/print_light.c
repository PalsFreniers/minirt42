#include <object/objects.h>
#include <stdio.h>

void	print_light(struct s_light *light)
{
	printf("\t\tlight => {\n");
	print_vec3("\t\t\t", "position", light->base.position);
	print_color("\t\t\t", light->base.color);
	print_float("\t\t\t", "britness", light->ratio);
	printf("\t\t}\n");
}
