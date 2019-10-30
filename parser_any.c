#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_any(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_EXPR_ANY;
	return (OK);
}