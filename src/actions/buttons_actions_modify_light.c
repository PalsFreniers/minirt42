#include "object/objects.h"
#include "scene/scene.h"
#include <mlx/mmlx.h>
#include <actions/buttons_actions.h>

void	button_scene_modify_light(struct s_mlx *mlx, int index)
{
	button_scene_reset(mlx);
	button_scene_modify_float_0_1(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(((struct s_sphere *)mlx->scene.objects[index])->diameter), "ratio");
	button_scene_modify_color(mlx, (struct s_vec2i){220, BASE_LINE_Y},
		&(mlx->scene.objects[index]->color));
}

void	button_add_light(struct s_mlx *mlx)
{
	struct s_object	*new;

	new = object_new(sizeof(struct s_light), OBJ_LIGHT);
	if (!new)
		return ;
	scene_append(&(mlx->scene), new);
	button_scene_modify_light(mlx, mlx->scene.len - 1);
}
