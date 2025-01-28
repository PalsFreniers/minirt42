/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_actions_mod_obj_vector3.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:38 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:17:44 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <actions/buttons_actions.h>
#include <mlx/mmlx.h>

void	button_scene_modify_vec3(struct s_mlx *mlx, struct s_vec2i pos,
		struct s_vec3 *pos_p)
{
	button_scene_modify_float_full(mlx, pos, &(pos_p->x), "X");
	pos.y += 50;
	button_scene_modify_float_full(mlx, pos, &(pos_p->y), "Y");
	pos.y += 50;
	button_scene_modify_float_full(mlx, pos, &(pos_p->z), "Z");
}

void	ufloat_dec(float *ptr)
{
	*ptr -= 0.01f;
	if (*ptr < 0)
		*ptr = 0.f;
}
