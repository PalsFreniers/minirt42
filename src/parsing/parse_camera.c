#include "strings/dstring.h"
#include <logger/logger.h>
#include <parsing/obey.h>
#include <parsing/parse.h>

static bool	parse_camera_impl(struct s_camera *camera, struct s_string *parts)
{
	if (!parse_position(parts[1], &(camera->position)))
		return (false);
	if (!parse_ranged_vector(parts[2], &(camera->orientation), 1, -1))
		return (false);
	if (!parse_range(parts[3], &(camera->fov), 180, 0))
		return (false);
	return (true);
}

bool	parse_camera(struct s_string *parts, size_t count,
		struct s_camera *camera)
{
	if (camera->exist)
	{
		logger_error("only one camera is able to exist at one time");
		return (false);
	}
	if (count != 4)
	{
		logger_error("unable to parse camera");
		return (false);
	}
	if (!parse_camera_impl(camera, parts))
		return (false);
	camera->exist = true;
	return (true);
}
