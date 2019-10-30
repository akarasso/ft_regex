#include "regex.h"
#include "internal_regex.h"

int		re_match_op_end(t_bin_tree *leaf, char *origin, int *cursor)
{
	if (!origin[*cursor] || origin[*cursor + 1] == '\n')
		return (OK);
	return (KO);
}

int		re_match_expr_group(t_bin_tree *leaf, char *origin, int *cursor)
{
	int	save_cursor;

	save_cursor = *cursor;
	if (leaf->left->exec(leaf->left, origin, cursor) != OK)
		return KO;
	// Should extract string here
	return (OK);
}

int		re_match_op_start(t_bin_tree *leaf, char *origin, int *cursor)
{
	if (*cursor != 0 && origin[(*cursor) - 1] == '\n')
		return (KO);
	if (leaf->right)
		return leaf->right->exec(leaf->right, origin, cursor);
	return KO;
}

int		re_match_op_star(t_bin_tree *leaf, char *origin, int *cursor)
{
	int		save_cursor;

	printf("STAR\n");
	save_cursor = *cursor;
	leaf->left->exec(leaf->left, origin, cursor);
	while (save_cursor != *cursor && origin[*cursor] && leaf->left->exec(leaf->left, origin, cursor) == OK)
		;
	printf("%p\n", leaf->left->exec);
	if (leaf->right)
		return leaf->right->exec(leaf->right, origin, cursor);
	return OK;
}

int		re_match_op_count(t_bin_tree *leaf, char *origin, int *cursor)
{
	int 	min;
	int 	i;
	int		save_cursor;

	save_cursor = *cursor;
	i = 0;
	while (i < leaf->re_token.data.op.min)
	{
		if (origin[*cursor] && leaf->left->exec(leaf->left, origin, cursor) != OK)
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
		&& leaf->left->exec(leaf->left, origin, cursor) == OK)
		i++;
	if (leaf->right)
		return leaf->right->exec(leaf->right, origin, cursor);
	return (OK);
}

int		re_match_op_query(t_bin_tree *leaf, char *origin, int *cursor)
{
	int		save_cursor;

	if (leaf->right)
	{
		save_cursor = *cursor;
		if (leaf->left->exec(leaf->left, origin, cursor) == OK) {
			if (leaf->right->exec(leaf->right, origin, cursor) == OK)
			{
				return (OK);
			}
			(*cursor) = save_cursor;
		} 
		return (leaf->right->exec(leaf->right, origin, cursor));
	}
	return (OK);
}

int		re_match_op_plus(t_bin_tree *leaf, char *origin, int *cursor)
{
	int		save_cursor;

	save_cursor = *cursor;
	if (leaf->left->exec(leaf->left, origin, cursor) != OK)
		return (KO);
	while (save_cursor != *cursor && origin[*cursor] && leaf->left->exec(leaf->left, origin, cursor) == OK)
		;
	if (leaf->right)
		return leaf->right->exec(leaf->right, origin, cursor);
	return OK;
}

int		re_match_expr_rng(t_bin_tree *leaf, char *origin, int *cursor)
{
	if ((leaf->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 1
			&& leaf->re_token.data.expr.rng.reverse == 0)
		|| (leaf->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 0
			&& leaf->re_token.data.expr.rng.reverse == 1))
	{
		(*cursor)++;
		return (OK);
	}
	return (KO);
}

int		re_match_expr_cst(t_bin_tree *leaf, char *origin, int *cursor)
{
	printf("CHECK CONST {%d} %s to %s\n", leaf->re_token.data.expr.cst.size, leaf->re_token.data.expr.cst.value, &origin[*cursor]);
	if (!strncmp(&origin[*cursor], leaf->re_token.data.expr.cst.value, leaf->re_token.data.expr.cst.size))
	{
		(*cursor) += leaf->re_token.data.expr.cst.size;
		if (leaf->right)
		{
			return leaf->right->exec(leaf->right, origin, cursor);
		}
		return (OK);
	}
	return (KO);
}

int		re_match_expr_any(t_bin_tree *leaf, char *origin, int *cursor)
{
	printf("ANY\n");
	if (origin[*cursor])
		(*cursor)++;
	return (OK);
}
