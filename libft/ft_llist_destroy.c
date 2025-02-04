/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llist_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:08:28 by tdelage           #+#    #+#             */
/*   Updated: 2025/02/04 20:47:33 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llist_destroy(struct s_llist *list, t_lstdel_f del)
{
	struct s_llist_node	*node;

	node = list->head;
	while (node)
	{
		ft_llist_node_destroy(node, del);
		node = node->next;
	}
	list->size = 0;
	list->head = NULL;
}
