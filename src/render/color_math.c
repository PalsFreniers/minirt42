/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:30:30 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/30 01:13:01 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_render_color	render_color_black(void)
{
	return ((t_render_color){
		.r = 0.0f,
		.g = 0.0f,
		.b = 0.0f,
	});
}

t_render_color	filter_color(t_render_color color, t_render_color filter)
{
	t_render_color	ret_color;

	ret_color.r = (color.r * filter.r) / 0xFF;
	ret_color.g = (color.g * filter.g) / 0xFF;
	ret_color.b = (color.b * filter.b) / 0xFF;
	return (ret_color);
}

t_render_color	color_scal_mul(t_render_color color, float f)
{
	t_render_color	ret_color;

	ret_color.r = color.r * f;
	ret_color.g = color.g * f;
	ret_color.b = color.b * f;
	return (ret_color);
}

t_render_color	color_add(t_render_color a, t_render_color b)
{
	t_render_color	color;

	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;
	return (color);
}
