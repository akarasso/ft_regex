/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:43:21 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:08:46 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

void			re_exec_init(
	int *n_match,
	t_regex_match **end_result,
	int *cursor,
	t_regex_match **results)
{
	*n_match = 0;
	*end_result = 0x0;
	*cursor = 0;
	*results = 0x0;
}

void			re_extract_match(
	t_regex_match *match,
	int old,
	int cursor,
	char *str)
{
	match->value = malloc(cursor - old + 1);
	memcpy(match->value, &str[old], cursor - old);
	match->value[cursor - old] = 0;
}

int				re_exec(
	t_regex *regex,
	t_regex_match **end_result,
	int *n_match,
	char *str)
{
	t_regex_match	match;
	t_regex_match	*results;
	int				cursor;
	int				old;

	re_exec_init(n_match, end_result, &cursor, &results);
	while (str[cursor])
	{
		old = cursor;
		if (regex->tree->exec(&match, regex->tree, str, &cursor) == OK)
		{
			(*n_match)++;
			re_extract_match(&match, old, cursor, str);
			re_result_push(regex, &results, &match, str);
			match.ngroup = 0;
			if (!(regex->options & FLAG_GLOBAL))
				return (OK);
			if (old == cursor)
				cursor++;
		}
		else
			cursor++;
	}
	*end_result = re_results_to_arr(results, *n_match);
	return (OK);
}
