#include "dstring.h"
#include "dstring_utils.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

float	string_to_float(struct s_string self)
{
	int64_t	dec;
	size_t	off;
	size_t	dec2;
	int		p;

	if (!string_check(self))
		return (0);
	dec = string_to_sqword(self);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (dec * 1.0f);
	off = string_search(self, string_new_u_from_cstr(".")) + 1;
	if (string_error(false, 0) == STRING_NEEDLE_NOT_FOUNDED)
	{
		string_error(true, STRING_SUCCESS);
		return (dec * 1.0f);
	}
	dec2 = string_to_uqword(string_new_u(self.ptr + off, self.len - off));
	p = log10(dec2 * 1.0) + 1;
	return (dec * 1.0f + (dec2 / pow(10, p)));
}
