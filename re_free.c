/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 11:16:28 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

void	re_free_tree(t_bin_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		re_free_tree(tree->left);
	if (tree->right)
		re_free_tree(tree->right);
	if (tree->re_token.type & TKN_EXPR_CST)
		free(tree->re_token.data.expr.cst.value);
	free(tree);
}

void	re_free(t_regex *regex)
{
	re_free_tree(regex->tree);
	free(regex->node_group);
}

void	re_free_matches(t_regex_match *match, int nmatch)
{
	int i;
	int o;

	i = 0;
	while (i < nmatch)
	{
		o = 0;
		while (o < match[i].ngroup)
		{
			free(match[i].group[o]);
			o++;
		}
		free(match[i].group);
		free(match[i].value);
		i++;
	}
	free(match);
}
