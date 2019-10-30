#ifndef INTERNAL_REGEX
# define INTERNAL_REGEX

int		re_compile_internal(t_regex *r, char *pat, int s);

/*
** Lexer
*/
int		lexer_match_start(char *pat, int size_left, int *size_match);
int		lexer_match_end(char *pat, int size_left, int *size_match);
int		lexer_match_subexpre(char *pat, int size_left, int *size_match);
int		lexer_match_bracket(char *pat, int size_left, int *size_match);
int		lexer_match_count(char *pat, int size_left, int *size_match);
int		lexer_match_point(char *pat, int size_left, int *size_match);
int		lexer_match_constant(char *pat, int size_left, int *size_match);

int		lexer_parser_count(t_token *token, char *pat, int size_match);
int		lexer_parser_start(t_token *token, char *pat, int size_match);
int		lexer_parser_end(t_token *token, char *pat, int size_match);
int		lexer_parser_bracket_chars_classes(t_token *token, char *pat, int *cursor);
int		lexer_parser_bracket_parser(t_token *token, char *pat, int size_match);
int		lexer_parser_bracket(t_token *token, char *pat, int size_match);
int		lexer_parser_point(t_token *token, char *pat, int size_match);
int		lexer_parser_const(t_token *token, char *pat, int size_match);

/*
** Match
*/

int		re_match_op_end(t_bin_tree *leaf, char *origin, int *cursor);
int		re_match_op_start(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_op_star(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_op_rng(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_op_query(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_op_plus(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_expr_rng(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_expr_cst(t_bin_tree *leaf, char *str, int *cursor);
int		re_match_expr_any(t_bin_tree *leaf, char *str, int *cursor);

int		re_exec(t_regex *regex, char *str);
t_match	*re_get_match_func(t_token *token);

/*
** Tree
*/

t_bin_tree	*create_leaf(int token_type);
void		push_leaf(t_regex *r, t_bin_tree *leaf);

#endif

