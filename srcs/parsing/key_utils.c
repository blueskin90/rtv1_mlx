#include "rtv1.h"

t_elem		*find_elem_by_key(t_elem *elem, char *key)
{
	t_elem		*curr;

	curr = elem;
	while (curr)
	{
		if (curr->key != NULL && !ft_strcmp(curr->key, key))
		{
			printf("KEY FOUND : \n");
			show_elem(curr);
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

