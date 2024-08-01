#ifndef DSTRING_UTILS_H
# define DSTRING_UTILS_H

# include "dstring.h"

char	*ft_realloc(char *ptr, size_t last, size_t new);
bool	string_check(struct s_string self);
bool	string_grow(struct s_string *self);

#endif // DSTRING_UTILS_H
