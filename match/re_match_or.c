/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:12:00 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_or(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
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
			return (node->right->exec(match, node->right, origin, cursor));
		return (KO);
	}
	return (OK);
}
