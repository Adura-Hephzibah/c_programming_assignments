#include <stdio.h>
#include <string.h>

/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	FILE *password_file = fopen("generated_passwords.txt", "r");

	if (password_file == NULL)
	{
		printf("Error opening password_file\n");
		return (1);
	}

	char input_pin[6];

	printf("Enter a PIN to crack: ");
	scanf("%s", input_pin);

	if (strlen(input_pin) != 5)
	{
		printf("Invalid input. Please enter a 5-digit PIN.\n");
		return (1);
	}


	char pin[6];
	int count = 0;

	while (fscanf(password_file, "%s", pin) != EOF)
	{
		count++;
		if (strcmp(input_pin, pin) == 0)
		{
			printf("Found the PIN after %d iterations.\n", count);
			break;
		}
	}

	printf("The probability of finding the PIN is %.6f\n", 1.0 / count);

	fclose(password_file);

	return (0);
}
