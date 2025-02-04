/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmlx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:07:03 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 00:20:07 by maamine          ###   ########.fr       */
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

enum	e_mouse_buttons
{
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

enum	e_key_codes
{
	KEY_ESCAPE		= 41,
	KEY_ENTER		= 40,
	KEY_W			= 26,
	KEY_A			= 4,
	KEY_S			= 22,
	KEY_D			= 7,
	KEY_Q			= 20,
	KEY_E			= 8,
	KEY_NUM_5		= 93,
	KEY_NUM_MINUS	= 86,
	KEY_NUM_PLUS	= 87,
};

struct						s_window
{
	mlx_window				win;
	mlx_window_create_info	info;
};

enum	e_render_mode
{
	RENDER_DEFAULT	= 0,
	RENDER_Z_BUFFER	= 0b01,
	RENDER_GRAD		= 0b10,
};

struct					s_render
{
	struct s_window		window;
	mlx_image			img;
	enum e_render_mode	mode;
	int					down_sizing
};

struct				s_ui
{
	struct s_window	window;
	struct s_button	static_b[6];
	struct s_button	interface_buttons[33];
	int				btn_count;
	struct s_numpad	interface_numpad[11];
	int				pad_count;
	int				page;
};

struct				s_mlx
{
	mlx_context		context;
	struct s_render	renderer;
	struct s_ui		ui;
	struct s_scene	scene;
};

typedef void		(*t_mlx_e_f)(int, void *);
typedef void		(*t_mlx_l_f)(void *);

bool				init_mlx(struct s_mlx *mlx);
void				free_mlx(struct s_mlx *mlx);

#endif // MMLX_H
