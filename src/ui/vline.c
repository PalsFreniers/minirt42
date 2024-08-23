#include <mlx.h>
#include <ui/vline.h>
#include <ui/window.h>

void	vline_print(struct s_mlx *mlx, struct s_vline v, int color)
{
	int	tmp;
	int	i;

	if (v.y1 > v.y2)
	{
		tmp = v.y1;
		v.y1 = v.y2;
		v.y2 = tmp;
	}
	i = v.y1;
	while (i < v.y2)
	{
		if (i < WIN_HEIGHT && i >= 0)
			mlx_pixel_put(mlx->mlx, mlx->win, v.x, i, color);
		i++;
	}
}

void	hline_print(struct s_mlx *mlx, struct s_vline v, int color)
{
	int	tmp;
	int	i;

	if (v.y1 > v.y2)
	{
		tmp = v.y1;
		v.y1 = v.y2;
		v.y2 = tmp;
	}
	i = v.y1;
	while (i < v.y2)
	{
		if (i < WIN_WIDTH && i >= 0)
			mlx_pixel_put(mlx->mlx, mlx->win, i, v.x, color);
		i++;
	}
}
