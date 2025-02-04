/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:41:13 by maamine           #+#    #+#             */
/*   Updated: 2025/02/04 22:59:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>
#include <object/objects.h>

t_vec3	vec3_map_2pi(t_vec3 a)
{
	t_vec3	tmp;

	tmp = vec3_new_from_one(M_PI);
	return (vec3_add(vec3_mul(a, tmp), tmp));
}

t_vec3	map_vec3(t_vec3 vec, t_vec3 translation, t_mat3 transform)
{
	return (mat3_apply(transform, vec3_sub(vec, translation)));
}

t_vec3	unmap_vec3(t_vec3 vec, t_vec3 translation, t_mat3 inverse_transform)
{
	return (vec3_add(mat3_apply(inverse_transform, vec), translation));
}

t_vec3	mat3_apply(t_mat3 a, t_vec3 b)
{
	return ((t_vec3){
		.x = a.m00 * b.x + a.m01 * b.y + a.m02 * b.z,
		.y = a.m10 * b.x + a.m11 * b.y + a.m12 * b.z,
		.z = a.m20 * b.x + a.m21 * b.y + a.m22 * b.z,
	});
}
