/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_node_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:16:25 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 19:19:50 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

void	ft_llist_node_destroy(struct s_llist_node *node, t_lstdel_f del)
{
	if (!node)
		return ;
	if (del)
		del(node->data);
	free(node);
}
