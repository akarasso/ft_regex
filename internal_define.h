#ifndef DEFINE_INTERNAL
# define DEFINE_INTERNAL

# define OK 0
# define KO 1
# define NO 1
# define ERROR_INCOMPLETE_RANGE 2
# define ERROR_BAD_CHARACTERS_CLASSES 3
# define ERROR_RANGE_OUT_OF_ORDER 4

# define TKN_OP 1 << 1
# define TKN_OP_STAR 1 << 1 // *
# define TKN_OP_RANGE 1 << 1 // {}
# define TKN_OP_QUERY 1 << 1 // ?
# define TKN_OP_PLUS 1 << 1 // +
# define TKN_TREE 1 << 2
# define TKN_EXPR 1 << 3

# define RNG_EXPR 1 << 1
# define CST_EXPR 1 << 2

#endif