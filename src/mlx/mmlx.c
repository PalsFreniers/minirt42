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

	mlx_get_screen_size(mlx->mlx, mlx->win.win, &w, &h);
	w /= 2;
	h = (h - WIN_HEIGHT) / 2;
	mlx_set_window_position(mlx->mlx, mlx->ray.win, w - WIN_WIDTH, h);
	mlx_set_window_position(mlx->mlx, mlx->win.win, w, h);
}

mlx_window_create_info	create_info(mlx_image render_target, const char *title)
{
	return ((mlx_window_create_info){
		.render_target = render_target,
		.title = title,
		.width = WIN_WIDTH,
		.height = WIN_HEIGHT,
		.is_fullscreen = false,
		.is_resizable = false,
	});
}

bool	init_mlx(struct s_mlx *mlx)
{
	// ft_bzero(mlx, sizeof(struct s_mlx) - sizeof(struct s_scene));
	ft_bzero(mlx, sizeof(struct s_mlx));
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (false);
	mlx->ray.info = create_info(0x0, "minirt render");
	mlx->ray.win = mlx_new_window(mlx->mlx, &mlx->ray.info);
	if (!mlx->ray.win)
		return (false);
	mlx->win.info = create_info(0x0, "minirt panel");
	mlx->win.win = mlx_new_window(mlx->mlx, &mlx->win.info);
	if (!mlx->win.win)
		return (false);
	mlx->ray_img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->ray_img)
		return (false);
	mlx->ray_back = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->ray_back)
		return (false);
	set_window_position(mlx);
	mlx_init_static_button(mlx);
	mlx->down_sizing = 1;
	return (true);
}

// bool	init_mlx(struct s_mlx *mlx)
// {
// 	// ft_bzero(mlx, sizeof(struct s_mlx) - sizeof(struct s_scene));
// 	ft_bzero(mlx, sizeof(struct s_mlx));
// 	mlx->mlx = mlx_init();
// 	if (!mlx->mlx)
// 		return (false);
// 	mlx->ray_img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!mlx->ray_img)
// 		return (false);
// 	mlx->ray.info = create_info(mlx->ray_img, "minirt render");
// 	mlx->ray.win = mlx_new_window(mlx->mlx, &mlx->ray.info);
// 	if (!mlx->ray.win)
// 		return (false);
// 	mlx->win.info = create_info(0x0, "minirt panel");
// 	mlx->win.win = mlx_new_window(mlx->mlx, &mlx->win.info);
// 	if (!mlx->win.win)
// 		return (false);
// 	mlx->ray_back = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!mlx->ray_back)
// 		return (false);
// 	set_window_position(mlx);
// 	mlx_init_static_button(mlx);
// 	mlx->down_sizing = 1;
// 	return (true);
// }

void	free_mlx(struct s_mlx *mlx)
{
	if (!mlx->mlx)
		return ;
	if (mlx->ray_img)
		mlx_destroy_image(mlx->mlx, mlx->ray_img);
	if (mlx->ray_back)
		mlx_destroy_image(mlx->mlx, mlx->ray_back);
	if (mlx->win.win)
		mlx_destroy_window(mlx->mlx, mlx->win.win);
	if (mlx->ray.win)
		mlx_destroy_window(mlx->mlx, mlx->ray.win);
	mlx_destroy_context(mlx->mlx);
	// ft_free("c", &(mlx->scene));
}

void	mlx_swap_ray_buffer(struct s_mlx *mlx)
{
	mlx_image	tmp;

	tmp = mlx->ray_back;
	mlx->ray_back = mlx->ray_img;
	mlx->ray_img = tmp;
	mlx_put_image_to_window(mlx->mlx, mlx->ray.win, mlx->ray_img, 0, 0);
}
