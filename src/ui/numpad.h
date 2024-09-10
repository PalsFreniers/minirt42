#ifndef NUMPAD_H
# define NUMPAD_H

# include "mlx/mmlx_sd.h"
# include <stdbool.h>

struct					s_numpad
{
	union
	{
		float			*f;
		unsigned char	*c;
	};
	int					x;
	int					y;
	bool				is_int;
};

struct s_numpad			numpad_new(void *value, bool is_int, int x, int y);
void					numpad_draw(struct s_mlx *mlx, struct s_numpad *self);

#endif // NUMPAD_H
