/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:21:44 by maamine           #+#    #+#             */
/*   Updated: 2024/12/15 00:04:24 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx/mmlx.h>
# include <math/la.h>

void	map_scene(struct s_scene *scene, t_vec3 translation, t_mat3 transform);

#endif // MINIRT_H
