#include "regex.h"
#include "internal_regex.h"

void	rpush_leaf(t_bin_tree **parent, t_bin_tree *child)
{
	if (*parent)
	{
		(*parent)->right = child;
		child->parent = (*parent);
		return;
	}
	*parent = child;
}

void	lpush_leaf(t_bin_tree **parent, t_bin_tree *child)
{
	if (*parent)
	{
		(*parent)->left = child;
		child->parent = (*parent);
		return;
	}
	*parent = child;
}

t_bin_tree	*create_leaf()
{
	t_bin_tree	*leaf;

	leaf = malloc(sizeof(*leaf));
	if (!leaf)
		return (0x0);
	memset(leaf, 0, sizeof(*leaf));
	return (leaf);
}

void	re_push_leaf(t_bin_tree **parent, t_bin_tree *leaf)
{
	if (!*parent)
	{
		rpush_leaf(parent, leaf);
		return;
	}
}

// Dupliquer une branche