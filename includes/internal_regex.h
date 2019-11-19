#ifndef INTERNAL_REGEX
# define INTERNAL_REGEX

extern t_lexer_match_parser	parser_func[];
extern size_t				rule_count;
extern t_lexer_flag			flags[];
extern size_t				flag_count;
extern t_char_class			char_classes[];
extern size_t				char_classes_count;

/*
** Lexer
*/
int		lexer_match_comment(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_start(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_end(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_group(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_bracket(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_count(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_any(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_constant(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_star(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_query(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_plus(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_or(t_regex *regex, char *pat, int size_left, int *size_match);
int		lexer_match_flag(t_regex *regex, char *pat, int size_left, int *size_match);

int		lexer_parse_comment(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_start(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_count(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_end(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_bracket_parser(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_bracket(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_any(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_const(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_group(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_star(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_query(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_plus(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_or(t_regex *regex, t_bin_tree *node, char *pat, int size_match);
int		lexer_parse_flag(t_regex *regex, t_bin_tree *node, char *pat, int size_match);



/*
** Match
*/

int		re_match_flag(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor);
int		re_match_op_end(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor);
int		re_match_op_start(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_op_star(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_op_count(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_op_query(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_op_plus(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_expr_rng(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_expr_cst(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_expr_any(t_regex_match *match, t_bin_tree *node, char *str, int *cursor);
int		re_match_expr_group(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor);
int		re_match_op_or(t_regex_match *match, t_bin_tree *node, char *origin, int *cursor);

/*
**	Utils
*/

int		ft_strlen(char *s);

/*
** Tree
*/

t_bin_tree	*create_node(t_lexer_match_parser *match);
int			push_node(t_regex *r, t_bin_tree *node);
int		valid_node(t_bin_tree *last, t_bin_tree *node);


void	re_compile_add_subgroup_node(t_regex *regex, t_bin_tree *node_group);
int		re_compile_internal(t_regex *r, char *pat, int s);
void	re_free_matches(t_regex_match *match, int nmatch);
void	re_free(t_regex *regex);

#endif

