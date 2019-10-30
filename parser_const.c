#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_const(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_EXPR_CST;
	leaf->re_token.data.expr.cst.value = malloc(size_match + 1);
	strncpy(leaf->re_token.data.expr.cst.value, pat, size_match);
	leaf->re_token.data.expr.cst.value[size_match] = 0;
	leaf->re_token.data.expr.cst.size = size_match;
	printf("CST: %s\n", leaf->re_token.data.expr.cst.value);
	return (OK);
}