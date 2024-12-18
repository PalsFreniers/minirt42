/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:16:46 by maamine           #+#    #+#             */
/*   Updated: 2024/12/18 17:25:39 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <mlx/mmlx.h>
# include <render/collision.h>

typedef union u_acolor
{
	uint32_t		argb;
	struct
	{
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
		uint8_t		a;
	};
}					t_acolor;

void		loop_render(struct s_mlx *mlx);

t_acolor	rgb_to_rgba(t_color color);
t_acolor	filter_acolor(t_acolor light, t_acolor filter);
t_acolor	blend_acolor(t_acolor a, t_acolor b);
t_acolor	get_light_acolor(struct s_mlx *mlx);
t_acolor	lit_color(struct s_mlx *mlx, t_collision *collision);

#endif // RENDER_H
