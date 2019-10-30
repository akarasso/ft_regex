#include "regex.h"
#include "internal_regex.h"

t_match match[] = {
	{ TKN_OP_STAR, re_match_op_star, "OP_STAR" },
	{ TKN_OP_RANGE, re_match_op_rng, "OP_RNG" },
	{ TKN_OP_QUERY, re_match_op_query, "OP_QUERY" },
	{ TKN_OP_PLUS, re_match_op_plus, "OP_PLUS" },
	{ TKN_EXPR_RNG, re_match_expr_rng, "EXPR_RNG" },
	{ TKN_EXPR_CST, re_match_expr_cst, "EXPR_CST" },
	{ TKN_OP_START, re_match_op_start, "SOL" },
	{ TKN_OP_END, re_match_op_end, "EOL" },
	{ TKN_EXPR_ANY, re_match_expr_any, "EXPR_ANY" },
};

t_match	*re_get_match_func(t_token *token)
{
	int i;

	i = 0;
	while (i < sizeof(match) / sizeof(match[0]))
	{
		if (match[i].token_type & token->type)
		{
			printf("TEST MATCH DO {%s}\n", match[i].debug);
			return (&match[i]);
		}
		i++;
	}
	return (0x0);
}

int		re_exec(t_regex *r, char *str)
{
	t_match		*match;
	int			cursor;

	cursor = 0;
	match = re_get_match_func(&r->tree->re_token);
	if (match->func(r->tree, str, &cursor) != OK)
		return (KO);
	printf("Len match %d\n", cursor);
	return cursor > 0 ? OK : KO;
}