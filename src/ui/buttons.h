/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:42:46 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 01:06:36 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTONS_H
# define BUTTONS_H

# include <mlx/mmlx_sd.h>
# include <stdbool.h>
# define PPC		7
# define BORDERC	(mlx_color)				0x8888FFFF
# define BORDER2C	(mlx_color)(uint32_t)	0x2222FFFF
# define TEXTC		(mlx_color)				0xDDDDDDFF

typedef void	(*t_button_f)	(void *, bool);
typedef void	(*t_button_i_f)	(void *, int, bool);

struct		s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
};

struct					s_button
{
	struct s_rect	rect;
	char			*text;
	void			*data;
	int				data_index;
	bool			is_clicked;
	union
	{
		t_button_f		on_click;
		t_button_i_f	on_click_idx;
	};
	bool			has_idx;
};

void				button_update(struct s_mlx *mlx, struct s_button *b, bool is_left_click);
void				button_draw(struct s_mlx *mlx, struct s_button *b);
struct s_button		button_new(int x, int y, int width, int height);
void				button_set(struct s_button *self, char *text, void *data, t_button_f func);
void				button_set_index(struct s_button *self, int index);
#endif // BUTTONS_H
