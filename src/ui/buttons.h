#ifndef BUTTONS_H
# define BUTTONS_H

# include <stdbool.h>
# include <mlx/mmlx_sd.h>
# define PPC 7
# define BORDERC 0xFF8888FF
# define TEXTC 0xFFDDDDDD

typedef void	(*t_button_f)(void *);

struct			s_button
{
	int			x;
	int			y;
	int			width;
	int			height;
	char		*text;
	void		*data;
	bool		is_clicked;
	t_button_f	on_click;
};

void			button_update(void *mlx, struct s_button *b);
void			button_unclick(struct s_button *b);
void			button_draw(struct s_mlx *mlx, struct s_button *b);

#endif // BUTTONS_H
