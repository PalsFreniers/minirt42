#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_light(struct s_light *self, int fd)
{
	write(fd, "L ", 2);
	if (!save_vec3(self->base.position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->ratio, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_color(self->base.color, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
