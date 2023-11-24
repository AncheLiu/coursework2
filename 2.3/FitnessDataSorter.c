#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

//sort function
void Sort(FitnessData arr[], int n) 
{
    FitnessData temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j].steps > arr[j+1].steps)
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }         
}



int main() {
    char line[100];
    char filename[100];
    char target[100];
    FitnessData data[1000];
    printf("Enter Filename: ");
    scanf("%s", filename);
    strcpy(target, filename);
    strcat(target, ".txt");
    
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: invalid file\n");
        return 1;
    }
    int count = 0;
    while (fgets(line, 1000, file))
    {
        tokeniseRecord(line, ',', data[count].date, data[count].time, &data[count].steps);
        count++;
    }
    fclose(file);
    int a = strlen(data[0].date);
    int b = strlen(data[0].time);
    for (int i = 0; i < count; i++)
    {
        if (strlen(data[i].date) != a)
        {
            printf("Error: invalid file\n");
            return 1;
        }
        if (strlen(data[i].time) != b)
        {
            printf("Error: invalid file\n");
            return 1;
        }
    }
    
    printf("Data sorted and written to %s\n",target);
    FILE *file1 = fopen(target, "w+");
    Sort(data, count);
    for ( count--; count >= 0; count--)
    {
        fprintf(file1,"%s\t%s\t%d\n", data[count].date, data[count].time, data[count].steps);
    }
    fclose(file1);
    return 0;
}
