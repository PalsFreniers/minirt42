/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:30:30 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/05 02:42:57 by maamine          ###   ########.fr       */
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
	return ((t_render_color){
		.r = (color.r * filter.r) / MAX_U8,
		.g = (color.g * filter.g) / MAX_U8,
		.b = (color.b * filter.b) / MAX_U8,
	});
}

t_render_color	color_scal_mul(t_render_color color, float f)
{
	return ((t_render_color){
		.r = color.r * f,
		.g = color.g * f,
		.b = color.b * f,
	});
}

t_render_color	color_add(t_render_color a, t_render_color b)
{
	return ((t_render_color){
		.r = a.r + b.r,
		.g = a.g + b.g,
		.b = a.b + b.b,
	});
}
