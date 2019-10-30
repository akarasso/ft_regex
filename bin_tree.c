#include "regex.h"
#include "internal_regex.h"

t_bin_tree	*create_leaf(int token_type)
{
	t_bin_tree	*leaf;

	leaf = malloc(sizeof(*leaf));
	if (!leaf)
		return (0x0);
	memset(leaf, 0, sizeof(*leaf));
	leaf->re_token.type = token_type;
	return (leaf);
}

void	push_leaf(t_regex *r, t_bin_tree *leaf)
{
	if (!r->last)
	{
		r->tree = leaf;
		r->last = leaf;
		leaf->parent = 0x0;
	}
	else
	{
		if ((r->last->re_token.type & TKN_OP_EXPR))
		{
			if (!r->last->left)
			{
				r->last->left = leaf;
				leaf->parent = r->last;
			}
			else
			{
				r->last->right = leaf;
				leaf->parent = r->last;
				r->last = leaf;
			}
		}
		else
		{
			r->last->right = leaf;
			leaf->parent = r->last;
			r->last = leaf;
		}
	}
}