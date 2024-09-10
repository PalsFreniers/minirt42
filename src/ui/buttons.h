#ifndef BUTTONS_H
# define BUTTONS_H

# include <mlx/mmlx_sd.h>
# include <stdbool.h>
# define PPC 7
# define BORDERC 0xFF8888FF
# define TEXTC 0xFFDDDDDD

typedef void			(*t_button_f)(void *);
typedef void			(*t_button_i_f)(void *, int);

struct					s_button
{
	int					x;
	int					y;
	int					width;
	int					height;
	char				*text;
	void				*data;
	int					data_index;
	bool				is_clicked;
	union
	{
		t_button_f		on_click;
		t_button_i_f	on_click_idx;
	};
	bool				has_idx;
};

void					button_update(void *mlx, struct s_button *b);
void					button_draw(struct s_mlx *mlx, struct s_button *b);
void					init_buttons_edit_ambiant_light(struct s_mlx *mlx);
struct s_button			button_new(int x, int y, int width, int height);
void					button_set(struct s_button *self, char *text,
							void *data, t_button_f func);
void					button_set_index(struct s_button *self, int index);
#endif // BUTTONS_H
