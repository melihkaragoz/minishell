#include "minishell.h"

void free_string_array(char **str)
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

void ms_set_execve_av2(void)
{
    t_token *tmp;
    t_token *tmp2;
    int sentence;
    int i;
    bool has_pipe;

    i = 0;
    sentence = -1;
    tmp = g_vars.head;
    tmp2 = g_vars.head;
    has_pipe = false;
    if (g_vars.exec->pipe_count > 0)
        has_pipe = true;
    g_vars.exec->av_token = malloc(sizeof(int *) * (g_vars.exec->pipe_count + 1));
    g_vars.exec->av_token[g_vars.exec->pipe_count] = NULL;
    g_vars.exec->av = malloc(sizeof(char **) * (g_vars.exec->pipe_count + 1));
    g_vars.exec->av[g_vars.exec->pipe_count] = NULL;

    g_vars.i = 0;
    while (tmp)
    {
        if (tmp->type == 2 || !(tmp->content) || tmp->type == 3) // herhangi bir biten cümle'yi farket
        {
            g_vars.exec->set_path = 0;
            sentence++;
            g_vars.exec->av_token[sentence] = malloc(sizeof(int) * (g_vars.i + 1));
            g_vars.exec->av_token[sentence][g_vars.i] = 0;
            g_vars.exec->av[sentence] = malloc(sizeof(char *) * (g_vars.i + 1));
            g_vars.exec->av[sentence][g_vars.i] = NULL;
            i = -1;
            while (++i < g_vars.i)
            {
                g_vars.exec->av[sentence][i] = ft_strdup(tmp2->content);
                g_vars.exec->av_token[sentence][i] = tmp2->type;
                if (!(tmp2->type) && !(g_vars.exec->set_path))
                {
                    if(ms_test_path(tmp2->content))
                    {
                        // printf("freeeeeeeeeee\n");
                        // free(g_vars.exec->av[sentence][i]);
                        g_vars.exec->av[sentence][i] = ms_test_path(tmp2->content);
                        g_vars.exec->set_path = 1;
                    }
                }
                tmp2 = tmp2->next;
            }
            // for (size_t i = 0; g_vars.exec->av[i]; i++)
            // {
            //     int j;
            //     for (j = 0; g_vars.exec->av[i][j]; j++)
            //     {
            //         // printf(" %s -", g_vars.exec->av[i][j]);
            //         // printf(" %d -", g_vars.exec->av_token[i][j]);
            //     }
            //     // printf(" %s\n", g_vars.exec->av[i][j]);
            // }
            if (tmp2 && tmp2->type == 2)
            {
                g_vars.exec->pipe_count--;
                if (has_pipe == true && g_vars.exec->pipe_count == -1)
                    break;
                tmp2 = tmp2->next;
                tmp = tmp->next;
                g_vars.i = 0;
                continue;
            }
            else if (tmp->content == NULL)
                break;
        }
        g_vars.i++;
        tmp = tmp->next;
    }
}

int ms_exec(void)
{
    // int has_pipe;
    // int pipe_fd[2];
    // pid_t child;
    // int status;             // child process return code
    // has_pipe = 0;
    // status = 0;
    ms_set_execve_av2(); // g_vars.exec->av oluşturulur.
    // printf("PIPE COUNT: %d\n", g_vars.exec->pipe_count);

    // av kontrol  area
    // int i;
    // for (i = 0; g_vars.exec->av[i]; i++)
    //     printf("\"%s\"\n", g_vars.exec->av[i]);
    // printf("\"%s\"\n", g_vars.exec->av[i]);
    // av kontrol area

    // if (has_pipe && pipe(pipe_fd) == -1)
    //     return (0);
    // child = fork();
    // if (!child)
    // {
    //     if (has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
    //         exit (31);
    //     execve(*g_vars.exec->av, g_vars.exec->av, g_vars.env);
    //     perror("bash: ");
    //     exit(1);
    // }
    // // printf("waitpid öncesi\n");
    // waitpid(child, &status, 0);
    // if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
    // {
    //     printf("ZORRRRT\n");
    // }
    // return WIFEXITED(status) && WEXITSTATUS(status);
    return (0);
}