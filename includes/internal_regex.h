/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_regex.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:23:54 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:31:40 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_REGEX_H
# define INTERNAL_REGEX_H

extern t_lexer_match_parser	g_parser_func[];
extern int					g_rule_count;
extern t_lexer_flag			g_flags[];
extern int					g_flag_count;
extern t_char_class			g_char_classes[];
extern int					g_char_classes_count;

/*
** Lexer
*/

int			lexer_match_comment(t_regex *r, char *p, int left, int *match);
int			lexer_match_start(t_regex *r, char *p, int left, int *match);
int			lexer_match_end(t_regex *r, char *p, int left, int *match);
int			lexer_match_group(t_regex *r, char *p, int left, int *match);
int			lexer_match_bracket(t_regex *r, char *p, int left, int *match);
int			lexer_match_count(t_regex *r, char *p, int left, int *match);
int			lexer_match_any(t_regex *r, char *p, int left, int *match);
int			lexer_match_constant(t_regex *r, char *p, int left, int *match);
int			lexer_match_star(t_regex *r, char *p, int left, int *match);
int			lexer_match_query(t_regex *r, char *p, int left, int *match);
int			lexer_match_plus(t_regex *r, char *p, int left, int *match);
int			lexer_match_or(t_regex *r, char *p, int left, int *match);
int			lexer_match_flag(t_regex *r, char *p, int left, int *match);

int			lexer_parse_comment(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_start(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_count(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_end(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_bracket_parser(
			t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_bracket(t_regex *r,
			t_bin_tree *n, char *s, int match);
int			lexer_parse_any(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_const(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_group(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_star(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_query(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_plus(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_or(t_regex *r, t_bin_tree *n, char *s, int match);
int			lexer_parse_flag(t_regex *r, t_bin_tree *n, char *s, int match);

int			lexer_parse_bracket_range(t_bin_tree *node, char *pat, int *cursor);
int			lexer_parse_bracket_chars_classes(t_regex *re, t_bin_tree *n,
			char *pat, int *cursor);
/*
** Match
*/

int			re_match_flag(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_end(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_start(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_star(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_count(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_query(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_plus(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_expr_rng(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_expr_cst(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_expr_any(t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_expr_group(
			t_regex_match *m, t_bin_tree *n, char *s, int *c);
int			re_match_op_or(t_regex_match *m, t_bin_tree *n, char *s, int *c);

/*
**	Utils
*/

int			ft_strlen(char *s);

/*
** Tree
*/

t_bin_tree	*create_node(t_lexer_match_parser *match);
int			push_node(t_regex *r, t_bin_tree *node);
int			valid_node(t_bin_tree *last, t_bin_tree *node);

void		re_compile_add_subgroup_node(t_regex *r, t_bin_tree *node);
int			re_compile_internal(t_regex *r, char *pat, int s);
void		re_free_matches(t_regex_match *match, int nmatch);
void		re_free(t_regex *regex);
void		re_result_push(t_regex *regex, t_regex_match **results,
	t_regex_match *match, char *str);
t_regex_match	*re_results_to_arr(t_regex_match *results, int n);

#endif
