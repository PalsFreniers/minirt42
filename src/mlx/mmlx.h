#ifndef MMLX_H
# define MMLX_H

# include <mlx.h>
# include <stdbool.h>
# include <ui/buttons.h>
# include <scene/scene.h>

# define BASE_LINE_Y 70

struct				s_mlx
{
	void			*mlx;
	void			*win;
	struct s_scene	*scene;
	bool			redraw;
	struct s_button	static_b[2];
        struct s_button interface_buttons[20];
        int btn_count;
};

typedef int			(*t_mlx_e_f)(int, void *);
typedef int			(*t_mlx_l_f)(void *);

bool	init_mlx(struct s_mlx *mlx, struct s_scene *scene);
void	free_mlx(struct s_mlx *mlx);

#endif // MMLX_H
