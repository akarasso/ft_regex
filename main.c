#include "regex.h"
#include "internal_regex.h"

int main(int argc, char **argv)
{
	t_regex			regex;
	t_regex_match	*match;
	int				n_match;

	if (argc > 1)
	{
		printf("INPUT: %s\n", argv[1]);
		if (re_regcomp(&regex, argv[1]) == OK)
		{
			printf("PARSE OK\n");
			if (argc > 2)
			{
				if (re_exec(&regex, &match, &n_match, argv[2]) == OK)
				{
					int o = 0;
					while (o < match->n_subgroup)
					{
						printf("Group %d: %s\n", o, match->subgroup[o]);
						o++;
					}
					printf("MATCH\n");
				}
				else
					printf("NO MATCH\n");
				// if (re_test(&regex, argv[2]) == OK)
				// 	printf("MATCH\n");
				// else
				// 	printf("NO MATCH\n");
			}
		}
		else
			printf("PARSE KO\n");
	}
	return 0;
}