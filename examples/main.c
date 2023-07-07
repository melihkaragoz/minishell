#include "../src/minishell.h"

int main(void)
{
	int p = fork();
	int i = 0;
	int *ip = &i;
	if (p == 0)
	{
		printf("child : p: %p\n", &i);
		printf("hello i'm mainp %d\n", ++(*ip));
	}
	else
	{
		printf("main: p: %p\n", &i);
		printf("hello i'm mainp %d\n", ++(*ip));
	}
	return (0);
}
