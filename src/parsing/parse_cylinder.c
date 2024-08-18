#include "object/objects.h"
#include <logger/logger.h>
#include <parsing/parse.h>

static bool	parse_cylinder_floats(struct s_string *parts,
		struct s_cylinder *cylinder)
{
	if (!parse_float(parts[3], &(cylinder->diameter)))
		return (false);
	if (cylinder->diameter <= 0)
	{
		logger_error("cylinders diameter can't be zero or negative");
		return (false);
	}
	if (!parse_float(parts[4], &(cylinder->height)))
		return (false);
	if (cylinder->height <= 0)
	{
		logger_error("cylinders height can't be zero or negative");
		return (false);
	}
	return (true);
}

bool	parse_cylinder(struct s_string *parts, size_t count,
		struct s_scene *scene)
{
	struct s_cylinder	*cylinder;

	if (count != 6)
	{
		logger_error("unable to parse cylinder");
		return (false);
	}
	cylinder = (void *)object_new(sizeof(struct s_cylinder), OBJ_CYLINDER);
	if (!scene_append(scene, (struct s_object *)cylinder))
		return (false);
	if (!parse_position(parts[1], &(cylinder->base.position)))
		return (false);
	if (!parse_ranged_vector(parts[2], &(cylinder->axis), 1, -1))
		return (false);
	if (!parse_cylinder_floats(parts, cylinder))
		return (false);
	if (!parse_color(parts[5], &(cylinder->base.color)))
		return (false);
	return (true);
}
