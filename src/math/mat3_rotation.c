/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:25:41 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:26:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

t_mat3	rotation_matrix_x(float angle)
{
	return ((t_mat3){
		.m00 = 1,
		.m01 = 0,
		.m02 = 0,
		.m10 = 0,
		.m11 = cosf(angle),
		.m12 = -sinf(angle),
		.m20 = 0,
		.m21 = sinf(angle),
		.m22 = cosf(angle),
	});
}

t_mat3	rotation_matrix_y(float angle)
{
	return ((t_mat3){
		.m00 = cosf(angle),
		.m01 = 0,
		.m02 = sinf(angle),
		.m10 = 0,
		.m11 = 1,
		.m12 = 0,
		.m20 = -sinf(angle),
		.m21 = 0,
		.m22 = cosf(angle),
	});
}

t_mat3	rotation_matrix_z(float angle)
{
	return ((t_mat3){
		.m00 = cosf(angle),
		.m01 = -sinf(angle),
		.m02 = 0,
		.m10 = sinf(angle),
		.m11 = cosf(angle),
		.m12 = 0,
		.m20 = 0,
		.m21 = 0,
		.m22 = 1,
	});
}

t_mat3	get_rotation_matrix(t_vec3 angle)
{
	t_mat3	ret;

	ret = mat3_identity();
	ret = mat3_mul(ret, rotation_matrix_z(angle.z));
	ret = mat3_mul(ret, rotation_matrix_y(angle.y));
	ret = mat3_mul(ret, rotation_matrix_x(angle.x));
	return (ret);
}
