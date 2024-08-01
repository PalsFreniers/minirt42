#include "dstring.h"
#include <stdlib.h>

enum e_string_error	string_error(bool set, enum e_string_error value)
{
	static enum e_string_error	string_error = STRING_SUCCESS;

	if (set)
		string_error = value;
	return (string_error);
}

char	*ft_realloc(char *ptr, size_t last, size_t new)
{
	char	*ret;

	ret = ft_calloc(new, sizeof(char));
	if (!ret)
		return (NULL);
	if (ptr)
	{
		while (--last > 0)
			ret[last] = ptr[last];
		ret[0] = ptr[0];
		free(ptr);
	}
	return (ret);
}

void	string_destroy(struct s_string *s)
{
	if (s->unowned)
	{
		string_error(true, STRING_NO_FREE_UNOWNED);
		return ;
	}
	free(s->ptr);
	*s = (struct s_string){0};
}

bool	string_check(struct s_string self)
{
	if (!self.ptr || self.capacity == 0)
	{
		string_error(true, STRING_EMPTY);
		return (false);
	}
	if (self.len > self.capacity)
	{
		string_error(true, STRING_CORRUPTED);
		return (false);
	}
	return (true);
}

struct s_string	string_copy(struct s_string self)
{
	char	*ptr;

	if (!string_check(self))
		return ((struct s_string){0});
	ptr = ft_realloc(NULL, 0, self.capacity);
	if (!ptr)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return ((struct s_string){0});
	}
	ft_memcpy(ptr, self.ptr, self.len);
	return ((struct s_string){
		.unowned = false,
		.ptr = ptr,
		.capacity = self.capacity,
		.len = self.len,
	});
}
