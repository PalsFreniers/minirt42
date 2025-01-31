/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:06:50 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 15:27:52 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <mlx/mmlx.h>

void	update_buttons_click(int e, struct s_mlx *mlx);
void	update_buttons_unclick(int e, struct s_mlx *mlx);
int		win_close(int e, struct s_mlx *mlx);
void	loop_draw_ui(struct s_mlx *mlx);
int		key_event(int key, struct s_mlx *mlx);

int		camera_move(int key, struct s_mlx *mlx);

#endif // HOOKS_H
