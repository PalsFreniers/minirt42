#include "ui/buttons.h"
#include <actions/buttons_actions.h>
#include <libft.h>
#include <mlx/mmlx.h>
#include <scene/scene.h>
#include <ui/window.h>

void	mlx_init_static_button(struct s_mlx *mlx)
{
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
	mlx->static_b[4] = button_new(400, 0, 100, 50);
	button_set(&(mlx->static_b[4]), "list", mlx, (t_button_f)button_list);
	mlx->static_b[5] = button_new(500, 0, 100, 50);
	button_set(&(mlx->static_b[5]), "screen", mlx, (t_button_f)button_screen);
}

void	set_window_position(struct s_mlx *mlx)
{
	int	w;
	int	h;

	mlx_get_screens_size(mlx->mlx, mlx->win, &w, &h);
	w /= 2;
	h = (h - WIN_HEIGHT) / 2;
	mlx_set_window_position(mlx->mlx, mlx->ray, w - WIN_WIDTH, h);
	mlx_set_window_position(mlx->mlx, mlx->win, w, h);
}

bool	init_mlx(struct s_mlx *mlx)
{
	ft_bzero(mlx, sizeof(struct s_mlx) - sizeof(struct s_scene));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->ray = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt render");
	if (!mlx->ray)
		return (false);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "minirt panel");
	if (!mlx->win)
		return (false);
	mlx->ray_img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->ray_img)
		return (false);
	mlx->ray_back = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->ray_back)
		return (false);
	set_window_position(mlx);
	mlx_init_static_button(mlx);
	return (true);
}

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->mlx)
		return ;
	if (mlx->ray_img)
		mlx_destroy_image(mlx->mlx, mlx->ray_img);
	if (mlx->ray_back)
		mlx_destroy_image(mlx->mlx, mlx->ray_back);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->ray)
		mlx_destroy_window(mlx->mlx, mlx->ray);
	mlx_destroy_display(mlx->mlx);
	ft_free("c", &(mlx->scene));
}

void	mlx_swap_ray_buffer(struct s_mlx *mlx)
{
	void	*tmp;

	tmp = mlx->ray_back;
	mlx->ray_back = mlx->ray_img;
	mlx->ray_img = tmp;
}
