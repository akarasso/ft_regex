/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_compile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:22:18 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 11:19:06 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

t_lexer_match_parser	*re_internal_match_token(
	t_regex *regex,
	char *pat,
	int size,
	int *size_match)
{
	int i;

	i = 0;
	while (i < g_rule_count)
	{
		*size_match = 0;
		if (g_parser_func[i].match(regex, pat, size, size_match) == OK)
			return (&g_parser_func[i]);
		i++;
	}
	return (0x0);
}

void					re_compile_add_subgroup_node(
	t_regex *regex,
	t_bin_tree *node_group)
{
	t_bin_tree **tmp;

	if (regex->ngroup >= regex->ngroup_max - 1)
	{
		tmp = malloc((regex->ngroup_max + 5) * sizeof(*tmp));
		if (regex->node_group)
		{
			memcpy(tmp, regex->node_group, regex->ngroup * sizeof(*tmp));
			free(regex->node_group);
		}
		else
			memset(tmp, 0, 5 * sizeof(*tmp));
		regex->node_group = tmp;
		regex->ngroup_max += 5;
	}
	regex->node_group[regex->ngroup] = node_group;
	regex->ngroup++;
}

static void				re_init_struct(t_regex *regex)
{
	regex->ngroup = 0;
	regex->ngroup_max = 0;
	regex->node_group = 0;
}

int						re_compile_internal(
	t_regex *regex,
	char *pat,
	int full_size)
{
	t_lexer_match_parser	*match;
	t_bin_tree				*node;
	int						size_match;
	int						cursor;

	cursor = 0;
	re_init_struct(regex);
	while (cursor < full_size)
	{
		match = re_internal_match_token(regex,
			&pat[cursor], full_size - cursor,
			&size_match);
		if (!match)
			return (KO);
		node = create_node(match);
		node->re_token.options = regex->options;
		if (push_node(regex, node) != OK)
			return (KO);
		if (match->parser(regex, node, &pat[cursor], size_match) != OK)
			return (KO);
		if (node->re_token.type & TKN_GROUP)
			re_compile_add_subgroup_node(regex, node);
		cursor += size_match;
	}
	return (OK);
}
