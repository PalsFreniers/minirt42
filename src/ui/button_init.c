#include <mlx/mmlx.h>
#include <stdio.h>
#include <ui/buttons.h>

void	add_0_1(float *f)
{
	if (!f)
		return ;
	*f += 0.01f;
	if (*f > 1)
		*f = 1;
}

void	sub_0_1(float *f)
{
	if (!f)
		return ;
	*f -= 0.01f;
	if (*f < 0)
		*f = 0;
}

void	add_0_255(unsigned int *i)
{
	if (!i)
		return ;
	*i += 1;
}

void	sub_0_255(unsigned char *i)
{
	if (!i)
		return ;
	*i -= 1;
}

void	print_flt(float *f)
{
	if (!f)
		return ;
	print_float("", "value", *f);
}

void	print_uc(unsigned char *u)
{
	if (!u)
		return ;
	printf("value => %d\n", *u);
}

void	append_interface_color(struct s_mlx *mlx, union u_color *color, int x,
		int y)
{
	int	tmp;

	tmp = mlx->btn_count;
	mlx->btn_count += 9;
	mlx->interface_buttons[tmp] = (struct s_button){
		.x = x,
		.y = y,
		.width = 20,
		.height = 20,
		.text = "+",
		.data = &(color->r),
		.on_click = (t_button_f)add_0_255,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 1] = (struct s_button){
		.x = x + 20,
		.y = y,
		.width = 60,
		.height = 20,
		.text = "red",
		.data = &(color->r),
		.on_click = (t_button_f)print_uc,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 2] = (struct s_button){
		.x = x + 80,
		.y = y,
		.width = 20,
		.height = 20,
		.text = "-",
		.data = &(color->r),
		.on_click = (t_button_f)sub_0_255,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 3] = (struct s_button){
		.x = x,
		.y = y + 40,
		.width = 20,
		.height = 20,
		.text = "+",
		.data = &(color->g),
		.on_click = (t_button_f)add_0_255,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 4] = (struct s_button){
		.x = x + 20,
		.y = y + 40,
		.width = 60,
		.height = 20,
		.text = "green",
		.data = &(color->g),
		.on_click = (t_button_f)print_uc,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 5] = (struct s_button){
		.x = x + 80,
		.y = y + 40,
		.width = 20,
		.height = 20,
		.text = "-",
		.data = &(color->g),
		.on_click = (t_button_f)sub_0_255,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 6] = (struct s_button){
		.x = x,
		.y = y + 80,
		.width = 20,
		.height = 20,
		.text = "+",
		.data = &(color->b),
		.on_click = (t_button_f)add_0_255,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 7] = (struct s_button){
		.x = x + 20,
		.y = y + 80,
		.width = 60,
		.height = 20,
		.text = "blue",
		.data = &(color->b),
		.on_click = (t_button_f)print_uc,
		.is_clicked = false,
	};
	mlx->interface_buttons[tmp + 8] = (struct s_button){
		.x = x + 80,
		.y = y + 80,
		.width = 20,
		.height = 20,
		.text = "-",
		.data = &(color->b),
		.on_click = (t_button_f)sub_0_255,
		.is_clicked = false,
	};
}

void	init_buttons_edit_ambiant_light(struct s_mlx *mlx)
{
	mlx->btn_count = 3;
	mlx->interface_buttons[0] = (struct s_button){
		.x = 0,
		.y = BASE_LINE_Y,
		.width = 20,
		.height = 20,
		.text = "+",
		.data = &(mlx->scene.ambient.ratio),
		.on_click = (t_button_f)add_0_1,
		.is_clicked = false,
	};
	mlx->interface_buttons[1] = (struct s_button){
		.x = 20,
		.y = BASE_LINE_Y,
		.width = 60,
		.height = 20,
		.text = "ratio",
		.data = &(mlx->scene.ambient.ratio),
		.on_click = (t_button_f)print_flt,
		.is_clicked = false,
	};
	mlx->interface_buttons[2] = (struct s_button){
		.x = 80,
		.y = BASE_LINE_Y,
		.width = 20,
		.height = 20,
		.text = "-",
		.data = &(mlx->scene.ambient.ratio),
		.on_click = (t_button_f)sub_0_1,
		.is_clicked = false,
	};
	append_interface_color(mlx, &(mlx->scene.ambient.color), 150, BASE_LINE_Y);
}
