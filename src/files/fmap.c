#include "files.h"

static struct s_string	fmap_free_all(struct s_string *str, t_fd f)
{
	close(f);
	string_destroy(str);
	return (string_zero());
}

struct s_string	fmap(const char *path)
{
	t_fd			f;
	char			buf[FMAP_BUF_SIZE + 1];
	int				tmp;
	struct s_string	ret;

	ret = string_new_with_capacity(FMAP_BUF_SIZE);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (string_zero());
	f = open(path, O_RDONLY);
	if (f < 0)
		return (fmap_free_all(&ret, f));
	while (string_error(false, 0) == STRING_SUCCESS)
	{
		tmp = read(f, buf, FMAP_BUF_SIZE * sizeof(char));
		if (tmp == 0)
			break ;
		if (tmp < 0)
			return (fmap_free_all(&ret, f));
		string_append(&ret, string_new_u(buf, tmp));
	}
	close(f);
	return (ret);
}
