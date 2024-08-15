#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

bool	parse_camera(struct s_string *parts, size_t count,
		struct s_camera *camera)
{
	if (count != 4)
	{
		logger_error("unable to parse camera");
		ft_free("p", parts);
		return (false);
	}
	if (!parse_position(parts[1], &(camera->position)))
	{
		ft_free("p", parts);
		return (false);
	}
	if (!parse_ranged_vector(parts[2], &(camera->orientation), 1, -1))
	{
		ft_free("p", parts);
		return (false);
	}
	if (!parse_range(parts[3], &(camera->fov), 180, 0))
	{
		ft_free("p", parts);
		return (false);
	}
	ft_free("p", parts);
	return (true);
}
