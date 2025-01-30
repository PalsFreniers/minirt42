/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:32:18 by maamine           #+#    #+#             */
/*   Updated: 2025/01/29 21:13:40 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <mlx/mmlx.h>
# include <object/objects.h>

typedef struct s_ray
{
	struct s_vec3	direction;
	struct s_vec3	origin;
}					t_ray;

struct s_ray		shoot_ray(int x, int y, float screen_to_cam_factor);

#endif // RAY_H
