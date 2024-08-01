#include "dstring.h"
#include "dstring_utils.h"

void	string_erase(struct s_string *self, size_t start, size_t len)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return ;
	}
	if (!string_check(*self))
		return ;
	ft_memmove(self->ptr + start, self->ptr + start + len, self->len - start
		- len);
	self->len -= len;
}

void	string_append(struct s_string *self, struct s_string str)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return ;
	}
	if (!string_check(*self))
		return ;
	while (self->len + str.len > self->capacity && !string_grow(self))
		;
	if (string_error(false, 0) != STRING_SUCCESS)
		return ;
	ft_memmove(self->ptr + self->len, str.ptr, str.len);
	self->len += str.len;
}

void	string_insert(struct s_string *self, struct s_string str, size_t start)
{
	if (self->unowned)
	{
		string_error(true, STRING_NO_MODIFY_UNOWNED);
		return ;
	}
	if (!string_check(*self))
		return ;
	while (self->len + str.len > self->capacity && !string_grow(self))
		;
	if (string_error(false, 0) != STRING_SUCCESS)
		return ;
	ft_memmove(self->ptr + start + str.len, self->ptr + start, self->len
		- start);
	ft_memmove(self->ptr + start, str.ptr, str.len);
	self->len += str.len;
}
