/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:27:05 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:53:14 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

t_mat3	mat3_add(t_mat3 a, t_mat3 b)
{
	return ((t_mat3){
		.m00 = a.m00 + b.m00,
		.m01 = a.m01 + b.m01,
		.m02 = a.m02 + b.m02,
		.m10 = a.m10 + b.m10,
		.m11 = a.m11 + b.m11,
		.m12 = a.m12 + b.m12,
		.m20 = a.m20 + b.m20,
		.m21 = a.m21 + b.m21,
		.m22 = a.m22 + b.m22,
	});
}

t_mat3	mat3_mul(t_mat3 a, t_mat3 b)
{
	return ((t_mat3){
		.m00 = a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
		.m01 = a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
		.m02 = a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,
		.m10 = a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
		.m11 = a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
		.m12 = a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,
		.m20 = a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
		.m21 = a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
		.m22 = a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22,
	});
}

t_mat3	mat3_scal_mul(t_mat3 a, float f)
{
	return ((t_mat3){
		.m00 = a.m00 * f,
		.m01 = a.m01 * f,
		.m02 = a.m02 * f,
		.m10 = a.m10 * f,
		.m11 = a.m11 * f,
		.m12 = a.m12 * f,
		.m20 = a.m20 * f,
		.m21 = a.m21 * f,
		.m22 = a.m22 * f,
	});
}

t_mat3	mat3_inverse(t_mat3 a)
{
	t_mat3	inverse;
	float	inv_determinant;

	inv_determinant
		= a.m00 * a.m11 * a.m22
		+ a.m01 * a.m12 * a.m20
		+ a.m02 * a.m10 * a.m21
		- a.m02 * a.m11 * a.m20
		- a.m12 * a.m21 * a.m00
		- a.m22 * a.m01 * a.m10;
	if (inv_determinant != 0)
		inv_determinant = 1 / inv_determinant;
	inverse.m00 = (a.m11 * a.m22 - a.m12 * a.m21) * inv_determinant;
	inverse.m01 = (a.m02 * a.m21 - a.m01 * a.m22) * inv_determinant;
	inverse.m02 = (a.m01 * a.m12 - a.m02 * a.m11) * inv_determinant;
	inverse.m10 = (a.m12 * a.m20 - a.m10 * a.m22) * inv_determinant;
	inverse.m11 = (a.m00 * a.m22 - a.m02 * a.m20) * inv_determinant;
	inverse.m12 = (a.m02 * a.m10 - a.m00 * a.m12) * inv_determinant;
	inverse.m20 = (a.m10 * a.m21 - a.m11 * a.m20) * inv_determinant;
	inverse.m21 = (a.m01 * a.m20 - a.m00 * a.m21) * inv_determinant;
	inverse.m22 = (a.m00 * a.m11 - a.m01 * a.m10) * inv_determinant;
	return (inverse);
}
