/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:29:07 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/29 18:22:57 by maamine          ###   ########.fr       */
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

static uint8_t	clamped_float_to_uint8(float f)
{
	if (f > MAX_U8)
		return (MAX_U8);
	else
		return (f);
}

mlx_color	render_to_mlx_color(t_render_color color)
{
	mlx_color	ret_color;

	ret_color.a = MAX_U8;
	ret_color.r = clamped_float_to_uint8(color.r);
	ret_color.g = clamped_float_to_uint8(color.g);
	ret_color.b = clamped_float_to_uint8(color.b);
	return (ret_color);
}
