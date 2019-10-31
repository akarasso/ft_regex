#include "regex.h"
#include "internal_regex.h"

int		re_test(t_regex *r, char *str)
{
	int				cursor;
	int				old;
	t_regex_match	match;

	cursor = 0;
	match.option = 0;
	while (str[cursor])
	{
		printf("{%s}\n", &str[cursor]);
		old = cursor;
		if (r->tree->exec(&match, r->tree, str, &cursor) == OK && old != cursor)
			return (OK);
		cursor++;
	}
	return KO;
}