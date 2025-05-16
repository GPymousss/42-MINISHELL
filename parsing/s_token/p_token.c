// #include "../parsing.h"

// int	is_metacharacter(char c)
// {
// 	return (ft_strchr(" \t\n|&;()<>", c) != NULL);
// }

// static int	handle_operator(char **input, t_token **tokens)
// {
// 	char	operator[3];
// 	int		i;

// 	ft_memset(operator, 0, 3);
// 	i = 0;
// 	operator[i] = (*input)[i];
// 	if (((*input)[i] == '>' && (*input)[i + 1] == '>') ||
// 		((*input)[i] == '<' && (*input)[i + 1] == '<') ||
// 		((*input)[i] == '|' && (*input)[i + 1] == '|') ||
// 		((*input)[i] == '&' && (*input)[i + 1] == '&'))
// 	{
// 		i++;
// 		operator[i] = (*input)[i];
// 	}
// 	token_add_back(tokens, init_token(ft_strdup(operator), NONE, NULL));
// 	*input += i + 1;
// 	return (1);
// }

// static int	handle_quote(char **input, t_token **tokens, t_quote type)
// {
// 	char	*content;
// 	int		i;

// 	i = 1;
// 	while ((*input)[i] && (*input)[i] != (*input)[0])
// 		i++;
// 	if ((*input)[i] != (*input)[0])
// 		return (printf("unclosed quote\n"), 0);
// 	content = ft_substr(*input, 1, i - 1);
// 	token_add_back(tokens, init_token(content, type, NULL));
// 	*input += i + 1;
// 	return (1);
// }

// static int	process_token(char **input, t_token **tokens)
// {
// 	char	*start;
// 	t_quote	type;

// 	start = *input;
// 	if (**input == '\'' || **input == '"')
// 	{
// 		if (**input == '\'')
// 			type = SINGLE;
// 		else
// 			type = DOUBLE;
// 		if (!handle_quote(input, tokens, type))
// 			return (0);
// 	}
// 	else if (ft_strchr("();&><|", **input))
// 		handle_operator(input, tokens);
// 	else
// 	{
// 		if (!handle_default_token(input, start, tokens))
// 			return (0);
// 	}
// 	return (1);
// }

// t_token	*tokenize(char *input)
// {
// 	t_token	*tokens;

// 	tokens = NULL;
// 	while (*input)
// 	{
// 		while (ft_isspace(*input))
// 			input++;
// 		if (!*input)
// 			break ;
// 		if (!process_token(&input, &tokens))
// 			return (NULL);
// 	}
// 	return (tokens);
// }
