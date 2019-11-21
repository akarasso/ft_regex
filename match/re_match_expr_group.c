/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_expr_group.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:13:19 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_expr_group(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	int	save_cursor;

	save_cursor = *cursor;
	if (node->left->exec(match, node->left, origin, cursor) != OK)
		return (KO);
	node->re_token.data.expr.grp.from = &origin[save_cursor];
	node->re_token.data.expr.grp.valid = 0;
	node->re_token.data.expr.grp.len = *cursor - save_cursor;
	if (node->right
		&& node->right->exec(match, node->right, origin, cursor) != OK)
	{
		node->re_token.data.expr.grp.valid = 1;
		return (KO);
	}
	return (OK);
}
