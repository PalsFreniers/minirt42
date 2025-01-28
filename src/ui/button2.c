/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 06:17:21 by tdelage           #+#    #+#             */
/*   Updated: 2025/01/28 06:17:22 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui/buttons.h"
#include <stdbool.h>

void	button_set_index(struct s_button *self, int index)
{
	self->has_idx = true;
	self->data_index = index;
}
