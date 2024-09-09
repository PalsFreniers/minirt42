#ifndef HOOKS_H
# define HOOKS_H

# include <mlx/mmlx.h>

enum	e_key_type
{
	KEY_ESCAPE = 41,
};

void	update_buttons_click(int e, struct s_mlx *mlx);
void	update_buttons_unclick(int e, struct s_mlx *mlx);
int		win_close(int e, struct s_mlx *mlx);
void	loop_draw_ui(struct s_mlx *mlx);
int		key_event(int key, struct s_mlx *mlx);

#endif // HOOKS_H
