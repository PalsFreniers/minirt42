#ifndef VLINE_H
# define VLINE_H

#include <mlx/mmlx.h>

struct	s_vline
{
	int	x;
	int	y1;
	int	y2;
};

void	vline_print(struct s_mlx *mlx, struct s_vline v, int tcolor);
void	hline_print(struct s_mlx *mlx, struct s_vline v, int tcolor);

#endif // VLINE_H
