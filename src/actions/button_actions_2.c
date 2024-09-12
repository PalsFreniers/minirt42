#include <actions/buttons_actions.h>
#include <stdbool.h>
#include <ui/window.h>

void	page_prev(struct s_mlx *mlx)
{
	mlx->page -= 1;
	if (mlx->page < 0)
		mlx->page = 0;
	button_list(mlx);
}

void	page_next(struct s_mlx *mlx)
{
	mlx->page += 1;
	if (mlx->page > (int)(mlx->scene.len + 1) >> 4)
		mlx->page = (mlx->scene.len + 1) >> 4;
	button_list(mlx);
}

void	button_scene_list_populate(struct s_mlx *mlx, int base, int start)
{
	int	number;

	number = (mlx->scene.len + 1) - start;
	if (number > 16)
		number = 16;
	if (start != 0)
		start--;
	set_list_button(mlx, start, base, number);
	mlx->btn_count = number;
}

void	button_list(struct s_mlx *mlx)
{
	button_scene_reset(mlx);
	mlx->interface_buttons[0] = button_new(20, WIN_HEIGHT - 40, 20, 20);
	button_set(&(mlx->interface_buttons[0]), "<", mlx, (t_button_f)page_prev);
	mlx->interface_buttons[1] = button_new(WIN_WIDTH - 40, WIN_HEIGHT - 40, 20,
			20);
	button_set(&(mlx->interface_buttons[1]), ">", mlx, (t_button_f)page_next);
	mlx->interface_numpad[0] = numpad_new(&(mlx->page), true, WIN_WIDTH / 2
			- 25, WIN_HEIGHT - 40);
	button_scene_list_populate(mlx, mlx->page == 0, mlx->page * 16);
	mlx->btn_count += 2;
        mlx->pad_count = 1;
}
