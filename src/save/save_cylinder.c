#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_cylinder(struct s_cylinder *self, int fd)
{
	write(fd, "cy ", 3);
	if (!save_vec3(self->base.position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_vec3(self->axis, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->diameter, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->height, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_color(self->base.color, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
