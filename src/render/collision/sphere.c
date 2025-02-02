/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:56 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/02 22:23:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render/collision.h>

bool	sphere_collide(struct s_ray *ray, struct s_sphere *sphere,
		t_collision *coll)
{
	const float	radius = sphere->diameter / 2;
	float		determinant;
	t_vec3		ray_to_sphere;
	float		dist_sq;
	float		ray_off_center;

	ray_to_sphere = vec3_sub(sphere->base.position, ray->origin);
	dist_sq = vec3_lenght_sq(ray_to_sphere);
	ray_off_center = vec3_dot(ray->direction, ray_to_sphere);
	determinant = powf(ray_off_center, 2) - (dist_sq - powf(radius, 2));
	if (determinant < 0)
		return (false);
	if (!coll)
		return (true);
	determinant = sqrtf(determinant);
	coll->dist = ray_off_center - determinant;
	if (coll->dist < 0.0f)
		coll->dist += 2 * determinant;
	coll->position = ray_collision(ray, coll->dist);
	coll->normal = vec3_normalise(vec3_sub(coll->position,
				sphere->base.position));
	if (ray_off_center < determinant)
		coll->normal = vec3_scal_mul(coll->normal, -1.0f);
	return (true);
}
