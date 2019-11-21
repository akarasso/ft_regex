/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_const.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:10:53 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_try_other_rule(
	t_regex *re,
	char *pat,
	int left,
	int *match)
{
	int i;
	int no;

	no = 0;
	i = 0;
	while (i < g_rule_count - 1)
	{
		if (g_parser_func[i].match(re, &pat[*match], left - *match, &no) == OK)
		{
			if ((g_parser_func[i].token_type & TKN_OP_EXPR) && *match > 1)
				(*match)--;
			return (OK);
		}
		i++;
	}
	return (KO);
}

int		lexer_match_constant(
	t_regex *re,
	char *pat,
	int left,
	int *match)
{
	while (pat[*match] && left - *match > 0)
	{
		if (pat[*match] == '\\')
		{
			(*match) += 2;
			continue;
		}
		if (lexer_try_other_rule(re, pat, left, match) == OK)
			return (OK);
		(*match)++;
	}
	return (OK);
}
