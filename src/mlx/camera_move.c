/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:11:20 by maamine           #+#    #+#             */
/*   Updated: 2025/02/05 02:52:51 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx/hooks.h>

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
	switch (key)
	{
	case KEY_W: camera->direction = rotate_camera_x(mlx, +0.1f);
		break;
	case KEY_S: camera->direction = rotate_camera_x(mlx, -0.1f);
		break;
	case KEY_A: camera->direction = mat3_apply(rotation_matrix_z(+0.1f), camera->direction);
		break;
	case KEY_D: camera->direction = mat3_apply(rotation_matrix_z(-0.1f), camera->direction);
		break;
	case KEY_Q: camera->position = vec3_add(camera->position, vec3_scal_mul(camera->direction, +0.5f));
		break;
	case KEY_E: camera->position = vec3_add(camera->position, vec3_scal_mul(camera->direction, -0.5f));
		break;
	default:
		break;
	}
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		camera_create_transform(camera);
	map_scene(&mlx->scene, camera->position, camera->transform);
	return (0);
}
