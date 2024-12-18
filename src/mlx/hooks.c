#include "mlx.h"
#include <mlx/hooks.h>
#include <ui/buttons.h>
#include <ui/vline.h>
#include <ui/window.h>
#include <scene/scene.h>
#include <minirt.h>

void	update_buttons_click(int e, struct s_mlx *mlx)
{
	int	x;

	(void)e;
	button_update(mlx->mlx, &(mlx->static_b[0]));
	button_update(mlx->mlx, &(mlx->static_b[1]));
	button_update(mlx->mlx, &(mlx->static_b[2]));
	button_update(mlx->mlx, &(mlx->static_b[3]));
	button_update(mlx->mlx, &(mlx->static_b[4]));
	button_update(mlx->mlx, &(mlx->static_b[5]));
	x = 0;
	while (x < mlx->btn_count)
	{
		button_update(mlx->mlx, &(mlx->interface_buttons[x]));
		x++;
	}
}

void	update_buttons_unclick(int e, struct s_mlx *mlx)
{
	int	x;

	(void)e;
	mlx->static_b[0].is_clicked = false;
	mlx->static_b[1].is_clicked = false;
	mlx->static_b[2].is_clicked = false;
	mlx->static_b[3].is_clicked = false;
	mlx->static_b[4].is_clicked = false;
	mlx->static_b[5].is_clicked = false;
	x = 0;
	while (x < mlx->btn_count)
	{
		mlx->interface_buttons[x].is_clicked = false;
		x++;
	}
}

int	win_close(int e, struct s_mlx *mlx)
{
	if (e == 0)
		mlx_loop_end(mlx->mlx);
	return (0);
}

void	loop_draw_ui(struct s_mlx *mlx)
{
	int	x;

	mlx_clear_window(mlx->mlx, mlx->win);
	button_draw(mlx, &(mlx->static_b[0]));
	button_draw(mlx, &(mlx->static_b[1]));
	button_draw(mlx, &(mlx->static_b[2]));
	button_draw(mlx, &(mlx->static_b[3]));
	button_draw(mlx, &(mlx->static_b[4]));
	button_draw(mlx, &(mlx->static_b[5]));
	x = 0;
	while (x < mlx->btn_count)
	{
		button_draw(mlx, &(mlx->interface_buttons[x]));
		x++;
	}
	x = 0;
	while (x < mlx->pad_count)
	{
		numpad_draw(mlx, &(mlx->interface_numpad[x]));
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->ray, mlx->ray_img, 0, 0);
}

static t_vec3	rotate_camera_x(struct s_mlx *mlx, float angle)
{
	t_vec3	new_dir_local;
	t_vec3	new_dir_global;

	new_dir_local = mat3_apply(rotation_matrix_x(angle),
			vec3_new(0.0f, 0.0f, 1.0f));
	new_dir_global = mat3_apply(mlx->scene.camera.inverse_transform,
			new_dir_local);
	return (new_dir_global);
}

int	camera_move(int key, struct s_mlx *mlx)
{
	struct s_camera	*camera;

	camera = &mlx->scene.camera;
	if (key == KEY_W)
		camera->direction = rotate_camera_x(mlx, -0.1f);
	else if (key == KEY_S)
		camera->direction = rotate_camera_x(mlx, +0.1f);
	else if (key == KEY_A)
		camera->direction = mat3_apply(rotation_matrix_z(+0.1f),
				camera->direction);
	else if (key == KEY_D)
		camera->direction = mat3_apply(rotation_matrix_z(-0.1f),
				camera->direction);
	else if (key == KEY_Q)
		camera->position = vec3_add(camera->position,
				vec3_scal_mul(camera->direction, +0.5f));
	else if (key == KEY_E)
		camera->position = vec3_add(camera->position,
				vec3_scal_mul(camera->direction, -0.5f));
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		camera_create_transform(camera);
	map_scene(&mlx->scene, camera->position, camera->transform);
	return (0);
}

int	key_event(int key, struct s_mlx *mlx)
{
	// printf("key: %d\n", key);	// 
	if (key == KEY_ESCAPE)
		return (win_close(0, mlx));
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == KEY_Q || key == KEY_E)
		return (camera_move(key, mlx));
	if (key == KEY_ENTER)
	{
		printf("cam_position:\n");																	// 
		printf_vec3(mlx->scene.camera.position);													// 
		printf("cam_direction:\n");																	// 
		printf_vec3(mlx->scene.camera.direction);													// 
		printf("cam_transform:\n");																	// 
		printf_mat3(mlx->scene.camera.transform);													// 
		printf("cam_inverse_transform:\n");															// 
		printf_mat3(mlx->scene.camera.inverse_transform);											// 
		printf("cam_T * cam_T^-1:\n");																// 
		printf_mat3(mat3_mul(mlx->scene.camera.transform, mlx->scene.camera.inverse_transform));	// 
		// printf("plane_type:\n");																	// 
		// printf_obj_type(mlx->scene.map_objects[7]);													// 
		// printf("\nplane_map_position:\n");															// 
		// printf_vec3(mlx->scene.map_objects[7]->position);											// 
		// printf("plane_map_normal:\n");																// 
		// printf_vec3(((struct s_plane *) mlx->scene.map_objects[7])->normal);						// 
		// printf("\nplane_unmap_position:\n");														// 
		// printf_vec3(unmap_vec3(mlx->scene.map_objects[7]->position,
		// 		mlx->scene.camera.position, mlx->scene.camera.inverse_transform));					// 
		// printf("plane_unmap_normal:\n");															// 
		// printf_vec3(mat3_apply(mlx->scene.camera.inverse_transform,
		// 		((struct s_plane *) mlx->scene.map_objects[7])->normal));							// 
		return (0);
	}
	if (key == KEY_NUM_MINUS)
	{
		if (mlx->down_sizing > 1)
			(mlx->down_sizing)--;
	}
	if (key == KEY_NUM_PLUS)
		(mlx->down_sizing)++;
	if (key == KEY_NUM_5)
		g_debug_show_grid = !g_debug_show_grid;
	return (0);
}
