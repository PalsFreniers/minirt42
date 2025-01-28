/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:56 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:18:59 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object/objects.h"
#include <libft.h>
#include <math.h>
#include <math/la.h>
#include <render/collision.h>

float	ft_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

bool	sphere_collide_function(struct s_ray *ray, struct s_sphere *sphere,
		t_collision *coll)
{
	const float	radius = sphere->diameter / 2;
	float		determinant;
	t_vec3		ray_to_sphere;
	float		rtsp_norm_squarred;
	float		ray_dot_rtsp;

	ray_to_sphere = vec3_sub(ray->origin, sphere->base.position);
	ray_dot_rtsp = vec3_dot(ray->direction, ray_to_sphere);
	rtsp_norm_squarred = vec3_lenght_sq(ray_to_sphere);
	determinant = ray_dot_rtsp * ray_dot_rtsp - (rtsp_norm_squarred - radius
			* radius);
	if (determinant < 0)
		return (false);
	if (coll)
	{
		coll->dist = (-ray_dot_rtsp) - sqrtf(determinant);
		coll->position = vec3_add(ray->origin, vec3_scal_mul(ray->direction,
					coll->dist));
		coll->normal = vec3_normalise(vec3_sub(coll->position,
					sphere->base.position));
	}
	return (true);
}
