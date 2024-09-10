
#include "object/objects.h"
#include "scene/scene.h"
#include <actions/buttons_actions.h>
#include <mlx/mmlx.h>

void	button_scene_modify_cylinder(struct s_mlx *mlx, int index)
{
	button_scene_reset(mlx);
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.x), "axis x");
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y + 50},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.y), "axis y");
	button_scene_modify_float_1_1(mlx, (struct s_vec2i){100, BASE_LINE_Y + 100},
		&(((struct s_plane *)mlx->scene.objects[index])->normal.z), "axis z");
	button_scene_modify_float_full(mlx, (struct s_vec2i){300, BASE_LINE_Y
		+ 150}, &(((struct s_plane *)mlx->scene.objects[index])->normal.z),
		"diameter");
	button_scene_modify_float_full(mlx, (struct s_vec2i){160, BASE_LINE_Y
		+ 150}, &(((struct s_plane *)mlx->scene.objects[index])->normal.z),
		"height");
	button_scene_modify_color(mlx, (struct s_vec2i){240, BASE_LINE_Y},
		&(mlx->scene.objects[index]->color));
	button_scene_modify_vec3(mlx, (struct s_vec2i){380, BASE_LINE_Y},
		&(mlx->scene.objects[index]->position));
}

void	button_add_cylinder(struct s_mlx *mlx)
{
	struct s_object	*new;

	new = object_new(sizeof(struct s_cylinder), OBJ_CYLINDER);
	if (!new)
		return ;
	scene_append(&(mlx->scene), new);
	button_scene_modify_cylinder(mlx, mlx->scene.len - 1);
}
