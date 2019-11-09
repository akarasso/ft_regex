#include "regex.h"
#include "internal_regex.h"

int		lexer_match_star(t_regex *regex, char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '*')
		return (NO);
	*size_match = 1;
	return (OK);
}
