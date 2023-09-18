#include <stdio.h>
#include <string.h>
/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char employees[][30] = {"Bob Jones", "David Doe", "Alex Ode",
							"Honore Mugisha", "Ade Alao", "Ada Igwe", "Eze Caleb",
							"Emma Isaac", "Obeiro Ruto", "Almarat Denis"};
	int salary[] = {78, 170, 600, 120, 90, 580, 300, 250, 100, 550};
	float net_salary[10];

	float net, tax, security, medical;

	for (int i = 0; i < 10; i++)
	{
		if (salary[i] <= 100)
		{
			tax = 0;
			security = 0.03 * salary[i];
			medical = 0.02 * salary[i];
		}
		else if (salary[i] <= 400)
		{
			tax = 0.2 * salary[i];
			security = 0.03 * salary[i];
			medical = 0.02 * salary[i];
		}
		else
		{
			tax = 0.28 * salary[i];
			security = 0.03 * salary[i];
			medical = 0.02 * salary[i];
		}
		net = salary[i] - (tax + security + medical);
		net_salary[i] = net;
	}

	printf("Here are the names of employees and their salary details: \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%16s, Gross Salary: USD%3d, Net Salary: USD%0.2f\n",
			   employees[i], salary[i], net_salary[i]);
	}

	return (0);
}
