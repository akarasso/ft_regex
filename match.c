#include "regex.h"
#include "internal_regex.h"

int		re_match_flag(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if (node->right)
		return node->right->exec(match, node->right, origin, cursor);
	return (OK);
}


int		re_match_op_or(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int		save_subgroup_index;
	int		save_cursor;

	if (match)
		save_subgroup_index = match->ngroup;
	save_cursor = *cursor;
	if (node->left && node->left->exec(match, node->left, origin, cursor) != OK)
	{
		if (match)
			match->ngroup = save_subgroup_index;
		*cursor = save_cursor;
		if (node->right)
			return node->right->exec(match, node->right, origin, cursor);
		return (KO);
	}
	return (OK);
}

int		re_match_op_end(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if (!origin[*cursor] || ((node->re_token.options & FLAG_MULTILINE)
		&& origin[*cursor + 1] == '\n'))
		return (OK);
	return (KO);
}

int		re_match_expr_group(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int	save_cursor;

	save_cursor = *cursor;
	if (node->left->exec(match, node->left, origin, cursor) != OK)
		return (KO);
	node->re_token.data.expr.grp.from = &origin[save_cursor];
	node->re_token.data.expr.grp.valid = 0;
	node->re_token.data.expr.grp.len = *cursor - save_cursor;
	if (node->right && node->right->exec(match, node->right, origin, cursor) != OK)
	{
		node->re_token.data.expr.grp.valid = 1;
		return (KO);
	}
	return (OK);
}

int		re_match_op_start(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if (node->re_token.options & FLAG_ANCHOR)
	{
		if (*cursor != 0)
			return (KO);
	}
	if (*cursor != 0 && origin[(*cursor) - 1] == '\n')
		return (KO);
	if (node->right)
		return node->right->exec(match, node->right, origin, cursor);
	return KO;
}

int		re_match_op_star(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int		save_cursor;

	save_cursor = *cursor;
	node->left->exec(match, node->left, origin, cursor);
	while (save_cursor != *cursor && origin[*cursor]
		&& node->left->exec(match, node->left, origin, cursor) == OK)
		;
	if (node->right)
		return node->right->exec(match, node->right, origin, cursor);
	return OK;
}

int		re_match_op_count(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int 	min;
	int 	i;
	int		save_cursor;

	save_cursor = *cursor;
	i = 0;
	while (i < node->re_token.data.op.min)
	{
		if (origin[*cursor] && node->left->exec(match, node->left, origin, cursor) != OK)
		{
			*cursor = save_cursor;
			return (KO);
		}
		i++;
		if (!origin[*cursor])
			break;
	}
	if (i < node->re_token.data.op.min)
	{
		*cursor = save_cursor;
		return (KO);
	}
	if (node->re_token.data.op.max != -1)
	{
		while ((i < node->re_token.data.op.max && node->re_token.data.op.max > 0
			|| node->re_token.data.op.max < 0) && origin[*cursor]
			&& node->left->exec(match, node->left, origin, cursor) == OK)
			i++;
	}
	if (node->right)
		return node->right->exec(match, node->right, origin, cursor);
	return (OK);
}

int		re_match_op_query(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int		save_cursor;

	save_cursor = *cursor;
	if (node->left->exec(match, node->left, origin, cursor) == OK)
	{
		if (!node->right)
			return (OK);
		else if (node->right->exec(match, node->right, origin, cursor) == OK)
			return (OK);
		(*cursor) = save_cursor;
	}
	return (OK);
}

int		re_match_op_plus(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	int		save_cursor;

	save_cursor = *cursor;
	if (node->left->exec(match, node->left, origin, cursor) != OK)
		return (KO);
	while (save_cursor != *cursor && origin[*cursor] && node->left->exec(match, node->left, origin, cursor) == OK)
		;
	if (node->right)
		return node->right->exec(match, node->right, origin, cursor);
	return OK;
}

int		re_match_expr_rng(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if ((node->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 1
			&& node->re_token.data.expr.rng.reverse == 0)
		|| (node->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 0
			&& node->re_token.data.expr.rng.reverse == 1))
	{
		(*cursor)++;
		return (OK);
	}
	return (KO);
}

int		re_match_expr_cst(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if (!strncmp(&origin[*cursor], node->re_token.data.expr.cst.value, node->re_token.data.expr.cst.size))
	{
		(*cursor) += node->re_token.data.expr.cst.size;
		if (node->right)
			return node->right->exec(match, node->right, origin, cursor);
		return (OK);
	}
	return (KO);
}

int		re_match_expr_any(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor)
{
	if (origin[*cursor] == '\n' && !(node->re_token.options & FLAG_SINGLE_LINE))
		return (KO);
	if (origin[*cursor])
		(*cursor)++;
	return (OK);
}

