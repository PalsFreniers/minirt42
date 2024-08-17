#include <libft.h>
#include <scene/scene.h>
#include <stddef.h>

void	free_scene(struct s_scene *scene)
{
	size_t	i;

	if (!scene->objects)
	{
		ft_bzero(scene, sizeof(struct s_scene));
		return ;
	}
	i = 0;
	while (i < scene->len)
		ft_free("p", scene->objects[i++]);
	ft_free("p", scene->objects);
	ft_bzero(scene, sizeof(struct s_scene));
}
