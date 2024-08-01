#ifndef DSTRING_H
# define DSTRING_H

# include <libft.h>
# include <stdbool.h>

typedef enum e_string_error
{
	STRING_MALLOC_ERROR,
	STRING_NO_FREE_UNOWNED,
        STRING_NO_MODIFY_UNOWNED,
	STRING_CORRUPTED,
	STRING_EMPTY,
	STRING_SUCCESS,
}					t_string_error;

enum e_string_error	string_error(bool set, enum e_string_error value);

typedef struct s_string
{
	char			*ptr;
	size_t			len;
	size_t			capacity;
	bool			unowned;
}					t_string;

struct s_string		string_new_from_cstr(char *s);
struct s_string		string_new(char *s, size_t len);
struct s_string		string_new_with_capacity(size_t capa);
struct s_string		string_new_u_from_cstr(char *s);
struct s_string		string_new_u(char *s, size_t len);

void				string_destroy(struct s_string *s);

struct s_string		string_copy(struct s_string self);

void				string_erase(struct s_string *self, size_t start,
						size_t len);
void				string_append(struct s_string *self, struct s_string str);
void				string_insert(struct s_string *self, struct s_string str,
						size_t start);
void				string_push(struct s_string *self, char c);
char				string_pop(struct s_string *self);
void				string_push_front(struct s_string *self, char c);
char				string_pop_front(struct s_string *self);

#endif // DARRAY_H
