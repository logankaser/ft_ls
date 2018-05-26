#include <sys/stat.h>
#include <limits.h>
#include <dirent.h>
#include "libft.h"

#define FILE(x) ((t_file*)x)

typedef struct		s_file
{
	char			name[NAME_MAX + 1];
	char			*path;
	struct stat 	meta;
}					t_file;

t_bool sort_ascii(const void *a, const void *b);
t_bool sort_ascii_r(const void *a, const void *b);
t_bool sort_time(const void *a, const void *b);
t_bool sort_time_r(const void *a, const void *b);
