#include "regex.h"
#include "internal_regex.h"

void	re_strncpy(t_bin_tree *node, char *dest, char *src, int n)
{
	while (n)
	{
		if ((node->re_token.options & FLAG_IGNORE_WHITESPACE) && *src == ' ')
		{
			src++;
			n--;
			continue;
		}
		if (*src == '\\')
		{
			src++;
			n--;
			if (!n)
				break;
		}
		if ((node->re_token.options & FLAG_CASE_INSENSITIVE) && *src >= 'A' && *src <= 'Z')
			*dest = *src + 'a' - 'A';
		else
			*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = 0;
}


int		lexer_parse_const(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	node->re_token.data.expr.cst.value = malloc(size_match + 1);
	re_strncpy(node, node->re_token.data.expr.cst.value, pat, size_match);
	node->re_token.data.expr.cst.size = size_match;
	return (OK);
}