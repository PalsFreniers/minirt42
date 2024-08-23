#include <actions/buttons_actions.h>
#include <mlx/hooks.h>

void	button_quit(struct s_mlx *mlx)
{
	win_close(0, mlx);
}
