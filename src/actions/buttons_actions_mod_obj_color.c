#include "object/objects.h"
#include <actions/buttons_actions.h>

void	char_inc(unsigned char *ptr)
{
	int	tmp;

	tmp = *ptr + 1;
	*ptr = tmp % 256;
}

void	char_dec(unsigned char *ptr)
{
	int	tmp;

	tmp = *ptr - 1;
	*ptr = tmp % 256;
}

void	button_scene_modify_uchar(struct s_mlx *mlx, struct s_vec2i pos,
		unsigned char *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)char_inc);
	mlx->interface_buttons[mlx->btn_count + 1] = button_new(pos.x + 20, pos.y,
		60, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2] = button_new(pos.x + 80, pos.y,
		20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)char_dec);
	mlx->interface_numpad[mlx->pad_count] = numpad_new(data, true, pos.x + 50,
		pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}

void	button_scene_modify_color(struct s_mlx *mlx, struct s_vec2i pos,
		union u_color *color)
{
	button_scene_modify_uchar(mlx, pos, &(color->r), "red");
	pos.y += 50;
	button_scene_modify_uchar(mlx, pos, &(color->g), "green");
	pos.y += 50;
	button_scene_modify_uchar(mlx, pos, &(color->b), "blue");
}
