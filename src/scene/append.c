#include "object/objects.h"
#include <libft.h>
#include <scene/scene.h>

static bool	scene_grow(struct s_scene *scene)
{
	if (scene->capacity == 0)
	{
		scene->objects = ft_calloc(1, sizeof(struct s_object *));
		if (!scene->objects)
			return (false);
		scene->capacity = 1;
		return (true);
	}
	scene->capacity *= 2;
	scene->objects = (void *)ft_realloc((char *)scene->objects, (scene->capacity
				/ 2) * sizeof(struct s_object *), scene->capacity
			* sizeof(struct s_object *));
	if (!scene->objects)
	{
		scene->capacity = 0;
		return (false);
	}
	return (true);
}

bool	scene_append(struct s_scene *scene, struct s_object *obj)
{
	if (scene->capacity <= scene->len)
		if (!scene_grow(scene))
			return (false);
	scene->objects[scene->len] = obj;
	scene->len++;
	return (true);
}
