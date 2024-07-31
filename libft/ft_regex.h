/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_regex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:28:27 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 02:17:50 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_REGEX_H
# define FT_REGEX_H

# include "ft_types.h"
# include "libft.h"

# ifndef FT_REGEX_MATCH_DOT_NL
#  define FT_REGEX_MATCH_DOT_NL 1
# endif // FT_REGEX_MATCH_DOT_NL
# ifndef FT_REGEX_TYPE_CHARACTER
#  define FT_REGEX_TYPE_CHARACTER '\\'
# endif // FT_REGEX_TYPE_CHARACTER
# define FT_MAX_REGEX_OBJECT 100
# define FT_MAX_CHAR_CLASS_LEN 500

enum					e_patterns
{
	UNUSED,
	DOT,
	BEGIN,
	END,
	QUESTIONMARK,
	STAR,
	PLUS,
	CHAR,
	CHAR_CLASS,
	INV_CHAR_CLASS,
	DIGIT,
	NOT_DIGIT,
	ALPHA,
	NOT_ALPHA,
	WHITESPACE,
	NOT_WHITESPACE,
};

struct					s_regex
{
	enum e_patterns		type;
	union
	{
		unsigned char	ch;
		unsigned char	*ccl;
	};
};

struct s_regex			*ft_re_compile(const char *pattern);
struct s_string			ft_re_match(struct s_regex *re, char *text);
struct s_string			ft_re_nc_match(const char *pattern, char *text);

#endif // FT_REGEX_H
