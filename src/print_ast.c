#include "../mini.h"

char		*type_to_str(int type);
void		print_command(t_cmd *command);
char		*operator_type_to_str(int type);
void		printTree(t_cmd *command, int depth, int isRight, int *branch);

void	print_AST_test(t_cmd *command)
{
	int array[1024] = {0};

	printTree(command, 0, 0, array);
}

void print_command(t_cmd *command)
{
	int 	i;
	// char	*infile = "STDIN";
	// char	*outfile = "STDOUT";

	i = -1;
    if (command->type == CMD || command->type == SUBSHELL)
    {
		if (command->type == SUBSHELL && command->args)
			printf("(\"%s\")", command->args[++i]);
		else if (command->args)
			printf("%s", command->args[++i]);
		while (command->args && command->args[++i] != NULL)
		{
			printf(" (\"%s\")", command->args[i]);
		}
	}

	printf ("%s", operator_type_to_str(command->type));
}

void printTree(t_cmd *command, int depth, int isRight, int *branch) {
    if (depth > 0) {
        for (int i = 0; i < depth - 1; i++) {
            if (branch[i]) printf("│   ");
            else printf("    ");
        }
        printf("%s", isRight ? "└──" : "├──");
    }

    if (command == NULL) {
        printf("NULL\n");
        return;
    }

    print_command(command);
    printf("\n");

    if (command->left != NULL || command->right != NULL) {
        branch[depth] = (command->right != NULL);
        printTree(command->left, depth + 1, command->right == NULL, branch);
        printTree(command->right, depth + 1, 1, branch);
    }
}

char *operator_type_to_str(int type)
{
	if (type == AND)
		return (ft_strdup("AND"));
	if (type == OR)
		return (ft_strdup("OR"));
	if (type == PIPE)
		return (ft_strdup("PIPE"));
	return (NULL);
}

bool is_operator_type(int type) {
    return type == AND || type == OR || type == PIPE;
}

bool is_redirection_type(int type) {
    return type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND || type == HEREDOC;
}

char *type_to_str(int type)
{
	if (type == CMD)
		return (ft_strdup("CMD"));
	if (is_operator_type(type))
		return (ft_strdup("OPERATOR"));
	if (is_redirection_type(type))
		return (ft_strdup("REDIRECTION"));
	if (type == SUBSHELL)
		return (ft_strdup("PARENTHESIS"));
	return (NULL);
}
