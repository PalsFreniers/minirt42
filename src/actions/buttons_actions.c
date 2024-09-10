#include "mlx/mmlx.h"
#include "ui/buttons.h"
#include <actions/buttons_actions.h>
#include <mlx/hooks.h>

void	button_quit(struct s_mlx *mlx)
{
	win_close(0, mlx);
}

void	button_scene_reset(struct s_mlx *mlx)
{
	mlx->btn_count = 0;
	mlx->pad_count = 0;
}

void	button_add_scene(struct s_mlx *mlx)
{
	button_scene_reset(mlx);
	mlx->interface_buttons[0] = button_new(100, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[0]), "sphere", mlx,
		(t_button_f)button_add_sphere);
	mlx->interface_buttons[1] = button_new(250, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[1]), "light", mlx,
		(t_button_f)button_add_light);
	mlx->interface_buttons[2] = button_new(400, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[2]), "plane", mlx,
		(t_button_f)button_add_plane);
	mlx->interface_buttons[3] = button_new(250, BASE_LINE_Y + 110, 100, 60);
	button_set(&(mlx->interface_buttons[3]), "cylinder", mlx,
		(t_button_f)button_add_cylinder);
	mlx->btn_count = 4;
}
