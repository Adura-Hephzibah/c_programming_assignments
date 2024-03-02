#include <stdio.h>
#include <stdlib.h>

/* Node structure definition */
/**
 * struct Node - struct to represent a node holding file size in KB
 * @data: size of files
 * @left: left child
 * @right: right child
 */
typedef struct Node
{
	int data;
	struct Node *left, *right;
} Node;

/**
 * newNode - Function to create a new node
 * @data: The data to be inserted into the node
 *
 * Return: A pointer to the newly created node
 */
Node *newNode(int data)
{
	Node *node = (Node *)malloc(sizeof(Node));

	node->data = data;

	/* Initialize left and right children as NULL */
	node->left = node->right = NULL;

	return (node);
}

/**
 * insertNode - Function to insert a new node into the BST
 * @node: The root of the BST
 * @data: The data to be inserted
 *
 * Return: The root of the BST after insertion
 */
Node *insertNode(Node *node, int data)
{
	/* If the tree is empty, assign a new node address */
	if (node == NULL)
		return (newNode(data));

	/* Else, recur down the tree */
	if (data < node->data)
		node->left  = insertNode(node->left, data);
	else if (data > node->data)
		node->right = insertNode(node->right, data);

	/* return the (unchanged) node pointer */
	return (node);
}

/**
 * printInOrder - Function to print the BST in-order
 * @node: The root of the BST
 */
void printInOrder(Node *node)
{
	/* first recur on left child */
	if (node == NULL)
		return;
	printInOrder(node->left);

	/* then print the data of node */
	printf("%d ", node->data);

	/* now recur on right child */
	printInOrder(node->right);
}

/**
 * minValueNode - Function to find the node with the minimum value
 * @node: The root of the BST
 *
 * Return: The node with the minimum value
 */
Node *minValueNode(Node *node)
{
	Node *current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return (current);
}

/**
 * deleteNode - Function to delete a node from the BST
 * @root: The root of the BST
 * @data: The data of the node to be deleted
 *
 * Return: The root of the BST after deletion
 */
Node *deleteNode(Node *root, int data)
{
	/* base case */
	if (root == NULL)
		return (root);

	/* If the key to be deleted is smaller than the root's key */
	if (data < root->data)
		root->left = deleteNode(root->left, data);

	/* If the key to be deleted is greater than the root's key */
	else if (data > root->data)
		root->right = deleteNode(root->right, data);

	/* if key is same as root's key */
	else
	{
		/* node with only one child or no child */
		if (root->left == NULL)
		{
			Node *temp = root->right;

			free(root);
			return (temp);
		}
		else if (root->right == NULL)
		{
			Node *temp = root->left;

			free(root);
			return (temp);
		}
		/* node with two children */
		Node *temp = minValueNode(root->right);

		root->data = temp->data;

		root->right = deleteNode(root->right, temp->data);
	}
	return (root);
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int files[] = {20, 15, 8, 16, 4, 5, 9, 10, 13, 11, 12,
															0, 14, 17, 19, 6, 18, 3, 2, 1};
	int n = sizeof(files) / sizeof(files[0]);

	Node *root = NULL;

	/* insertNode file sizes into the BST */
	root = insertNode(root, files[0]);

	for (int i = 1; i < n; i++)
		insertNode(root, files[i]);

	/* print the BST in-order */
	printf("BST before deletion:\n");
	printInOrder(root);
	printf("\n");

	/* find the minimum file size */
	Node *min = minValueNode(root);

	printf("Minimum file size: %dKB\n", min->data);

	/* delete the minimum file size if it's less than 1KB */
	if (min->data < 1)
	{
		printf("Deleting file of size less than 1KB...\n");
		root = deleteNode(root, min->data);
	}

	/* print the BST in-order after deletion */
	printf("BST after deletion:\n");
	printInOrder(root);
	printf("\n");

	return (0);
}
