/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:29:00 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_group(
	t_regex *regex,
	t_bin_tree *node,
	char *pat,
	int size_match)
{
	t_regex sub;
	int		ret;
	int		i;

	sub.test = pat;
	sub.tree = 0x0;
	sub.last = 0x0;
	sub.node_group = 0;
	sub.ngroup = 0;
	sub.ngroup_max = 0;
	sub.options = regex->options;
	ret = re_compile_internal(&sub, pat + 1, size_match - 2);
	if (ret == OK)
	{
		node->left = sub.tree;
		i = 0;
		while (i < sub.ngroup)
		{
			re_compile_add_subgroup_node(regex, sub.node_group[i]);
			i++;
		}
	}
	return (ret);
}
