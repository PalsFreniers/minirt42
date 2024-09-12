#include <actions/buttons_actions.h>

t_button_f	get_action_for_obj(enum e_object_type type)
{
	if (type == OBJ_SPHERE)
		return ((t_button_f)button_scene_modify_sphere);
	if (type == OBJ_LIGHT)
		return ((t_button_f)button_scene_modify_light);
	if (type == OBJ_PLANE)
		return ((t_button_f)button_scene_modify_plane);
	if (type == OBJ_CYLINDER)
		return ((t_button_f)button_scene_modify_cylinder);
	return ((t_button_f)button_scene_modify_ambient);
}

char	*get_name_for_obj(enum e_object_type type)
{
	if (type == OBJ_SPHERE)
		return ("sphere");
	if (type == OBJ_LIGHT)
		return ("light");
	if (type == OBJ_PLANE)
		return ("plane");
	if (type == OBJ_CYLINDER)
		return ("cylinder");
	return ("ambient");
}

void	init_set_list_button(int *i, int *posx, int *posy)
{
	*i = -1;
	*posx = 1;
	*posy = 1;
}

void	set_list_button(struct s_mlx *mlx, int start, int base, int number)
{
	int					i;
	int					posx;
	int					posy;
	enum e_object_type	type;

	init_set_list_button(&i, &posx, &posy);
	while (++i < number)
	{
		if (base && i == 0)
			type = -1;
		else
			type = mlx->scene.objects[i + start - base]->type;
		mlx->interface_buttons[2 + i] = button_new(posx * 100 + ((posx - 1)
					* 50), BASE_LINE_Y + posy * 60 + ((posy - 1) * 50), 100,
				60);
		button_set(&(mlx->interface_buttons[2 + i]), get_name_for_obj(type),
			mlx, get_action_for_obj(type));
		button_set_index(&(mlx->interface_buttons[2 + i]), start + i - base);
		posx = posx + 1;
		if (posx > 4)
		{
			posx = 1;
			posy++;
		}
	}
}
