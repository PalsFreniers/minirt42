#ifndef BUTTONS_H
# define BUTTONS_H

# include <stdbool.h>

typedef void	(*t_button_f)(void *);

struct			s_button
{
	int			x;
	int			y;
	int			width;
	int			height;
	char		*text;
	int			color;
	int			tcolor;
	void		*data;
	bool		is_clicked;
	t_button_f	on_click;
};

void			button_update(void *mlx, struct s_button *b);
void			button_unclick(struct s_button *b);
void			button_draw(void *mlx, void *win, struct s_button *b);

#endif // BUTTONS_H
