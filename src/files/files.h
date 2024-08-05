#ifndef FILES_H
# define FILES_H

# include <fcntl.h>
# include <libft.h>
# include <strings/dstring.h>
# include <unistd.h>

# define FMAP_BUF_SIZE 200

struct s_string	fmap(char *path);

#endif // FILES_H
