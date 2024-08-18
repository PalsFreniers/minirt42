#include <object/objects.h>
#include <stdio.h>

void	print_cylinder(struct s_cylinder *cylinder)
{
	printf("\t\tcylinder => {\n");
	print_vec3("\t\t\t", "position", cylinder->base.position);
	print_color("\t\t\t", cylinder->base.color);
	print_vec3("\t\t\t", "axis", cylinder->axis);
	print_float("\t\t\t", "diameter", cylinder->diameter);
	print_float("\t\t\t", "height", cylinder->height);
	printf("\t\t}\n");
}
