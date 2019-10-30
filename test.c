#include "regex.h"
#include "internal_regex.h"

int		re_exec(t_regex *r, char *str)
{
	int			cursor;

	cursor = 0;
	if (r->tree->exec(r->tree, str, &cursor) != OK)
		return (KO);
	printf("Len match %d\n", cursor);
	return cursor > 0 ? OK : KO;
}