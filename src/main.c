/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:30 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/19 19:54:33 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <files/files.h>
#include <libft.h>
#include <logger/logger.h>
#include <mlx.h>
#include <parsing/obey.h>
#include <parsing/parse.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings/dstring.h>
#include <ui/buttons.h>
#include <ui/window.h>

struct				s_mlx
{
	void			*mlx;
	void			*win;
	struct s_scene	*scene;
	bool			redraw;
	struct s_button	static_b[1];
};

typedef int			(*t_mlx_e_f)(int, void *);
typedef int			(*t_mlx_l_f)(void *);

void	update_mlx(struct s_mlx *mlx)
{
	if (mlx->redraw)
	{
		mlx->redraw = false;
		button_draw(mlx->mlx, mlx->win, &(mlx->static_b[0]));
	}
}

void	update_buttons_click(int e, struct s_mlx *mlx)
{
	(void)e;
	button_update(mlx->mlx, &(mlx->static_b[0]));
}

void	update_buttons_unclick(int e, struct s_mlx *mlx)
{
	(void)e;
	button_unclick(&(mlx->static_b[0]));
}

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
		.text = "print scene",
		.data = scene,
		.on_click = (t_button_f)print_scene,
		.color = 0xFFAAAAAA,
		.tcolor = 0xFF0000FF,
	};
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

void	register_free_funcs(void)
{
	ft_free_register('s', (t_free_function)string_destroy);
	ft_free_register('p', (t_free_function)free);
	ft_free_register('c', (t_free_function)free_scene);
	ft_free_register('m', (t_free_function)free_mlx);
}

int	win_close(int e, struct s_mlx *mlx)
{
	if (e == 0)
		mlx_loop_end(mlx->mlx);
	return (0);
}

int	main(int c, char **args)
{
	struct s_scene	scene;
	struct s_mlx	mlx;

	register_free_funcs();
	if (c != 2)
	{
		logger_error("usage: %s <path/to/file.rt>", args[0]);
		return (1);
	}
	if (!parse_file(args[1], &scene, args[0]))
	{
		free_scene(&scene);
		return (1);
	}
	if (!init_mlx(&mlx, &scene))
	{
		ft_free("cm", &scene, &mlx);
		return (1);
	}
	print_scene(&scene);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, (t_mlx_e_f)win_close,
		&mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_MOUSEDOWN,
		(t_mlx_e_f)update_buttons_click, &mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_MOUSEUP,
		(t_mlx_e_f)update_buttons_unclick, &mlx);
	mlx_loop_hook(mlx.mlx, (t_mlx_l_f)update_mlx, &mlx);
	mlx_loop(mlx.mlx);
	ft_free("cm", &scene, &mlx);
	return (0);
}
