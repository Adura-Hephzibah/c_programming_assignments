#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * struct Student - struct to represent a student
 * @firstName: data
 * @lastName: data
 * @email: data
 * @age: data
 * @next: pointer to next node
 */
typedef struct Student
{
	char *firstName;
	char *lastName;
	char *email;
	int age;
	struct Student *next;
} Student;


/**
 * addStudentMiddle - to add a student in the middle of the linked list
 * @head_ref: array
 * @new_student: student to add in middle
 * @position: index to add student
 * Return: A
 */
void addStudentMiddle(Student **head_ref, Student *new_student, int position)
{
	Student *current = *head_ref;

	/* Traverse till the point where new node is to be inserted */
	for (int i = 0; current != NULL && i < position - 1; i++)
		current = current->next;

	/* Insert the new node at the desired position */
	new_student->next = current->next;
	current->next = new_student;
}

/**
 * deleteLastStudent - to delete the last student in the linked list
 * @head_ref: argument
 * Return: printed list
 */
void deleteLastStudent(Student **head_ref)
{
	Student *temp = *head_ref;
	Student *prev = NULL;

	/* Traverse to the last node */
	while (temp->next != NULL)
	{
		prev = temp;
		temp = temp->next;
	}

	/* Change the next of second last node to NULL */
	if (prev)
		prev->next = NULL;

	/* Delete last node */
	free(temp);
}

/**
 * printList - to print the linked list
 * @node: argument
 * Return: printed list
 */
void printList(Student *node)
{
	while (node != NULL)
	{
		printf("Name: %s %s ", node->firstName, node->lastName);
		printf("Email: %s ", node->email);
		printf("Age: %d\n", node->age);
		node = node->next;
	}
	printf("\n");
}

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	/* Initialize head of the linked list */
	Student *head = NULL;

	char *firstNames[] = {"John", "Emma", "Michael", "Sophia",
													"William", "Olivia", "James", "Amelia",
														"Benjamin", "Isabella"};
	char *lastNames[] = {"Smith", "Johnson", "Williams", "Brown",
										"Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
	char *emails[] = {"john@example.com", "emma@example.com",
								"michael@example.com", "sophia@example.com",
										"william@example.com", "olivia@example.com",
											"james@example.com", "amelia@example.com",
												"benjamin@example.com", "isabella@example.com"};
	int ages[10] = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};


	/* Create 10 students and add them to the linked list */
	for (int i = 9; i >= 0; i--)
	{
		Student *new_student = (Student *)malloc(sizeof(Student));

		new_student->firstName = firstNames[i];
		new_student->lastName = lastNames[i];
		new_student->email = emails[i];
		new_student->age = ages[i];
		new_student->next = head;
		head = new_student;
	}


	/* Print the linked list */
	printf("Linked List before operations:\n");
	printList(head);

	/* Create a new student to be added in the middle */
	Student *middle_student = (Student *)malloc(sizeof(Student));

	middle_student->firstName = "Middle";
	middle_student->lastName = "Student";
	middle_student->email = "middle.student@example.com";
	middle_student->age = 25;

	/* Add the new student in the middle of the linked list*/
	addStudentMiddle(&head, middle_student, 5);

	/* Print the linked list after adding a student */
	printf("Linked List after adding a student:\n");
	printList(head);

	/* Delete the last student in the linked list */
	deleteLastStudent(&head);

	/* Print the linked list after deleting a student */
	printf("Linked List after deleting a student:\n");
	printList(head);

	return (0);
}
