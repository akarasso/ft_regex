/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_result.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:55:02 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:56:39 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

void			re_extract_group(
	t_regex *regex,
	t_regex_match *match,
	char *str)
{
	int i;

	(void)str;
	i = 0;
	match->ngroup = 0;
	match->group = malloc(regex->ngroup * sizeof(*match->group));
	while (i < regex->ngroup)
	{
		if (regex->node_group[i]->re_token.data.expr.grp.valid == 0)
		{
			match->group[match->ngroup] = malloc(
				regex->node_group[i]->re_token.data.expr.grp.len + 1);
			memcpy(match->group[match->ngroup],
				regex->node_group[i]->re_token.data.expr.grp.from,
				regex->node_group[i]->re_token.data.expr.grp.len);
			match->group[match->ngroup][regex->node_group[i]
				->re_token.data.expr.grp.len] = 0;
			match->ngroup++;
		}
		i++;
	}
}

void			re_result_push(
	t_regex *regex,
	t_regex_match **results,
	t_regex_match *match,
	char *str)
{
	t_regex_match *new;

	re_extract_group(regex, match, str);
	new = malloc(sizeof(*new));
	memcpy(new, match, sizeof(*new));
	if (*results)
		new->next = *results;
	else
		new->next = 0x0;
	*results = new;
}

t_regex_match	*re_results_to_arr(t_regex_match *results, int n)
{
	t_regex_match	*tr;
	t_regex_match	*tmp;

	tr = 0x0;
	if (n)
	{
		tr = malloc(sizeof(*tr) * (n));
		while (n)
		{
			memcpy(&tr[n - 1], results, sizeof(*results));
			tmp = results->next;
			free(results);
			results = tmp;
			n--;
		}
	}
	return (tr);
}
