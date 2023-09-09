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
    int i;
    int j;

    printf("set_av\n");
    g_vars.tmp_token = g_vars.head;
    i = 0;
    while (g_vars.tmp_token)
    {
        // if (g_vars.tmp_token->type == 1)
        //     g_vars.tmp_token->;
        if (g_vars.tmp_token->type == 2 || g_vars.tmp_token->next == NULL)
            break ;
        i++;
        g_vars.tmp_token = g_vars.tmp_token->next;
    }
    g_vars.exec->av = malloc(sizeof(char *) * (i + 1));
    g_vars.exec->av[i] = NULL;
    j = 0;
    g_vars.tmp_token = g_vars.head;
    printf("i : %d\n", i);
    while (j < i)
    {
        g_vars.exec->av[j] = ft_strdup(g_vars.tmp_token->content);
        printf("asdasdasd: %s\n", g_vars.exec->av[j]);
        g_vars.tmp_token = g_vars.tmp_token->next;
        j++;
    }
    printf("asdasdasd: %s\n", g_vars.exec->av[j]);
}

int ms_exec(void)
{
    int has_pipe;
    int pipe_fd[2];
    pid_t child;
    int status;


    has_pipe = 0;
    status = 0;
    ms_set_execve_av(); // g_vars.exec->av oluşturulur.
    if (g_vars.exec->pipe_count > 0)
    {
        if (g_vars.exec->pipe_count > 0)
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


        // av kontrol  area
        int i;
        for (i = 0; g_vars.exec->av[i]; i++)
            printf("\"%s\"\n", g_vars.exec->av[i]);
        printf("\"%s\"\n", g_vars.exec->av[i]);
        // av kontrol area
        // if ()

        // printf("cikti deneme\n");
        execve(*g_vars.exec->av, g_vars.exec->av, g_vars.env);
        perror("bash: ");
        exit(1);
    }
    // printf("waitpid öncesi\n");
    waitpid(child, &status, 0);
    if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
    {
        printf("ZORRRRT\n");
    }
    // return (0);
    return WIFEXITED(status) && WEXITSTATUS(status);
}