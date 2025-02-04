/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:32:39 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 00:00:11 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <actions/buttons_actions.h>
#include <fcntl.h>
#include <ui/window.h>
#include <unistd.h>

float	float_step(float val, bool is_left_click, int sign)
{
	float	step;

	step = (OFFSET_SMALL);
	if (is_left_click)
		step = 0.1f;
	return (val + step * sign);
}

void	compute_color(mlx_color c, char ret[3])
{
	ret[0] = c.r;
	ret[1] = c.g;
	ret[2] = c.b;
}

void	button_screen(struct s_mlx *mlx)
{
	int		fd;
	int		y;
	int		x;
	char	c[3];

	fd = open("screen.ppm", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		return ;
	write(fd, "P6\n900 600 255\n", 15);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			compute_color(mlx_get_image_pixel(mlx->context, mlx->img, x, y), c);
			write(fd, c, 3);
			x++;
		}
		y++;
	}
	close(fd);
}
