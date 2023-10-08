#include "../main/minishell.h"

void ms_free_string_array(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void ms_copy_struct(t_env *src)
{
	t_env *s;
	t_env *d;

	d = ms_new_env();
	s = src;
	g_vars.export_list = d;
	g_vars.export_head = d;
	while (s->content)
	{
		d->content = ft_strdup(s->content);
		d->next = ms_new_env();
		d = d->next;
		s = s->next;
	}
}

void ms_add_env_list(char *s)
{
	t_env *te;

	te = ms_lstchr(s);
	if (te && te->content)
	{
		te->content = s;
		return;
	}
	g_vars.env_tail->next = ms_new_env();
	g_vars.env_tail->next->content = ft_strdup(s);
	g_vars.env_tail = g_vars.env_tail->next;
	g_vars.env_tail->next = NULL;
}

void ms_print_export(void) // leak var
{
	t_env *t;
	char **s;
	int i;

	t = g_vars.env_head;
	while (t && t->content)
	{
		s = ft_split(t->content, '=');
		if (!s[1])
			s[1] = "";
		// printf("declare -x %s=\"%s\"\n", s[0], s[1]);
		printf("declare -x %s=\"", s[0]);
		i = 0;
		while (s[++i] && ft_strncmp(s[i], "", 1))
		{
			printf("%s", s[i]);
			if (s[i + 1] && ft_strncmp(s[i + 1], "", 1))
				printf("=\n");
		}
		printf("\"\n");
		t = t->next;
		// ms_free_db_array(s);
	}
}

char *ms_getenv(char *s) // bagli listeden cekiyor
{
	t_env *t;
	char **sp;
	char *val;
	int j;
	int	k;

	t = g_vars.env_head;
	val = calloc(1, 1);
	while (t && t->content)
	{
		sp = ft_split(t->content, '=');
		if ((ft_strlen(sp[0]) == ft_strlen(s)) && !ft_strncmp(s, sp[0], ft_strlen(s)))
		{
			k = ft_strchr(t->content, '=') - t->content;
			val = malloc(sizeof(char) * ft_strlen(ft_strchr(t->content, '=')));
			j = -1;
			while(t->content[++k])
				val[++j] = t->content[k];
			val[++j] = 0;
			return (val);
		}
		t = t->next;
	}
	return (NULL);
}

char *ms_get_env(char *s) // bastaki env arrayinden cekiyor
{
	int i;
	char **tmp;
	i = -1;
	while (g_vars.env[++i])
	{
		tmp = ft_split(g_vars.env[i], '=');
		if (*tmp && !ft_strncmp(tmp[0], s, ft_strlen(s)))
			return (tmp[1]);
	}
	return (NULL);
}

void ms_set_execve_arg(void)
{
	t_token *tmp;
	t_token *tmp2;
	int sentence;
	int i;

	i = 0;
	sentence = -1;
	tmp = g_vars.head;
	tmp2 = g_vars.head;
	g_vars.exec->av_token = malloc(sizeof(int *) * (g_vars.exec->pipe_count + 1));
	g_vars.exec->av_token[g_vars.exec->pipe_count] = NULL;
	g_vars.exec->av = malloc(sizeof(char **) * (g_vars.exec->pipe_count + 1));
	g_vars.exec->av[g_vars.exec->pipe_count] = NULL;
	g_vars.i = 0;
	g_vars.exec->arg_num = 0;
	while (tmp)
	{
		if (tmp->type == 2 || !(tmp->content)) // herhangi bir biten cümle'yi farket
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
				g_vars.exec->arg_num++;
				g_vars.exec->av[sentence][i] = ft_strdup(tmp2->content);
				g_vars.exec->av_token[sentence][i] = tmp2->type;
				if (!(tmp2->type) && !(g_vars.exec->set_path))
				{
					if (tmp2->content && ms_test_path(tmp2->content))
					{
						g_vars.exec->av[sentence][i] = ms_test_path(tmp2->content);
						g_vars.exec->set_path = 1;
					}
				}
				tmp2 = tmp2->next;
			}
			if (tmp2 && tmp2->type == 2)
			{
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

void ms_run_pwd(void)
{
	char *s;

	s = ft_strdup(ms_getenv("PWD"));
	getcwd(s, ft_strlen(s));
	printf("%s\n", s);
	free(s);
}

void ms_run_echo(char **sentence)
{
	bool n;
	int i;

	i = 1;
	n = false;
	while (sentence[i])
	{
		if (i == 1 && !ft_strncmp("-n", sentence[i], 2))
		{
			n = true;
			i++;
			continue;
		}
		printf("%s", sentence[i]);
		if (sentence[i + 1])
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
}

void ms_run_cd(char **sentence)
{
	char *pwd;
	char *opwd;
	int res;

	res = 0;
	pwd = ft_strdup(ms_get_env("PWD"));
	getcwd(pwd, ft_strlen(pwd));
	if (sentence[1] && !ft_strncmp(sentence[1], "-", 1))
	{
		res = chdir(ms_getenv("OLDPWD"));
		if (res == -1)
			return ((void)printf("[!] OLDPWD not set\n"));
		printf("%s\n", ms_getenv("OLDPWD"));
	}
	else if (sentence[1])
		res = chdir(sentence[1]);
	else if (!sentence[1])
		chdir(ms_getenv("HOME"));
	else
		return;
	if (res != -1)
	{
		opwd = ft_strjoin("OLDPWD=", pwd);
		if (!((ft_strlen(opwd) == ft_strlen(pwd)) && !ft_strncmp(opwd, pwd, ft_strlen(opwd))))
			ms_add_env_list(opwd);
		free(pwd);
		pwd = ft_strdup(ms_get_env("PWD"));
		getcwd(pwd, ft_strlen(pwd));
		ms_add_env_list(ft_strjoin("PWD=", pwd));
	}
}

t_env *ms_lstchr(char *s)
{
	t_env *lst;

	lst = g_vars.env_head;
	while (lst && lst->content)
	{
		if (ms_strncmp(s, lst->content, '='))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int ms_strncmp(char *a, char *b, char c)
{
	return (ft_nstrchr(a, c) == ft_nstrchr(b, c) && !ft_strncmp(a, b, ft_nstrchr(a, c)));
}

void ms_run_env(void)
{
	t_env *lst;

	lst = g_vars.env_head;
	while (lst && lst->content)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void ms_run_export(char *s)
{
	char **sp;

	if (g_vars.export_list && !g_vars.export_list->next)
	{
		g_vars.export_tail = g_vars.env_tail;
		ms_copy_struct(g_vars.env_head);
	}
	if (!s)
		ms_print_export();
	else
	{
		sp = ft_split(s, '=');
		if (sp[1])
			ms_add_env_list(s);
	}
}

void ms_run_unset(char *s)
{
	t_env *prev;

	char *split;
	g_vars.env_list = g_vars.env_head;
	prev = g_vars.env_head;
	while (s && g_vars.env_list && g_vars.env_list->content)
	{
		split = ft_split(g_vars.env_list->content, '=')[0];
		if (ft_strlen(split) == ft_strlen(s))
		{
			if (!ft_strncmp(s, split, ft_strlen(split)))
			{
				prev->next = g_vars.env_list->next;
				free(g_vars.env_list);
				ms_update_env_tail();
				return;
			}
		}
		prev = g_vars.env_list;
		g_vars.env_list = g_vars.env_list->next;
	}
}

void ms_update_env_tail(void)
{
	// printf("before tail: %s\n", g_vars.env_tail->content);
	g_vars.env_tail = g_vars.env_head;
	while (g_vars.env_tail->next->content)
	{
		// printf("current tail: %s\n", g_vars.env_tail->content);
		g_vars.env_tail = g_vars.env_tail->next;
	}
	// printf("after tail: %s\n", g_vars.env_tail->content);
}

void ms_print_oldpwd(void)
{
	if (ms_getenv("OLDPWD") == NULL)
		printf("bash: cd: OLDPWD not set\n");
	else
		printf("%s\n", ms_getenv("OLDPWD"));
}

void ms_run_pi(void)
{
	int i;
	int fd;
	char *str;

	i = 0;
	fd = open("../π.txt", O_RDONLY);
	if (fd < 1)
		return;
	str = get_next_line(fd);
	while (str)
	{
		printf("%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
}

int ms_check_executable(void)
{
	int i;
	int j;

	i = 0;
	while (i <= g_vars.exec->pipe_count)
	{
		j = 0;
		while (g_vars.exec->av[i][j])
			j++;
		if (j == 1 && g_vars.exec->av_token[i][j - 1] == 5)
			return (0 && printf("minishell: syntax error near unexpected token `newline'\n"));
		else if (j == 0)
			return (0 && printf("minishell: syntax error near unexpected token `newline'\n"));
		i++;
	}
	return (1);
}

void ms_exec_builtin(char **sentence)
{
	// ft_putstr_fd("BUILTIN\n", g_vars.stdo);
	if (!ft_strncmp(sentence[0], "echo", 5))
		ms_run_echo(sentence);
	else if (!ft_strncmp(sentence[0], "pwd", 4))
		ms_run_pwd();
	else if (!ft_strncmp(sentence[0], "env", 4))
		ms_run_env();
	else if (!ft_strncmp(sentence[0], "export", 7) && !sentence[1])
		ms_print_export();
	else if (!ft_strncmp(sentence[0], "export", 7))
		return;
	else if (!ft_strncmp(sentence[0], "cd", 3) && (sentence[1] && !ft_strncmp(sentence[1], "-", 2)))
		ms_print_oldpwd();
	else if (!ft_strncmp(sentence[0], "cd", 3))
		return;
	else if (!ft_strncmp(sentence[0], "π", 3))
		ms_run_pi();
	else
	{
		const char *errmsg = ft_strjoin("bash: ", sentence[0]);
		errmsg = ft_strjoin(errmsg, " command not found");
		printf("%s\n", errmsg);
	}
	// printf("built-in geldi zort: %s\n", sentence[0]);
}

int ms_exec(int sentence)
{
	int has_pipe;
	int pipe_fd[2];
	int status; // child process return code
	pid_t child;
	bool builtin;
	int redirection;

	builtin = false;
	redirection = 0;
	status = 0;
	has_pipe = 0;
	if (g_vars.exec->pipe_count > 0)
	{
		has_pipe = 1;
		g_vars.exec->pipe_count--;
	}
	if (has_pipe && pipe(pipe_fd) == -1)
		return (0);
	g_vars.retred = ms_isred_sentence(sentence); // redirection control
	if (g_vars.retred && g_vars.retred->type >= 3)
	{
		if (ms_redirect_parse(g_vars.exec->av[sentence], g_vars.retred->index))
			return (1);
		if (ms_redirect_manage(sentence, g_vars.retred->type, g_vars.retred->index))
			return (0);
		ms_remove_redrets(sentence, g_vars.retred->index);
		// free(&(g_vars.retred));
	}

	if (g_vars.exec->av_token[sentence][0] == 1) // burdan built-in'e gidiyor
	{
		// ft_putstr_fd("pipe yok builtin\n", 1);
		builtin = true;
		if (!ft_strncmp(g_vars.exec->av[sentence][0], "export", 7) && g_vars.exec->av[sentence][1] && !has_pipe)
		{
			ms_run_export(g_vars.exec->av[sentence][1]);
			return (1);
		}
		else if (!ft_strncmp(g_vars.exec->av[sentence][0], "cd", 3) && !has_pipe) // pipe yoksa her türlü cd geldi.
		{
			ms_run_cd(g_vars.exec->av[sentence]);
			return (1);
		}
		else if (!ft_strncmp(g_vars.exec->av[sentence][0], "unset", 6))
		{
			if (has_pipe)
				return (1);
			ms_run_unset(g_vars.exec->av[sentence][1]);
			return (1);
		}
	}
	child = fork();
	if (!child)
	{
		// ft_putstr_fd("in child\n", g_vars.stdo);
		if (!redirection && has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
			exit(31);
		if (builtin == true) // burdan built-in'e gidiyor
		{
			ms_exec_builtin(g_vars.exec->av[sentence]);
			exit(1);
		}
		else
		{
			execve(*g_vars.exec->av[sentence], g_vars.exec->av[sentence], g_vars.env);
			const char *errmsg = ft_strjoin("bash: ", *g_vars.exec->av[sentence]);
			perror(errmsg);
			exit(1);
		}
	}
	waitpid(child, &status, 0);
	g_vars.exit_status = status;
	if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
	{
		printf("[!!] dup calismadi\n");
		exit(31);
	}
	return WIFEXITED(status) && WEXITSTATUS(status);
}
