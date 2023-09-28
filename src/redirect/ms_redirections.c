#include "../main/minishell.h"

t_return_red *ms_isred_sentence(int sentence)
{
    int i;
    t_return_red *returnred;

    returnred = malloc(sizeof(t_return_red *));
    i = 0;
    while (g_vars.exec->av_token[sentence][i])
    {
        if (g_vars.exec->av_token[sentence][i] >= 3)
        {
            returnred->index = i;
            returnred->type = g_vars.exec->av_token[sentence][i];
            return (returnred);
        }
        // return (g_vars.exec->av_token[sentence][i]);
        i++;
    }
    return (0);
}

int    ms_redirect_parse(char **sentence, int index)
{
    int i;

    if (!sentence[index + 1])
        return (printf("bash: syntax error near unexpected token `newline'\n") && 1);
    i = 0;
    while ((sentence[index + 1][i]))
    {
        if (!ft_isalnum(sentence[index + 1][i]))
            return (printf("bash: syntax error near unexpected token \'%c\'", sentence[index + 1][i]) && 1);
        i++;
    }
    return (0);
}

void    ms_set_infile()
{

}

void    ms_set_outfile()
{

}

void    ms_set_heredoc()
{

}

void    ms_set_append()
{

}


ms_redirect_manage(int type, int index)
{
    if (type == 3) // <
        ms_set_infile();
    else if (type == 4) // >
        ms_set_outfile();
    else if (type == 5) // <<
        ms_set_heredoc();
    else if (type == 6) // >>
        ms_set_append();
}

ms_remove_redrets(int index)
{
}