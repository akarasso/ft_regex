#include "regex.h"
#include "internal_regex.h"

t_bin_tree	*create_leaf(t_lexer_match_parser *match)
{
	t_bin_tree	*leaf;

	leaf = malloc(sizeof(*leaf));
	if (!leaf)
		return (0x0);
	memset(leaf, 0, sizeof(*leaf));
	leaf->re_token.type = match->token_type;
	leaf->exec = match->exec;
	return (leaf);
}

int		valid_leaf(t_bin_tree *last, t_bin_tree *leaf)
{
	if (!last)
	{
		if ((leaf->re_token.type & TKN_OP_EXPR))
		{
			printf("Can't find operator expression at start.");
			return (KO);
		}
		return (OK);
	}
	if ((last->re_token.type & TKN_OP_EXPR) && (leaf->re_token.type & TKN_OP_EXPR))
	{
		printf("Can't find operator token after another one.");
		return (KO);
	}
	else if ((last->re_token.type & TKN_OP_OR) && (leaf->re_token.type & TKN_OP_OR))
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

void	push_leaf_op_expr(t_regex *r, t_bin_tree *leaf)
{
	if (r->last->parent)
	{
		r->last->parent->right = leaf;
	}
	else
	{
		r->tree = leaf;
	}
	leaf->parent = r->last->parent;
	leaf->left = r->last;
	r->last->parent = leaf;
	r->last = leaf;
}

void	push_leaf_op_or(t_regex *r, t_bin_tree *leaf)
{
	leaf->left = r->tree;
	leaf->parent = 0x0;
	r->tree->parent = leaf->left;
	r->tree = leaf;
	r->last = leaf;
}

int		push_leaf(t_regex *r, t_bin_tree *leaf)
{
	if (valid_leaf(r->last, leaf) != OK)
		return KO;
	if (!r->last)
	{
		r->tree = leaf;
		r->last = leaf;
		leaf->parent = 0x0;
	}
	else
	{
		if ((leaf->re_token.type & TKN_OP_EXPR))
			push_leaf_op_expr(r, leaf);
		else if ((leaf->re_token.type & TKN_OP_OR))
			push_leaf_op_or(r, leaf);
		else
		{
			r->last->right = leaf;
			leaf->parent = r->last;
			r->last = leaf;
		}
	}
	return (OK);
}