#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_comment(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	node->re_token.data.expr.cst.value = malloc(size_match + 1);
	strncpy(node->re_token.data.expr.cst.value, pat, size_match);
	node->re_token.data.expr.cst.value[size_match] = 0;
	node->re_token.data.expr.cst.size = size_match;
	return (OK);
}
