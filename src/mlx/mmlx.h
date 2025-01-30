/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:07:03 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:10:30 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMLX_H
# define MMLX_H

# include <mlx.h>
# include <scene/scene.h>
# include <stdbool.h>
# include <ui/buttons.h>
# include <ui/numpad.h>

# define BASE_LINE_Y 70

struct s_window
{
	mlx_window				win;
	mlx_window_create_info	info;
};

struct				s_mlx
{
	mlx_context		context;
	struct s_window	ui;
	struct s_window	render;
	mlx_image		img;
	struct s_button	static_b[6];
	struct s_button	interface_buttons[33];
	int				btn_count;
	struct s_numpad	interface_numpad[11];
	int				pad_count;
	int				page;
	int				down_sizing;
	struct s_scene	scene;
};

typedef void		(*t_mlx_e_f)(int, void *);
typedef void		(*t_mlx_l_f)(void *);

bool				init_mlx(struct s_mlx *mlx);
void				free_mlx(struct s_mlx *mlx);
void				mlx_swap_ray_buffer(struct s_mlx *mlx);

#endif // MMLX_H
