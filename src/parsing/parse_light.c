#include "object/objects.h"
#include <logger/logger.h>
#include <parsing/parse.h>

bool	parse_light(struct s_string *parts, size_t count, struct s_scene *scene)
{
	struct s_light	*light;

	if (count != 4)
	{
		logger_error("unable to parse light");
		return (false);
	}
	light = (struct s_light *)object_new(sizeof(struct s_light), OBJ_LIGHT);
	if (!scene_append(scene, (struct s_object *)light))
		return (false);
	if (!parse_position(parts[1], &(light->base.position)))
		return (false);
	if (!parse_range(parts[2], &(light->ratio), 1, 0))
		return (false);
	if (!parse_color(parts[3], &(light->base.color)))
		return (false);
	return (true);
}
