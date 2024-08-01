/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:28 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 04:50:29 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSTRING_UTILS_H
# define DSTRING_UTILS_H

# include "dstring.h"

char	*ft_realloc(char *ptr, size_t last, size_t new);
bool	string_check(struct s_string self);
bool	string_grow(struct s_string *self);
char	*calculate_trim(struct s_string self, struct s_string chars);
size_t	calculate_trim_len(struct s_string self, struct s_string chars);

#endif // DSTRING_UTILS_H
