#include "rakia_hakim.h"

/**
 * display_list - Print the contents of a linked list
 * @list: Pointer to the linked list
 * Return: Number of elements in the list
 */
size_t display_list(list_t *list)
{
	list_t *current_node = list;
	int count = 0;
	int str_len = 0;

	if (list == NULL)
		return (0);

	while (current_node != NULL)
	{
		if (current_node->var == NULL)
		{
			write(STDOUT_FILENO, "(nil)", 5);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			str_len = 0;
			while ((current_node->var)[str_len] != '\0')
				str_len++;
			write(STDOUT_FILENO, current_node->var, str_len);
			write(STDOUT_FILENO, "\n", 1);
		}
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * add_to_end - Add a node to the end of a linked list
 * @head: Pointer to the pointer to the head of the linked list
 * @data: Data to be added to the new node
 * Return: Pointer to the new linked list
 */
list_t *add_to_end(list_t **head, char *data)
{
	list_t *new_node;
	list_t *current_node;

	if (head == NULL || data == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->var = _strdup(data);
	new_node->next = NULL;

	current_node = *head;
	if (current_node != NULL)
	{
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (*head);
}

/**
 * delete_node_at_index - Remove a node at a specific index
 * @head: Pointer to the pointer to the head of the linked list
 * @index: Index of the node to be removed
 * Return: 1 if successful, -1 if failed
 */
int delete_node_at_index(list_t **head, int index)
{
	list_t *new_head;
	list_t *current_node;
	int count = 0;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		current_node = (*head)->next;
		free((*head)->var);
		free(*head);
		*head = current_node;
		return (1);
	}

	count = 1;
	new_head = *head;
	while (count < index)
	{
		if (new_head == NULL)
			return (-1);
		new_head = new_head->next;
		count++;
	}

	current_node = new_head->next;
	new_head->next = current_node->next;
	free(current_node->var);
	free(current_node);
	return (1);
}

/**
 * free_linked_list - Free the memory of a linked list
 * @list: Pointer to the linked list
 */
void free_linked_list(list_t *list)
{
	list_t *current_node;

	while (list != NULL)
	{
		current_node = list;
		list = list->next;
		free(current_node->var);
		free(current_node);
	}
}
