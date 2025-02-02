/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:32:23 by maamine           #+#    #+#             */
/*   Updated: 2025/02/03 00:56:22 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

t_vec3	vec3_scal_mul(t_vec3 a, float f)
{
	return (vec3_new(f * a.x, f * a.y, f * a.z));
}

float	vec3_sum(t_vec3 a)
{
	return (a.x + a.y + a.z);
}

float	vec3_length_sq(t_vec3 a)
{
	const t_vec3	tmp = vec3_mul(a, a);

	return (vec3_sum(tmp));
}

float	vec3_length(t_vec3 a)
{
	return (sqrtf(vec3_length_sq(a)));
}

t_vec3	vec3_normalise(t_vec3 a)
{
	float	len;

	len = vec3_length(a);
	if (len == 0)
		return (vec3_zero());
	return (vec3_div(a, vec3_new_from_one(len)));
}
