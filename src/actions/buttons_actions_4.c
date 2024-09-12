#include <actions/buttons_actions.h>
#include <fcntl.h>
#include <ui/window.h>
#include <unistd.h>

void	compute_color(int c, char ret[3])
{
	ret[0] = (c >> (8 * 2)) & 0xFF;
	ret[1] = (c >> (8 * 1)) & 0xFF;
	ret[2] = (c >> (8 * 0)) & 0xFF;
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
	write(fd, "P6\n800 600 255\n", 15);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			compute_color(mlx_get_image_pixel(mlx->mlx, mlx->ray_img, x, y), c);
			write(fd, c, 3);
			x++;
		}
		y++;
	}
	close(fd);
}
