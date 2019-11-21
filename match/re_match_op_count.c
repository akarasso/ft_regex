/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_op_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:13:37 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_count_min(
	t_regex_match *match,
	t_bin_tree *nd,
	char *origin,
	int *cursor)
{
	int i;

	i = 0;
	while (i < nd->re_token.data.op.min)
	{
		if (origin[*cursor]
			&& nd->left->exec(match, nd->left, origin, cursor) != OK)
			return (-1);
		i++;
		if (!origin[*cursor])
			break ;
	}
	if (i < nd->re_token.data.op.min)
		return (-1);
	return (i);
}

int		re_match_op_count(
	t_regex_match *match,
	t_bin_tree *nd,
	char *origin,
	int *cursor)
{
	int		i;
	int		save_cursor;

	save_cursor = *cursor;
	i = re_match_op_count_min(match, nd, origin, cursor);
	if (i < 0)
	{
		*cursor = save_cursor;
		return (KO);
	}
	if (nd->re_token.data.op.max != -1)
		while (((i < nd->re_token.data.op.max && nd->re_token.data.op.max > 0)
			|| nd->re_token.data.op.max < 0)
			&& origin[*cursor]
			&& nd->left->exec(match, nd->left, origin, cursor) == OK)
			i++;
	if (nd->right)
		return (nd->right->exec(match, nd->right, origin, cursor));
	return (OK);
}
