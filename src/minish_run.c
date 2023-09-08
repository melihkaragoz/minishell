#include "minishell.h"

void    free_string_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void    ms_set_execve_av(void)
{
    t_token *tmp;
    int i;
    int j;

    printf("saf\n");
    if (g_vars.exec->av && *g_vars.exec->av)
        free_string_array(g_vars.exec->av);
    tmp = g_vars.head;
    i = 0;
    while (tmp)
    {
        if (tmp->type == 2 || tmp->next == NULL)
            break ;
        i++;
        tmp = tmp->next;
    }
    g_vars.exec->av = malloc(sizeof(char *) * (i + 1));
    g_vars.exec->av[i] = NULL;
    j = 0;
    tmp = g_vars.head;
    printf("i : %d\n", i);
    while (j < i)
    {
        printf("asdasdasd: %s\n", tmp->content);
        g_vars.exec->av[j] = ft_strdup(tmp->content);
        tmp = tmp->next;
        j++;
    }
    getchar();
}

int ms_exec(void)
{
    int has_pipe;
    int pipe_fd[2];
    pid_t child;
    int status;

    has_pipe = 0;
    status = 0;
    if (g_vars.exec->pipe_count >= 0)
    {
        ms_set_execve_av();
        has_pipe = 1;
        g_vars.exec->pipe_count--;
    }
    if (has_pipe && pipe(pipe_fd) == -1)
        return (0);
    child = fork();
    if (!child)
    {
        if (has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
        {
            exit (31);
        }
        execve(*g_vars.exec->av, g_vars.exec->av, g_vars.env);
        return (0);
    }
    printf("ZORT\n");
    waitpid(child, &status, 0);
    if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
    {
        exit (32);
        printf("ZORT\n");
    }
    return WIFEXITED(status) && WEXITSTATUS(status);
}