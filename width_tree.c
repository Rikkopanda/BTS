
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct s_node
{
	int 			value;
	struct s_node 	*left;
	struct s_node 	*right;
};

int g_len = 0;
int g_len2 = 0;

int search_longest_path(struct s_node *n, int len)
{
	int len2;
	// printf("hello\n");
	if (n == NULL)
	{
		printf("\tleaf = %d \n", len - 1);
		if (g_len < len - 1)
			g_len = len - 1;
		return (len - 1);
	}
	printf("left");
	len = search_longest_path(n->left, len + 1);
	if (len == 0)
	{
		g_len2 = g_len;
		g_len = 0;
		g_len2++;//for root
	}
	printf("right");
	len2 = search_longest_path(n->right, len + 1);
	if (len == 0)
	{
		g_len2 += g_len;
		printf("total len =  %d\n", g_len2);
		printf("%d(len = %d, len2 = %d) \n", n->value, len, len2);
	}
	if (len >= len2)
		return len - 1;
	else
		return len2 - 1;
}

struct s_node 	*node_new(int value)
{
	struct s_node *new = malloc(sizeof(struct s_node));

	(new)->value = value;
	(new)->right = NULL;
	(new)->left = NULL;
	return (new);
}

void insert_node(struct s_node **n, int value)
{
	if (*n == NULL)
		*n = node_new(value);
	else if (value < (*n)->value)
		insert_node(&(*n)->left, value);
	else if (value > (*n)->value)
		insert_node(&(*n)->right, value);
}

/*
	traverse left first, then right. recursively
*/
void in_order_traverse(struct s_node *n, int i)
{
	if (n == NULL)
		return;
	in_order_traverse(n->left, i + 1);
	printf("%d(%d) ", n->value, i);
	in_order_traverse(n->right, i + 1);
}


/*
	traverse left first, then right. recursively
*/
void print_reverse_in_order_traverse(struct s_node *n, int space)
{
	if (n == NULL)
		return;

	space += 5;

	print_reverse_in_order_traverse(n->right, space);


	for (int i = 0; i < space; i++)
		printf(" ");

	printf("%d", n->value);

	printf("\n");

	print_reverse_in_order_traverse(n->left, space);
}



/*
	free starting from the leaf up untill last, the root
*/
void post_order_free(struct s_node *n, int i)
{
	if (n == NULL)
		return;
	post_order_free(n->left, i + 1);
	post_order_free(n->right, i + 1);
	free(n);
	n = NULL;
}

int main(void)
{

	struct s_node *root = NULL;

    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    insert_node(&root, 20);
    insert_node(&root, 40);
    insert_node(&root, 60);
    insert_node(&root, 80);
    insert_node(&root, 10);
    insert_node(&root, 25);
    insert_node(&root, 35);
    insert_node(&root, 45);
    insert_node(&root, 55);

	in_order_traverse(root, 0);
	printf("\n");
	search_longest_path(root, 0);

	print_reverse_in_order_traverse(root, 0);

	post_order_free(root, 0);
}





