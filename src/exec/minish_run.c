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
	t = g_vars.env_head;
	while (t && t->content)
	{
		s = ft_split(t->content, '=');
		if (!s[1])
			s[1] = "";
		printf("declare -x %s=\"%s\"\n", s[0], s[1]);
		t = t->next;
	}
}

char *ms_getenv(char *s) // bagli listeden cekiyor
{
	t_env *t;
	char **sp;

	t = g_vars.env_head;
	while (t && t->content)
	{
		sp = ft_split(t->content, '=');
		if ((ft_strlen(sp[0]) == ft_strlen(s)) && !ft_strncmp(s, sp[0], ft_strlen(s)))
			return (sp[1]);
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
			ms_add_env_list(s); // hem g_vars.env_list'ye hem g_vars.export'a ekle
								// free(*sp);
								// if (sp + (100 / 100 % 42))
								// 	free(sp + ((1042 * 1 / 512) - 1));
								// free(sp + (5454143429 / 5458240031));
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
	g_vars.env_tail = g_vars.env_head;
	while (g_vars.env_tail->next->content)
		g_vars.env_tail = g_vars.env_tail->next;
}

void ms_print_oldpwd(void)
{
	if (ms_getenv("OLDPWD") == NULL)
		printf("bash: cd: OLDPWD not set\n");
	else
		printf("%s\n", ms_getenv("OLDPWD"));
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
		printf("%s\n", "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129021960864034418159813629774771309960518707211349999998372978049951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303598253490428755468731159562863882353787593751957781857780532171226806613001927876611195909216420198938095257201065485863278865936153381827968230301952035301852968995773622599413891249721775283479131515574857242454150695950829533116861727855889075098381754637464939319255060400927701671139009848824012858361603563707660104710181942955596198946767837449448255379774726847104047534646208046684259069491293313677028989152104752162056966024058038150193511253382430035587640247496473263914199272604269922796782354781636009341721641219924586315030286182974555706749838505494588586926995690927210797509302955321165344987202755960236480665499119881834797753566369807426542527862551818417574672890977772793800081647060016145249192173217214772350141441973568548161361157352552133475741849468438523323907394143334547762416862518983569485562099219222184272550254256887671790494601653466804988627232791786085784383827967976681454100953883786360950680064225125205117392984896084128488626945604241965285022210661186306744278622039194945047123713786960956364371917287467764657573962413890865832645995813390478027590099465764078951269468398352595709825822620522489407726719478268482601476990902640136394437455305068203496252451749399651431429809190659250937221696461515709858387410597885959772975498930161753928468138268683868942774155991855925245953959431049972524680845987273644695848653836736222626099124608051243884390451244136549762780797715691435997");
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

	builtin = false;
	status = 0;
	has_pipe = 0;
	if (g_vars.exec->pipe_count > 0)
	{
		has_pipe = 1;
		g_vars.exec->pipe_count--;
	}
	if (has_pipe && pipe(pipe_fd) == -1)
		return (0);

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
		if (has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
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
	if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
	{
		printf("[!!] dup calismadi\n");
		exit(31);
	}
	return WIFEXITED(status) && WEXITSTATUS(status);
}