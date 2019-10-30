#include "regex.h"
#include "internal_regex.h"

int		re_match_op_end(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match;

	if (!origin[*cursor] || origin[*cursor + 1] == '\n')
		return (OK);
	return (KO);
}

int		re_match_op_start(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match;

	if (*cursor != 0 && origin[(*cursor) - 1] == '\n')
		return (KO);
	if (leaf->right)
	{
		match = re_get_match_func(&leaf->right->re_token);
		return match->func(leaf->right, origin, cursor);
	}
	return KO;
}

int		re_match_op_star(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match;

	match = re_get_match_func(&leaf->left->re_token);
	while (origin[*cursor] && match->func(leaf->left, origin, cursor) == OK)
		;
	if (leaf->right)
	{
		match = re_get_match_func(&leaf->right->re_token);
		return match->func(leaf->right, origin, cursor);
	}
	return OK;
}

int		re_match_op_rng(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match_left;
	t_match	*match_right;
	int 	min;
	int 	i;
	int		save_cursor;

	match_left = re_get_match_func(&leaf->left->re_token);
	match_right = re_get_match_func(&leaf->left->re_token);
	save_cursor = *cursor;
	i = 0;
	while (i < leaf->re_token.data.op.min)
	{
		if (origin[*cursor] && match_left->func(leaf->left, origin, cursor) != OK)
		{
			*cursor = save_cursor;
			return (KO);
		}
		i++;
	}
	if (i < leaf->re_token.data.op.min)
		return (KO);
	while ((i < leaf->re_token.data.op.max && leaf->re_token.data.op.max > 0
		|| leaf->re_token.data.op.max < 0) && origin[*cursor]
		&& match_left->func(leaf->left, origin, cursor) == OK)
		i++;
	if (leaf->right)
		return match_right->func(leaf->right, origin, cursor);
	return (OK);
}

int		re_match_op_query(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match_left;
	t_match	*match_right;
	int		save_cursor;

	match_left = re_get_match_func(&leaf->left->re_token);
	match_right = re_get_match_func(&leaf->left->re_token);
	if (leaf->right)
	{
		save_cursor = *cursor;
		if (match_left->func(leaf->left, origin, cursor) == OK) {
			if (match_right->func(leaf->right, origin, cursor) == OK)
				return (OK);
			(*cursor) = save_cursor;
		} 
		return (match_right->func(leaf->right, origin, cursor));
	}
	return (OK);
}

int		re_match_op_plus(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match;

	match = re_get_match_func(&leaf->left->re_token);
	if (match->func(leaf->left, origin, cursor) != OK)
		return (KO);
	while (origin[*cursor] && match->func(leaf->left, origin, cursor) == OK)
		;
	if (leaf->right)
	{
		match = re_get_match_func(&leaf->right->re_token);
		return match->func(leaf->right, origin, cursor);
	}
	return OK;
}

int		re_match_expr_rng(t_bin_tree *leaf, char *origin, int *cursor)
{
	
}

int		re_match_expr_cst(t_bin_tree *leaf, char *origin, int *cursor)
{
	t_match	*match;

	if (!strncmp(&origin[*cursor], leaf->re_token.data.expr.cst.value, leaf->re_token.data.expr.cst.size))
	{
		(*cursor) += leaf->re_token.data.expr.cst.size;
		if (leaf->right)
		{
			match = re_get_match_func(&leaf->right->re_token);
			return match->func(leaf->right, origin, cursor);
		}
		return (OK);
	}
	return (KO);
}

int		re_match_expr_any(t_bin_tree *leaf, char *origin, int *cursor)
{
	if (origin[*cursor])
		(*cursor)++;
	return (OK);
}
