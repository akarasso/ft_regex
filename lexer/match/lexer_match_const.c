#include "regex.h"
#include "internal_regex.h"

int		lexer_match_constant(t_regex *regex, char *pat, int size_left, int *size_match)
{
	int i;
	int no;

	no = 0;
	while (pat[*size_match] && size_left - *size_match > 0)
	{
		i = 0;
		if (pat[*size_match] == '\\')
		{
			(*size_match) += 2;
			continue;
		}		
		while (i < rule_count - 1)
		{
			if (parser_func[i].match(regex, &pat[*size_match], size_left - *size_match, &no) == OK)
			{
				if ((parser_func[i].token_type & TKN_OP_EXPR) && *size_match > 1)
					(*size_match)--;
				return (OK);
			}
			i++;
		}
		(*size_match)++;	
	}
	return (OK);
}