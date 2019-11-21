/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_op_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:01:05 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_start(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	if (node->re_token.options & FLAG_ANCHOR)
	{
		if (*cursor != 0)
			return (KO);
	}
	if (*cursor != 0 && origin[(*cursor) - 1] == '\n')
		return (KO);
	if (node->right)
		return (node->right->exec(match, node->right, origin, cursor));
	return (KO);
}
