/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:29:07 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/31 16:40:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

mlx_color	rgb_to_mlx_color(union u_color color)
{
	mlx_color	ret_color;

	ret_color.a = MAX_U8;
	ret_color.r = color.r;
	ret_color.g = color.g;
	ret_color.b = color.b;
	return (ret_color);
}

t_render_color	rgb_to_render_color(union u_color color)
{
	t_render_color	ret_color;

	ret_color.r = color.r;
	ret_color.g = color.g;
	ret_color.b = color.b;
	return (ret_color);
}

static uint8_t	ease_out(float f)
{
	float	sigmoid;

	f *= EASE_OUT_ATTENUATION;
	sigmoid = 1 / (1 + expf(-f));
	sigmoid = 2 * sigmoid - 1;
	return (sigmoid * MAX_U8);
}

mlx_color	render_to_mlx_color(t_render_color color)
{
	mlx_color	ret_color;

	ret_color.a = MAX_U8;
	ret_color.r = ease_out(color.r);
	ret_color.g = ease_out(color.g);
	ret_color.b = ease_out(color.b);
	return (ret_color);
}
