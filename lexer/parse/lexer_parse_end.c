#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_end(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	node->re_token.type = node->re_token.type | TKN_OP_END;
	return (OK);
}