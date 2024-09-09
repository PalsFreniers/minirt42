#include <actions/buttons_actions.h>
#include <libft.h>
#include <mlx/mmlx.h>
#include <scene/scene.h>
#include <ui/window.h>

bool	init_mlx(struct s_mlx *mlx, struct s_scene *scene)
{
	ft_bzero(mlx, sizeof(struct s_mlx));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt");
	if (!mlx->win)
		return (false);
	mlx->redraw = true;
	mlx->static_b[0] = (struct s_button){
		.x = 0,
		.y = 0,
		.width = 100,
		.height = 50,
		.text = "quit",
		.data = mlx,
		.on_click = (t_button_f)button_quit,
	};
	mlx->static_b[1] = (struct s_button){
		.x = 100,
		.y = 0,
		.width = 100,
		.height = 50,
		.text = "print scene",
		.data = scene,
		.on_click = (t_button_f)print_scene,
	};
	mlx->btn_count = 0;
	init_buttons_edit_ambiant_light(mlx);
	return (true);
}

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->mlx)
		return ;
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
}
