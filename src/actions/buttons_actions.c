#include "mlx/mmlx.h"
#include "ui/buttons.h"
#include <actions/buttons_actions.h>
#include <fcntl.h>
#include <mlx/hooks.h>
#include <save/save.h>
#include <unistd.h>

void	button_quit(struct s_mlx *mlx)
{
	win_close(0, mlx);
}

void	button_scene_reset(struct s_mlx *mlx)
{
	mlx->btn_count = 0;
	mlx->pad_count = 0;
}

void	button_add_scene(struct s_mlx *mlx)
{
	button_scene_reset(mlx);
	mlx->interface_buttons[0] = button_new(100, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[0]), "sphere", mlx,
		(t_button_f)button_add_sphere);
	mlx->interface_buttons[1] = button_new(250, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[1]), "light", mlx,
		(t_button_f)button_add_light);
	mlx->interface_buttons[2] = button_new(400, BASE_LINE_Y, 100, 60);
	button_set(&(mlx->interface_buttons[2]), "plane", mlx,
		(t_button_f)button_add_plane);
	mlx->interface_buttons[3] = button_new(250, BASE_LINE_Y + 110, 100, 60);
	button_set(&(mlx->interface_buttons[3]), "cylinder", mlx,
		(t_button_f)button_add_cylinder);
	mlx->btn_count = 4;
}

bool	save_obj(struct s_object *obj, int fd)
{
	if (obj->type == OBJ_SPHERE)
		return (save_sphere((struct s_sphere *)obj, fd));
	if (obj->type == OBJ_LIGHT)
		return (save_light((struct s_light *)obj, fd));
	if (obj->type == OBJ_PLANE)
		return (save_plane((struct s_plane *)obj, fd));
	if (obj->type == OBJ_CYLINDER)
		return (save_cylinder((struct s_cylinder *)obj, fd));
	return (false);
}

void	button_save(struct s_scene *scene)
{
	int		fd;
	size_t	i;

	fd = open("map.rt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0)
		return ;
	if (!save_ambient_light(&(scene->ambient), fd))
		return ((void)close(fd));
	if (!save_camera(&(scene->camera), fd))
		return ((void)close(fd));
	write(fd, "\n", 1);
	i = 0;
	while (i < scene->len)
	{
		if (!save_obj(scene->objects[i], fd))
			return ((void)close(fd));
		i++;
	}
	close(fd);
}
