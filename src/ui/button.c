#include <mlx.h>
#include <stdbool.h>
#include <stdio.h>
#include <ui/buttons.h>
#include <ui/window.h>

static bool	collide(int a[4], int b[4])
{
	if (a[0] + a[2] < b[0])
		return (false);
	if (a[0] > b[0] + b[2])
		return (false);
	if (a[1] + a[3] < b[1])
		return (false);
	if (a[1] > b[1] + b[3])
		return (false);
	return (true);
}

void	button_update(void *mlx, struct s_button *b)
{
	int	x;
	int	y;
	int	rect[4];

	if (b->is_clicked)
		return ;
	mlx_mouse_get_pos(mlx, &x, &y);
	rect[0] = b->x;
	rect[1] = b->y;
	rect[2] = b->width;
	rect[3] = b->height;
	if (collide((int[4]){x, y, 2, 2}, rect))
	{
		b->is_clicked = true;
		b->on_click(b->data);
	}
}

void	button_unclick(struct s_button *b)
{
	b->is_clicked = false;
}

void	button_draw(void *mlx, void *win, struct s_button *b)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < b->height)
	{
		if (y + b->y < 0 || y + b->y >= WIN_HEIGHT)
		{
			y++;
			continue ;
		}
// 		x = 0;
		while (x < b->width)
		{
			if (x + b->x < 0 || x + b->x >= WIN_WIDTH)
			{
				x++;
				continue ;
			}
			mlx_pixel_put(mlx, win, x + b->x, y + b->y, b->color);
			x++;
		}
		y++;
	}
	mlx_string_put(mlx, win, b->x + 5, b->y + 5, b->tcolor, b->text);
}
