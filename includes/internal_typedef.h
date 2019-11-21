/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_typedef.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:14:32 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_TYPEDEF_H
# define INTERNAL_TYPEDEF_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_regex				t_regex;
typedef struct s_lexer_match_parser	t_lexer_match_parser;
typedef struct s_lexer_flag			t_lexer_flag;
typedef struct s_token				t_token;
typedef struct s_bin_tree			t_bin_tree;
typedef struct s_regex_match		t_regex_match;
typedef struct s_char_class			t_char_class;
typedef int							(*t_lexer_match_func)(
	t_regex*, char*, int, int *);
typedef int							(*t_lexer_parse_func)(
	t_regex *regex, t_bin_tree*, char*, int);
typedef int							(*t_match_func)(
	t_regex_match *match, t_bin_tree *, char *, int *);

#endif
