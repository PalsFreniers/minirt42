#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_ambient_light(struct s_ambient *self, int fd)
{
	write(fd, "A ", 2);
	if (!save_float(self->ratio, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_color(self->color, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
