#include "libft.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <strings/dstring.h>
#include <strings/dstring_utils.h>

static struct s_string	destroy_zero(struct s_string *a)
{
	if (a)
		string_destroy(a);
	return (string_zero());
}

struct s_string	string_from_float(float value, int a_dot)
{
	struct s_string	ret;
	float			fpart;
	struct s_string	dec;
	int				p;
	int				app;

	ret = string_from_sqword((int64_t)value);
	if (string_error(false, 0) != STRING_SUCCESS)
		return ((struct s_string){0});
	fpart = value - (int64_t)value;
	if (fpart == 0)
		return (ret);
	p = pow(10, a_dot);
	fpart *= p;
	if ((size_t)fpart == 0)
		return (ret);
	app = 0;
	string_push(&ret, '.');
	while (fpart < (int)(p / 10))
	{
		fpart *= 10;
		app++;
		string_push(&ret, '0');
	}
	app = pow(10, app);
	fpart /= app;
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	dec = string_from_uqword(fpart);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	string_append(&ret, dec);
	string_destroy(&dec);
	if (fpart)
		if (string_error(false, 0) != STRING_SUCCESS)
			return (destroy_zero(&ret));
	if (value < 0 && (int)value == 0)
		string_push_front(&ret, '-');
	return (ret);
}

char	*string_to_cstr(struct s_string self)
{
	char	*ret;

	if (!string_check(self) || self.len == 0)
		return (NULL);
	ret = ft_calloc(self.len + 1, sizeof(char));
	if (!ret)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return (NULL);
	}
	ft_memcpy(ret, self.ptr, self.len);
	return (ret);
}
