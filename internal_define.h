#ifndef DEFINE_INTERNAL
# define DEFINE_INTERNAL

# define OK 0
# define KO 1
# define NO 1
# define ERROR_INCOMPLETE_RANGE 2
# define ERROR_BAD_CHARACTERS_CLASSES 3
# define ERROR_RANGE_OUT_OF_ORDER 4

# define TKN_OP 1 << 1
# define TKN_OP_EXPR 1 << 12
# define TKN_EXPR 1 << 2
# define TKN_OP_STAR 1 << 3 // *
# define TKN_OP_START 1 << 11 // ^
# define TKN_OP_END 1 << 13 // $
# define TKN_OP_RANGE 1 << 4 // {}
# define TKN_OP_QUERY 1 << 5 // ?
# define TKN_OP_PLUS 1 << 6 // +
# define TKN_GROUP 1 << 7 // (expr1|expr2)
# define TKN_EXPR_RNG 1 << 8 // [a-z]
# define TKN_EXPR_CST 1 << 9 // const
# define TKN_EXPR_ANY 1 << 10 // .

#endif