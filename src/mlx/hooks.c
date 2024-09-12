#include "mlx.h"
#include <mlx/hooks.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>

void	update_buttons_click(int e, struct s_mlx *mlx)
{
	int	x;

	(void)e;
	button_update(mlx->mlx, &(mlx->static_b[0]));
	button_update(mlx->mlx, &(mlx->static_b[1]));
	button_update(mlx->mlx, &(mlx->static_b[2]));
	button_update(mlx->mlx, &(mlx->static_b[3]));
	button_update(mlx->mlx, &(mlx->static_b[4]));
	button_update(mlx->mlx, &(mlx->static_b[5]));
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
	mlx->static_b[0].is_clicked = false;
	mlx->static_b[1].is_clicked = false;
	mlx->static_b[2].is_clicked = false;
	mlx->static_b[3].is_clicked = false;
	mlx->static_b[4].is_clicked = false;
	mlx->static_b[5].is_clicked = false;
	x = 0;
	while (x < mlx->btn_count)
	{
		mlx->interface_buttons[x].is_clicked = false;
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

	mlx_clear_window(mlx->mlx, mlx->win);
	button_draw(mlx, &(mlx->static_b[0]));
	button_draw(mlx, &(mlx->static_b[1]));
	button_draw(mlx, &(mlx->static_b[2]));
	button_draw(mlx, &(mlx->static_b[3]));
	button_draw(mlx, &(mlx->static_b[4]));
	button_draw(mlx, &(mlx->static_b[5]));
	x = 0;
	while (x < mlx->btn_count)
	{
		button_draw(mlx, &(mlx->interface_buttons[x]));
		x++;
	}
	x = 0;
	while (x < mlx->pad_count)
	{
		numpad_draw(mlx, &(mlx->interface_numpad[x]));
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->ray, mlx->ray_img, 0, 0);
}

int	key_event(int key, struct s_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		return (win_close(0, mlx));
	return (0);
}
