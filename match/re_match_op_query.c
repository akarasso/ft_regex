/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_op_query.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:59:06 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_query(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
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
