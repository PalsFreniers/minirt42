#include "object/objects.h"
#include "scene/scene.h"
#include <actions/buttons_actions.h>
#include <mlx/mmlx.h>

void	button_scene_modify_plane(struct s_mlx *mlx, int index)
{
	button_scene_reset(mlx);
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.x), "norm x");
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y + 50},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.y), "norm y");
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y + 100},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.z), "norm z");
	button_scene_modify_color(mlx, (struct s_vec2i){240, BASE_LINE_Y},
		&(mlx->scene.objects[index]->color));
	button_scene_modify_vec3(mlx, (struct s_vec2i){380, BASE_LINE_Y},
		&(mlx->scene.objects[index]->position));
}

void	button_add_plane(struct s_mlx *mlx)
{
	struct s_object	*new;

	new = object_new(sizeof(struct s_plane), OBJ_PLANE);
	if (!new)
		return ;
	scene_append(&(mlx->scene), new);
	button_scene_modify_plane(mlx, mlx->scene.len - 1);
}
