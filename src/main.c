#include "strings/dstring.h"
#include <libft.h>
#include <stdio.h>

int	main(void)
{
	struct s_string	s;

	s = string_copy(string_new_u_from_cstr("Heo 123W"));
	string_erase(&s, 4, 3);
	string_append(&s, string_new_u_from_cstr("orld!"));
	string_insert(&s, string_new_u_from_cstr("ll"), 2);
	printf("%.*s\n", (int)s.len, s.ptr);
	string_destroy(&s);
	return (0);
}
