#include "regex.h"
#include "internal_regex.h"

void			result_push(t_regex_match **results, t_regex_match *match)
{
	t_regex_match *new;

	new = malloc(sizeof(*new));
	memcpy(new, match, sizeof(*new));
	if (*results)
		new->next = *results;
	else
		new->next = 0x0;
	*results = new;
}

t_regex_match	*results_to_arr(t_regex_match *results, int n)
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
	return tr;
}

void	re_extract_group(t_regex *regex, t_regex_match *match, char *str)
{
	int i;

	i = 0;
	match->ngroup = 0;
	match->group = malloc(regex->ngroup * sizeof(*match->group));
	while (i < regex->ngroup)
	{
		if (regex->node_group[i]->re_token.data.expr.grp.valid == 0)
		{
			match->group[match->ngroup] = malloc(regex->node_group[i]->re_token.data.expr.grp.len + 1);
			memcpy(match->group[match->ngroup], regex->node_group[i]->re_token.data.expr.grp.from, regex->node_group[i]->re_token.data.expr.grp.len);
			match->group[match->ngroup][regex->node_group[i]->re_token.data.expr.grp.len] = 0;
			match->ngroup++;
		}
		i++;
	}
}

int		re_exec(t_regex *regex, t_regex_match **end_result, int *n_match, char *str)
{
	t_regex_match	match;
	t_regex_match	*results;
	int				cursor;
	int				old;

	*n_match = 0;
	*end_result = 0x0;
	cursor = 0;
	results = 0x0;
	if (!regex->tree)
		return (KO);
	while (str[cursor])
	{
		old = cursor;
		if (regex->tree->exec(&match, regex->tree, str, &cursor) == OK)
		{
			(*n_match)++;
			match.value = malloc(cursor - old + 1);
			memcpy(match.value, &str[old], cursor - old);
			match.value[cursor - old] = 0;
			re_extract_group(regex, &match, str);
			result_push(&results, &match);
			match.ngroup = 0;
			if (!(regex->options & FLAG_GLOBAL))
				return (OK);
			if (old == cursor)
				cursor++;
		}
		else
			cursor++;
	}
	*end_result = results_to_arr(results, *n_match);
	return (OK);
}	