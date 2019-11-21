/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_expr_const.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:00:18 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_expr_cst(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	if (!strncmp(&origin[*cursor], node->re_token.data.expr.cst.value,
		node->re_token.data.expr.cst.size))
	{
		(*cursor) += node->re_token.data.expr.cst.size;
		if (node->right)
			return (node->right->exec(match, node->right, origin, cursor));
		return (OK);
	}
	return (KO);
}
