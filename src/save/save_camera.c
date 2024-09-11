#include <save/save.h>
#include <stdbool.h>
#include <unistd.h>

bool	save_camera(struct s_camera *self, int fd)
{
	write(fd, "C ", 2);
	if (!save_vec3(self->position, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_vec3(self->orientation, fd))
		return (false);
	write(fd, " ", 1);
	if (!save_float(self->fov, fd))
		return (false);
	write(fd, "\n", 1);
	return (true);
}
