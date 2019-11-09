#include "regex.h"
#include "internal_regex.h"

int		re_test(t_regex *r, char *str)
{
	int				cursor;
	int				old;

	cursor = 0;
	while (str[cursor])
	{
		printf("{%s}\n", &str[cursor]);
		old = cursor;
		if (r->tree->exec(0x0, r->tree, str, &cursor) == OK && old != cursor)
			return (OK);
		cursor++;
	}
	return KO;
}