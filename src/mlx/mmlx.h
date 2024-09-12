#ifndef MMLX_H
# define MMLX_H

# include <mlx.h>
# include <scene/scene.h>
# include <stdbool.h>
# include <ui/buttons.h>
# include <ui/numpad.h>

# define BASE_LINE_Y 70

struct				s_mlx
{
	void			*mlx;
	void			*win;
	void			*ray;
	void			*ray_img;
	void			*ray_back;
	struct s_button	static_b[6];
	struct s_button	interface_buttons[33];
	int				btn_count;
	struct s_numpad	interface_numpad[11];
	int				pad_count;
	int				page;
	struct s_scene	scene;
};

typedef int			(*t_mlx_e_f)(int, void *);
typedef int			(*t_mlx_l_f)(void *);

bool				init_mlx(struct s_mlx *mlx);
void				free_mlx(struct s_mlx *mlx);
void				mlx_swap_ray_buffer(struct s_mlx *mlx);

#endif // MMLX_H
