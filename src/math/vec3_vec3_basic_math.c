/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vec3_basic_math.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:22:34 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:23:04 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	return (vec3_new(a.x / b.x, a.y / b.y, a.z / b.z));
}
