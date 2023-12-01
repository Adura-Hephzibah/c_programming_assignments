#include <stdio.h>

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int d1, d2, d3, d4, d5;
	FILE *passwordFile = fopen("generated_passwords.txt", "w");

	if (passwordFile == NULL)
	{
		printf("Error opening file\n");
		return (1);

	}

	for (d1 = 0; d1 <= 9; d1++)
		for (d2 = 0; d2 <= 9; d2++)
			for (d3 = 0; d3 <= 9; d3++)
				for (d4 = 0; d4 <= 9; d4++)
					for (d5 = 0; d5 <= 9; d5++)
						fprintf(passwordFile, "%d%d%d%d%d\n", d1, d2, d3, d4, d5);

	fclose(passwordFile);

	printf("PINs generated and saved in file\n");

	return (0);
}
