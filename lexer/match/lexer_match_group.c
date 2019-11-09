#include "regex.h"
#include "internal_regex.h"

int		lexer_match_group(t_regex *regex, char *pat, int size_left, int *size_match)
{
	int		stack;

	if (!size_left || *pat != '(')
		return (NO);
	stack = 0;
	while (size_left && pat[*size_match])
	{
		if (pat[*size_match] == '(')
		{
			stack++;
		}
		else if (pat[*size_match] == ')')
		{
			stack--;
			if (stack == 0)
				break;
		}
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != ')')
		return (ERROR_INCOMPLETE_RANGE);
	(*size_match)++;
	return (OK);
}