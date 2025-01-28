/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:29:07 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:29:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

mlx_color	rgb_to_mlx_color(union u_color color)
{
	mlx_color	ret_color;

	ret_color.a = 0xFF;
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

mlx_color	render_to_mlx_color(t_render_color color)
{
	mlx_color	ret_color;

	ret_color.a = 0xFF;
	if (color.r > 0xFF)
		ret_color.r = 0xFF;
	else
		ret_color.r = color.r;
	if (color.g > 0xFF)
		ret_color.g = 0xFF;
	else
		ret_color.g = color.g;
	if (color.b > 0xFF)
		ret_color.b = 0xFF;
	else
		ret_color.b = color.b;
	return (ret_color);
}
