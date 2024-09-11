#include "ui/buttons.h"
#include <actions/buttons_actions.h>
#include <libft.h>
#include <mlx/mmlx.h>
#include <scene/scene.h>
#include <ui/window.h>

bool	init_mlx(struct s_mlx *mlx)
{
	ft_bzero(mlx, sizeof(struct s_mlx) - sizeof(struct s_scene));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt");
	if (!mlx->win)
		return (false);
	mlx->static_b[0] = button_new(0, 0, 100, 50);
	button_set(&(mlx->static_b[0]), "quit", mlx, (t_button_f)button_quit);
	mlx->static_b[1] = button_new(100, 0, 100, 50);
	button_set(&(mlx->static_b[1]), "print scene", &(mlx->scene),
		(t_button_f)print_scene);
	mlx->static_b[2] = button_new(200, 0, 100, 50);
	button_set(&(mlx->static_b[2]), "add", mlx, (t_button_f)button_add_scene);
	mlx->static_b[3] = button_new(300, 0, 100, 50);
	button_set(&(mlx->static_b[3]), "save", &(mlx->scene),
		(t_button_f)button_save);
	return (true);
}

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->mlx)
		return ;
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	ft_free("c", &(mlx->scene));
}
