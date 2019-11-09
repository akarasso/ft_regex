#include "regex.h"
#include "internal_regex.h"

int		lexer_match_count(t_regex *regex, char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '{')
		return (NO);
	while (size_left && pat[*size_match] && pat[*size_match] != '}')
	{
		if (pat[*size_match] == '-')
			return (NO);
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != '}')
		return (NO);
	(*size_match)++;
	return (OK);
}