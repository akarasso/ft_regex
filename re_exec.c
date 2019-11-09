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
	t_regex_match	**tr;

	if (n)
	{
		tr = malloc(sizeof(*tr) * n);
		while (n)
		{
			printf("%p\n", results);
			tr[n - 1] = results;
			results = results->next;
			n--;
		}
	}
}

int		re_exec(t_regex *regex, t_regex_match **end_result, int *n_match, char *str)
{
	t_regex_match	match;
	t_regex_match	*results;
	int				cursor;
	int				old;

	cursor = 0;
	results = 0x0;
	match.n_subgroup = 0;
	*n_match = 0;
	match.subgroup = malloc(sizeof(char*) * regex->n_subgroup_max);
	while (str[cursor])
	{
		old = cursor;
		if (regex->tree->exec(&match, regex->tree, str, &cursor) == OK)
		{
			(*n_match)++;
			result_push(&results, &match);
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