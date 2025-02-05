/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:29:07 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 02:45:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

mlx_color	rgb_to_mlx_color(union u_color color)
{
	return ((mlx_color){
		.a = MAX_U8,
		.r = color.r,
		.g = color.g,
		.b = color.b,
	});
}

t_render_color	rgb_to_render_color(union u_color color)
{
	return ((t_render_color){
		.r = color.r,
		.g = color.g,
		.b = color.b,
	});
}

static uint8_t	ease_out(float f)
{
	float	sigmoid;

	f *= EASE_OUT_ATTENUATION;
	sigmoid = 1 / (1 + expf(-f));
	return ((2 * sigmoid - 1) * MAX_U8);
}

mlx_color	render_to_mlx_color(t_render_color color)
{
	return ((mlx_color){
		.a = MAX_U8,
		.r = ease_out(color.r),
		.g = ease_out(color.g),
		.b = ease_out(color.b),
	});
}
