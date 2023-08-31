#include "shell.h"

/**
 * _myhistory - display history line with numbers
 * @info: Structure contains potential arguments.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return 0;
}

/**
 * unset_alias - remove alias from alias list.
 * @info: parameter structure 
 * @str: the string alias
 *
 * Return: 0 on success, otherwise 1
 */
int unset_alias(info_t *info, char *str)
{
	char *p;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	char c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return ret;
}

/**
 * set_alias - adds/updates an alias in alias list.
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: 0 on success,itherwise 1
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	if (!*++p)
		return unset_alias(info, str);

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias node.
 * @node: alias node
 *
 * Return: 0 on success otherwise 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node) {
		p = _strchr(node->str, '=');
	for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}

/**
 * _myalias - displays/sets aliases.
 * @info: Struct contains potential arguments.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1) {
		node = info->alias;
	while (node) {
		print_alias(node);
		node = node->next;
	}
	return 0;
	}

	for (i = 1; info->argv[i]; i++) {
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return 0;
}

