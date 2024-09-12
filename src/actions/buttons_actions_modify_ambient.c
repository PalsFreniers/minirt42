#include "scene/scene.h"
#include <actions/buttons_actions.h>
#include <mlx/mmlx.h>

void	button_scene_modify_ambient(struct s_mlx *mlx, int index)
{
	(void)index;
	button_scene_reset(mlx);
	button_scene_modify_float_0_1(mlx, (struct s_vec2i){100, BASE_LINE_Y},
		&(mlx->scene.ambient.ratio), "ratio");
	button_scene_modify_color(mlx, (struct s_vec2i){240, BASE_LINE_Y},
		&(mlx->scene.ambient.color));
}
