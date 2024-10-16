#include "ui/buttons.h"
#include "ui/numpad.h"
#include <actions/buttons_actions.h>

void	float_inc_1(float *ptr);

void	float_inc_full(float *ptr)
{
	*ptr += 0.01f;
}

void	ufloat_dec_full(float *ptr)
{
	*ptr -= 0.01f;
}

void	float_dec_1(float *ptr)
{
	*ptr -= 0.01f;
	if (*ptr < -1)
		*ptr = -1.0f;
}

void	button_scene_modify_float_full(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)float_inc_full);
	mlx->interface_buttons[mlx->btn_count + 1] = button_new(pos.x + 20, pos.y,
		80, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2] = button_new(pos.x + 100, pos.y,
		20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)ufloat_dec_full);
	mlx->interface_numpad[mlx->pad_count] = numpad_new(data, false, pos.x + 30,
		pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}

void	button_scene_modify_float_1_1(struct s_mlx *mlx, struct s_vec2i pos,
		float *data, char *text)
{
	mlx->interface_buttons[mlx->btn_count] = button_new(pos.x, pos.y, 20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count]), "+", data,
		(t_button_f)float_inc_1);
	mlx->interface_buttons[mlx->btn_count + 1] = button_new(pos.x + 20, pos.y,
		80, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 1]), text, NULL, NULL);
	mlx->interface_buttons[mlx->btn_count + 2] = button_new(pos.x + 100, pos.y,
		20, 20);
	button_set(&(mlx->interface_buttons[mlx->btn_count + 2]), "-", data,
		(t_button_f)float_dec_1);
	mlx->interface_numpad[mlx->pad_count] = numpad_new(data, false, pos.x + 30,
		pos.y + 40);
	mlx->btn_count += 3;
	mlx->pad_count += 1;
}
