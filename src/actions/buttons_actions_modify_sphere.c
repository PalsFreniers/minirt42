#include "object/objects.h"
#include "scene/scene.h"
#include <actions/buttons_actions.h>
#include <mlx/mmlx.h>

void	button_scene_modify_sphere(struct s_mlx *mlx, int index)
{
	button_scene_reset(mlx);
	button_scene_modify_float(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(((struct s_sphere *)mlx->scene.objects[index])->diameter),
		"diameter");
	button_scene_modify_color(mlx, (struct s_vec2i){240, BASE_LINE_Y},
		&(mlx->scene.objects[index]->color));
	button_scene_modify_vec3(mlx, (struct s_vec2i){380, BASE_LINE_Y},
		&(mlx->scene.objects[index]->position));
}

void	button_add_sphere(struct s_mlx *mlx)
{
	struct s_object	*new;

	new = object_new(sizeof(struct s_sphere), OBJ_SPHERE);
	if (!new)
		return ;
	scene_append(&(mlx->scene), new);
	button_scene_modify_sphere(mlx, mlx->scene.len - 1);
}
