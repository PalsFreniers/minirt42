#include <object/objects.h>
#include <stdio.h>

void	print_vec3(char *tabs, char *name, struct s_vec3 vec)
{
	printf("%s%s => {%f, %f, %f};\n", tabs, name, vec.x, vec.y, vec.z);
}

void	print_color(char *tabs, union u_color c)
{
	printf("%scolor => 0x%x {%d, %d, %d};\n", tabs, c.rgb, c.r, c.g, c.b);
}

void	print_float(char *tabs, char *name, float value)
{
	printf("%s%s => %f;\n", tabs, name, value);
}
