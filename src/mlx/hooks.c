#include <mlx/hooks.h>
#include <stdio.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>

void	update_buttons_click(int e, struct s_mlx *mlx)
{
	int	x;

	(void)e;
	button_update(mlx->mlx, &(mlx->static_b[0]));
	button_update(mlx->mlx, &(mlx->static_b[1]));
	x = 0;
	while (x < mlx->btn_count)
	{
		button_update(mlx->mlx, &(mlx->interface_buttons[x]));
		x++;
	}
}

void	update_buttons_unclick(int e, struct s_mlx *mlx)
{
	int	x;

	(void)e;
	button_unclick(&(mlx->static_b[0]));
	button_unclick(&(mlx->static_b[1]));
	x = 0;
	while (x < mlx->btn_count)
	{
		button_unclick(&(mlx->interface_buttons[x]));
		x++;
	}
}

int	win_close(int e, struct s_mlx *mlx)
{
	if (e == 0)
		mlx_loop_end(mlx->mlx);
	return (0);
}

void	loop_draw_ui(struct s_mlx *mlx)
{
	int	x;

	if (mlx->redraw)
	{
		mlx->redraw = false;
		button_draw(mlx, &(mlx->static_b[0]));
		button_draw(mlx, &(mlx->static_b[1]));
		x = 0;
		while (x < mlx->btn_count)
		{
			button_draw(mlx, &(mlx->interface_buttons[x]));
			x++;
		}
	}
}

int	key_event(int key, struct s_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		return (win_close(0, mlx));
	return (0);
}
