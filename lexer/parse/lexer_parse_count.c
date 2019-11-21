/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:21 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:34:35 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

void	lexer_parse_count_range(t_bin_tree *node, char *pat, int size_match)
{
	int		index;
	char	selecteur;

	selecteur = 0;
	index = 0;
	while (index < size_match)
	{
		if (pat[index] >= '0' && pat[index] <= '9')
		{
			if (!selecteur)
				node->re_token.data.op.min = node->re_token.data.op.min
					* 10 + (pat[index] - '0');
			else
			{
				if (node->re_token.data.op.max < 0)
					node->re_token.data.op.max = 0;
				node->re_token.data.op.max = node->re_token.data.op.max
					* 10 + (pat[index] - '0');
			}
		}
		else if (pat[index] == ',')
			selecteur++;
		index++;
	}
}

int		lexer_parse_count(
	t_regex *regex,
	t_bin_tree *node,
	char *pat,
	int size_match)
{
	(void)regex;
	node->re_token.data.op.min = 0;
	node->re_token.data.op.max = -1;
	lexer_parse_count_range(node, pat + 1, size_match);
	return (OK);
}
