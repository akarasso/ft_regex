#include "regex.h"
#include "internal_regex.h"

int		valid_node(t_bin_tree *last, t_bin_tree *node)
{
	if (!last)
	{
		if ((node->re_token.type & TKN_OP_EXPR))
		{
			printf("Can't find operator expression at start.");
			return (KO);
		}
		return (OK);
	}
	if ((last->re_token.type & TKN_OP_EXPR) && (node->re_token.type & TKN_OP_EXPR))
	{
		printf("Can't find operator token after another one.");
		return (KO);
	}
	else if ((last->re_token.type & TKN_OP_OR) && (node->re_token.type & TKN_OP_OR))
	{
		printf("Can't find operator OR after another one.");
		return (KO);
	}
	else if (last->re_token.type == TKN_OP_EXPR)
	{
		printf("Can't find expression before token operator.");
		return (KO);
	}
	return (OK);
}
