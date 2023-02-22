#include <stdlib.h>
#include <stdio.h>

typedef struct s_value
{
	char    *value;
}	t_value;

typedef struct s_len
{
	int len;
}	t_len;

typedef struct s_list
{
    void    *content;
    struct s_list	*next;
}   t_list;

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = NULL;
	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		if (lst && new)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
    return (*lst);
}

t_value *item_value(char *str)
{
    t_value *item;
    
    item = malloc(sizeof(t_value));
    item->value = str;
    return (item);
}

t_len *item_len(char *str)
{
    t_len *item;
    int i;

    i = 0;
    while (str[i])
        i++;
    item = malloc(sizeof(t_len));
    item->len = i;
    return (item);
}

int main(int ac, char **av)
{
    int i;
    t_value *v_content;
    t_list  *v_new;
    t_list  *v_head;
    t_len   *l_data;
    t_list  *l_new;
    t_list  *l_head;

    i = 0;
    v_head = NULL;
    l_head = NULL;
    while (i < ac)
    {
        v_content = item_value(av[i]);
        v_new = ft_lstnew(v_content);
        v_head = ft_lstadd_back(&v_head, v_new);
        i++;
    }
    i = 0;
    while (i < ac)
    {
        l_data = item_len(av[i]);
        l_new = ft_lstnew(l_data);
        l_head = ft_lstadd_back(&l_head, l_new);
        i++;
    }
    while (v_head && l_head)
    {
        printf("%s = %d\n", ((t_value *)(v_head->content))->value, ((t_len *)(l_head->content))->len);
        v_head = v_head->next;
        l_head = l_head->next;
    }
}
