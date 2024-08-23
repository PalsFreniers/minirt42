#include <libft.h>
#include <stdbool.h>
#include <stdio.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>
#include <mlx/mmlx.h>

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
	if (collide((int [4]){x, y, 2, 2}, rect))
	{
		b->is_clicked = true;
		b->on_click(b->data);
	}
}

void	button_unclick(struct s_button *b)
{
	b->is_clicked = false;
}

void	button_draw(struct s_mlx *mlx, struct s_button *b)
{
	int	x;
	int	y;

	x = b->x + b->width / 2 - ((ft_strlen(b->text) * PPC) / 2);
	y = b->y + b->height / 2 - (PPC / 2) + PPC - 2;
	mlx_string_put(mlx->mlx, mlx->win, x, y, TEXTC, b->text);
	vline_print(mlx, (struct s_vline){b->x, b->y, b->y + b->height}, BORDERC);
	vline_print(mlx, (struct s_vline){b->x + b->width, b->y, b->y + b->height},
		BORDERC);
	hline_print(mlx, (struct s_vline){b->y, b->x, b->x + b->width}, BORDERC);
	hline_print(mlx, (struct s_vline){b->y + b->height, b->x, b->x + b->width},
		BORDERC);
}
