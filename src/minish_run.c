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

    if (*g_vars.exec->av)
        free_string_array(g_vars.exec->av);
    tmp = g_vars.head;
    i = 0;
    while (tmp->content)
    {
        if (tmp->type == 2)
            break ;
        i++;
        tmp = tmp->next;
    }
    g_vars.exec->av = malloc(sizeof(char *) * (i + 1));
    g_vars.exec->av[i] = NULL;
    i = 0;
    tmp = g_vars.head;
    while (g_vars.exec->av[i])
    {
        g_vars.exec->av[i] = ft_strdup(tmp->content);
        tmp = tmp->next;
        i++;
    }
}

int ms_exec(void)
{
    int has_pipe;
    int pipe_fd[2];
    int child;
    int status;

    has_pipe = 0;
    status = 0;
    if (g_vars.exec->pipe_count > 0)
        has_pipe = 1;
    if (has_pipe && pipe(pipe_fd) == -1)
        return (0);
    child = fork();
    if (child == 0)
    {
        if (has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
            exit (31);
        ms_set_execve_av();
        printf("asdasdasd: %s\n", g_vars.exec->av[0]);
        execve(*g_vars.exec->av, g_vars.exec->av, 0);
    }
    waitpid(child, &status, 0);
    if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
        exit (32);
    return (0);
}