/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:37:17 by maamine           #+#    #+#             */
/*   Updated: 2025/01/31 17:43:02 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AXES_H
# define AXES_H

# include <mlx/mmlx.h>

# define AXIS_CENTER_X 800
# define AXIS_CENTER_Y 75
# define AXIS_SIZE 50
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF

void	axes_draw(struct s_mlx *mlx);

#endif // AXES_H