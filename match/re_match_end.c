/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:59:48 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_op_end(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	(void)match;
	if (!origin[*cursor] || ((node->re_token.options & FLAG_MULTILINE)
		&& origin[*cursor + 1] == '\n'))
		return (OK);
	return (KO);
}
