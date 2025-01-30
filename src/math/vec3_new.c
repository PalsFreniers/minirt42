/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:20:14 by maamine           #+#    #+#             */
/*   Updated: 2025/01/30 02:21:01 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math/la.h>

t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){
		.x = x,
		.y = y,
		.z = z,
	});
}

t_vec3	vec3_new_from_one(float v)
{
	return (vec3_new(v, v, v));
}

t_vec3	vec3_zero(void)
{
	return ((t_vec3){0});
}
