/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:53:57 by maamine           #+#    #+#             */
/*   Updated: 2024/10/13 04:16:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

/**
 * 	loop through x, y:
 * 		draw_line			--> not hard, only depends on x, y and FOV
 * 		get_intersection	--> moves and rotates line, check with objects
 * 
 * 	get_intersection:
 * 		loop through objects:
 * 			if check_intersection:
 * 				if nearer and valid:
 * 					inters = tmp_inters
 */

void	loop_render(struct s_mlx *mlx)
{
	// int	x;
	// int	y;
	// struct s_vec3	line;
	// struct s_inters	inters;

	// y = 0;
	// while (y < 1000)
	// {
	// 	x = 0;
	// 	while (x < 1000)
	// 	{
	// 		line = draw_line(mlx, x, y);
	// 		inters = get_inters(mlx, line);
	// 		draw_pixel(inters);
	// 		x++;
	// 	}
	// 	y++;
	// }
}