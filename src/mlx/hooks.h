/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:06:50 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 20:29:19 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <mlx/mmlx.h>

enum	e_key_type
{
	KEY_ESCAPE = 41,
	KEY_ENTER = 40,
	KEY_W = 26,
	KEY_A = 4,
	KEY_S = 22,
	KEY_D = 7,
	KEY_Q = 20,
	KEY_E = 8,
	KEY_NUM_5 = 93,
	KEY_NUM_MINUS = 86,
	KEY_NUM_PLUS = 87,
};

void	update_buttons_click(int e, struct s_mlx *mlx);
void	update_buttons_unclick(int e, struct s_mlx *mlx);
int		win_close(int e, struct s_mlx *mlx);
void	loop_draw_ui(struct s_mlx *mlx);
int		key_event(int key, struct s_mlx *mlx);

int		camera_move(int key, struct s_mlx *mlx);

#endif // HOOKS_H
