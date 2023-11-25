#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
char filename[100];
FITNESS_DATA data[1000];
// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {
    char line[100];
    int go = 1;
    while (go)
    {
        char choice;
        int count;
        char steps[1000];
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");
        printf("Enter choice: ");
        choice = getchar();
        while (getchar() != '\n');
        switch (choice)
        {
        case 'A':
        case 'a':
            count = 0;            
            printf("Input filename: ");
            fgets(line, 100, stdin);
            sscanf(line, " %s ", filename);
            FILE *file = fopen(filename, "r");
            if (!file)
            {
                printf("Error: Could not find or open the file.\n");
                exit(1);
                break;
            }
            while (fgets(line, 100, file))
            {
                tokeniseRecord(line, ",", data[count].date, data[count].time, steps);
                data[count].steps = atoi(steps);
                count++;
            }
            printf("File successfully loaded.\n\n");
            fclose(file);
            break;
        
        case 'B':
        case 'b':
            printf("Total records: %d\n\n", count);
            break;

        case 'C':
        case 'c': 
        {
            int min;
            int num = 0;
            min = data[0].steps;
            for (int i = 0; i < count; i++)
            {
                if (min > data[i].steps)
                {
                    min = data[i].steps;
                    num = i;
                }
            }
            printf("Fewest steps: %s %s\n\n", data[num].date, data[num].time);
            break;
        }
        case 'D':
        case 'd':
        {
            int max = data[0].steps;
            int num = 0;
            for (int i = 0; i < count; i++)
            {
                if (max < data[i].steps)
                {
                    max = data[i].steps;
                    num = i;
                }
            }
            printf("Largest steps: %s %s\n\n", data[num].date, data[num].time);
            break;
        }
        case 'E':
        case 'e':
        {
            int total = 0;
            for (int i = 0; i < count; i++)
            {
                total += data[i].steps;
            }
            int mean = (total + count / 2) / count;

            printf("Mean step count: %d\n\n", mean);
            break;
        }
        case 'F':
        case 'f':
        {
            int len = 0, temp_len = 0, end, initial;
            for (int i = 0; i < count; i++)
            {
                if (data[i].steps>500)
                {
                    temp_len ++;
                    if (temp_len > len)
                    {
                        len = temp_len;
                        end = i;
                    }
                }
                else
                {
                    temp_len = 0;
                }
            }
            initial = end - len + 1;
            printf("Longest period start: %s %s\n",data[initial].date,data[initial].time);
            printf("Longest period end: %s %s\n\n",data[end].date,data[end].time);
            break;
        }
        case 'Q':
        case 'q':
            go = 0;
            return 0;
            break;
        default:
            printf("Invalid choice. Try again.\n\n");
            break;
        }
    }
}









