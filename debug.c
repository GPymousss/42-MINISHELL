#include "minishell.h"

static char	*get_token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("MOT");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR_ENTREE");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR_SORTIE");
	else if (type == TOKEN_HERE_DOC)
		return ("HERE_DOC");
	else if (type == TOKEN_APPEND)
		return ("APPEND");
	return ("INCONNU");
}

static char	*get_quote_type_str(t_quote quote)
{
	if (quote == NONE)
		return ("AUCUNE");
	else if (quote == SINGLE)
		return ("SIMPLE");
	else if (quote == DOUBLE)
		return ("DOUBLE");
	return ("INCONNU");
}

static char	*get_symbol_str(t_symbol symbol)
{
	if (symbol == REDIR_IN)
		return ("REDIR_ENTREE (<)");
	else if (symbol == REDIR_OUT)
		return ("REDIR_SORTIE (>)");
	else if (symbol == HERE_DOC)
		return ("HERE_DOC (<<)");
	else if (symbol == APPEND)
		return ("APPEND (>>)");
	return ("INCONNU");
}

static void	print_separator(char *title)
{
	int	i;
	int	len;
	int	total_width;

	total_width = 60;
	len = ft_strlen(title);
	ft_printf("\n");
	for (i = 0; i < total_width; i++)
		ft_printf("=");
	ft_printf("\n");
	for (i = 0; i < (total_width - len) / 2; i++)
		ft_printf(" ");
	ft_printf("%s\n", title);
	for (i = 0; i < total_width; i++)
		ft_printf("=");
	ft_printf("\n");
}

static void	print_tokens_detailed(t_token *tokens)
{
	t_token	*current;
	int		count;

	print_separator("TOKENS");
	if (!tokens)
	{
		ft_printf("Aucun token trouve!\n");
		return ;
	}
	current = tokens;
	count = 0;
	ft_printf("Nombre de tokens: %d\n\n", (int)get_token_count(tokens));
	while (current)
	{
		ft_printf("TOKEN #%d:\n", count);
		ft_printf("   Valeur: \"%s\"\n", current->value ? current->value : "(NULL)");
		ft_printf("   Type: %s\n", get_token_type_str(current->type));
		ft_printf("   Guillemets: %s\n", get_quote_type_str(current->quote));
		current = current->next;
		count++;
		ft_printf("\n");
	}
}

static void	print_redirection_analysis(t_redir *redir)
{
	t_redir	*current;
	int		count;

	if (!redir)
	{
		ft_printf("   Aucune redirection\n");
		return ;
	}
	current = redir;
	count = 0;
	ft_printf("   Redirections:\n");
	while (current)
	{
		ft_printf("      REDIR #%d:\n", count);
		ft_printf("         Type: %s\n", get_symbol_str(current->symbol));
		ft_printf("         Fichier: \"%s\"\n", current->file ? current->file : "(NULL)");
		current = current->next;
		count++;
	}
}

static void	print_commands_detailed(t_cmd *cmds)
{
	t_cmd	*current;
	int		cmd_count;
	int		arg_count;

	print_separator("COMMANDES");
	if (!cmds)
	{
		ft_printf("Aucune commande trouvee!\n");
		return ;
	}
	current = cmds;
	cmd_count = 0;
	ft_printf("Nombre de commandes: %d\n\n", (int)get_cmd_count(cmds));
	while (current)
	{
		ft_printf("COMMANDE #%d:\n", cmd_count);
		if (!current->args)
		{
			ft_printf("   Aucun argument!\n");
		}
		else
		{
			ft_printf("   Arguments:\n");
			arg_count = 0;
			while (current->args[arg_count])
			{
				ft_printf("      [%d] \"%s\"", arg_count, current->args[arg_count]);
				if (arg_count == 0)
					ft_printf(" (commande)");
				else
					ft_printf(" (argument)");
				ft_printf("\n");
				arg_count++;
			}
			ft_printf("   Total arguments: %d\n", arg_count);
		}
		print_redirection_analysis(current->redir);
		if (current->next)
			ft_printf("   Connecte par PIPE\n");
		else
			ft_printf("   (derniere commande)\n");
		current = current->next;
		cmd_count++;
		ft_printf("\n");
	}
}

void	debug_full_parsing(t_shell *shell, char *input)
{
	ft_printf("\nDEBUG PARSING: \"%s\"\n", input);
	
	shell->input = input;
	if (tokenize(shell->input, &shell->tokens) != 0)
	{
		ft_printf("ECHEC DE LA TOKENISATION!\n");
		return ;
	}
	
	print_tokens_detailed(shell->tokens);
	
	expand_tokens(shell, shell->tokens);
	ft_printf("Expansion terminee.\n");
	
	if (parse_tokens_to_cmds(shell, shell->tokens) != 0)
	{
		ft_printf("ECHEC DU PARSING DES COMMANDES!\n");
		return ;
	}
	
	print_commands_detailed(shell->cmds);
	print_separator("PARSING TERMINE");
	ft_printf("Parsing reussi!\n\n");
}
