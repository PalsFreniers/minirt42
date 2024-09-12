#include "mlx.h"
#include "strings/dstring.h"
#include "ui/buttons.h"
#include <mlx/mmlx.h>
#include <stdlib.h>
#include <ui/numpad.h>

struct s_numpad	numpad_new(void *value, bool is_int, int x, int y)
{
	return ((struct s_numpad){
		.c = value,
		.is_int = is_int,
		.x = x,
		.y = y,
	});
}

void	numpad_draw(struct s_mlx *mlx, struct s_numpad *self)
{
	struct s_string	s;
	char			*ptr;

	if (self->is_int)
		s = string_from_sdword(*(self->c));
	else
		s = string_from_float(*(self->f), 3);
	if (string_error(false, 0) != STRING_SUCCESS)
		s = string_new_u_from_cstr("0000");
	ptr = string_to_cstr(s);
	string_destroy(&s);
	if (!ptr)
		mlx_string_put(mlx->mlx, mlx->win, self->x, self->y, TEXTC,
			"0000");
	else
		mlx_string_put(mlx->mlx, mlx->win, self->x, self->y, TEXTC,
			ptr);
	free(ptr);
}
