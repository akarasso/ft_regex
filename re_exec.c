#include "regex.h"
#include "internal_regex.h"

int		re_exec(t_regex *regex, t_regex_match **match, int *n_match, char *str)
{
	int			cursor;
	int			old;

	cursor = 0;
	*match = malloc(sizeof(t_regex_match));
	if (!*match)
		return KO;
	(*match)->option = regex->option | EXTRACT_SUBGROUP;
	(*match)->n_subgroup = 0;
	(*match)->subgroup = malloc(sizeof(char*) * regex->n_subgroup_max);
	while (str[cursor])
	{
		old = cursor;
		if (regex->tree->exec(*match, regex->tree, str, &cursor) == OK && old != cursor)
		{
			(*n_match)++;
			if (!(regex->option & GLOBAL))
				return (OK);
			// Use linked list to next elem
		}
		else
			cursor++;
	}
	return (KO);
}