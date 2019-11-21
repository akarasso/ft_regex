/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_bracket_classes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:17:47 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:17:56 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_bracket_chars_classes(
	t_regex *re,
	t_bin_tree *n,
	char *pat,
	int *cursor)
{
	int	save_cursor;
	int	i;

	save_cursor = *cursor;
	i = 0;
	while (pat[*cursor] && pat[*cursor] != ']')
		(*cursor)++;
	if (*cursor > 1 && pat[*cursor] == ']' && pat[*cursor - 1] == ':')
	{
		while (i < g_char_classes_count)
		{
			if (!strncmp(g_char_classes[i].match, &pat[save_cursor], *cursor))
			{
				(*cursor)++;
				lexer_parse_bracket(re, n, g_char_classes[i].associated,
					ft_strlen(g_char_classes[i].associated));
				return (OK);
			}
			i++;
		}
		return (ERROR_BAD_CHARACTERS_CLASSES);
	}
	*cursor = save_cursor;
	return (KO);
}
