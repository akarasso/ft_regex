#include "regex.h"
#include "internal_regex.h"

int main(int argc, char **argv)
{
	t_regex			regex;
	t_regex_match	*matches;
	int				nmatch;

	if (argc > 1)
	{
		if (re_regcomp(&regex, argv[1]) == OK)
		{
			if (argc > 2)
			{
				if (re_exec(&regex, &matches, &nmatch, argv[2]) == OK)
				{
					printf("Nombre de match: %d\n", nmatch);
					int i = 0;
					while (i < nmatch)
					{
						printf("Global match: %s\n", matches[i].value);
						printf("Subgroup: %d\n", matches[i].ngroup);
						int o = 0;
						while (o < matches[i].ngroup)
						{
							printf("Group %d: %s\n", o, matches[i].group[o]);
							o++;
						}
						i++;
					}
					re_free_matches(matches, nmatch);
				}
				else
					printf("NO MATCH\n");
				if (re_test(&regex, argv[2]) == OK)
					printf("MATCH\n");
				else
					printf("NO MATCH\n");
			}
			re_free(&regex);
		}
		else
			printf("PARSE KO\n");
	}
	return 0;
}