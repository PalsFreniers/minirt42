/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vec3_advanced_math.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:33:53 by maamine           #+#    #+#             */
/*   Updated: 2025/02/03 00:56:22 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (vec3_length(vec3_sub(a, b)));
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (vec3_sum(vec3_mul(a, b)));
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_new(
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x)));
}
