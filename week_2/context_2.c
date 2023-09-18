#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
/**
 * main - Entry Point
 *
 * Return: Always 0 (Success)
 */

char randomSpecial(void)
{
    char special[] = "!@#$%^&*()_+-=[]{}|;:',.<>?";
    int numChars = strlen(special);
    int randomIndex = rand() % numChars;
    return (special[randomIndex]);
}

char randomNumber(void)
{
    return (rand() % 10);
}

int main(void)
{
    srand(time(NULL));

    char first[100];
    char second[100];
    char secondWord[100];

    /* Request two words*/
    printf("Enter the first word: ");
    scanf("%s", first);

    printf("Enter the second word: ");
    scanf("%s", second);

    /* Capitalize first letter of first word*/
    if (islower(first[0]))
    {
        first[0] = toupper(first[0]);
    }

    /*generate random special character*/
    char specialOne = randomSpecial();

    /* Reverse second word in lower case*/
    int length = strlen(second);
    for (int i = length - 1; i >= 0; i--)
    {
        if (!islower(second[i]))
        {
            second[i] = tolower(second[i]);
        }
        char temp = second[i];

        secondWord[length - 1 - i] = temp;
    }

    /* generate second random special character */
    char specialTwo = randomSpecial();

    /* Combine the different parts together*/
    char password[150];
    snprintf(password, sizeof(password), "%c%c%s%c%d",
             first[0], specialOne, secondWord, specialTwo, randomNumber());

    /* If the password is not up to 8 characters*/
    int passwordLength = strlen(password);
    while (passwordLength < 8)
    {
        char randomChar = rand() % 94 + 33;
        strncat(password, &randomChar, 1);
        passwordLength++;
    }

    printf("The strong password is %s\n", password);
    return (0);
}
