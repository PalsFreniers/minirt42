#include <save/save.h>
#include <unistd.h>

bool	save_vec3(struct s_vec3 vec, int fd)
{
	if (!save_float(vec.x, fd))
		return (false);
	write(fd, ",", 1);
	if (!save_float(vec.y, fd))
		return (false);
	write(fd, ",", 1);
	if (!save_float(vec.z, fd))
		return (false);
	return (true);
}
