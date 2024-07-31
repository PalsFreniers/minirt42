/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 01:15:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 03:56:10 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATCH_H
# define FT_MATCH_H

# include "ft_regex.h"

int	matchquestion(struct s_regex re, struct s_regex *regex, char *text,
		size_t *len);
int	matchstar(struct s_regex re, struct s_regex *regex, char *text,
		size_t *len);
int	matchplus(struct s_regex re, struct s_regex *regex, char *text,
		size_t *len);
int	matchone(struct s_regex re, char c);
int	matchcharclass(char c, char *str);
int	matchmetachar(char c, char *str);
int	matchrange(char c, char *str);
int	ismetachar(char c);
int	matchdot(char c);

int	match_patern(struct s_regex *re, char *text, size_t *len);

int	matchcharclass_range(char c, char *str);

#endif // FT_MATCH_H
