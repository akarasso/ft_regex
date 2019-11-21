/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_op_star.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:11:07 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_star(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	int		save_cursor;

	save_cursor = *cursor;
	node->left->exec(match, node->left, origin, cursor);
	while (save_cursor != *cursor && origin[*cursor]
		&& node->left->exec(match, node->left, origin, cursor) == OK)
		;
	if (node->right)
		return (node->right->exec(match, node->right, origin, cursor));
	return (OK);
}
