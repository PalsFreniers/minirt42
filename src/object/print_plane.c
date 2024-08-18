#include <object/objects.h>
#include <stdio.h>

void	print_plane(struct s_plane *plane)
{
	printf("\t\tplane => {\n");
	print_vec3("\t\t\t", "position", plane->base.position);
	print_color("\t\t\t", plane->base.color);
	print_vec3("\t\t\t", "normal", plane->normal);
	printf("\t\t}\n");
}
