#include "regex.h"
#include "internal_regex.h"

t_bin_tree	*create_node(t_lexer_match_parser *match)
{
	t_bin_tree	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (0x0);
	memset(node, 0, sizeof(*node));
	node->re_token.type = match->token_type;
	node->exec = match->exec;
	return (node);
}