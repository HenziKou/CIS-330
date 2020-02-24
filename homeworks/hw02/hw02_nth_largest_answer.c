/*
Henzi Kou
CIS 330
Jee Whan Choi
Homework 2

19 April 2019
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "test.dat"

#define uint32_t u_int32_t

int  arg_test(int argc, char **argv);
void conversion_test();
void load_data(int **int_array, uint32_t *array_size);
int  find_nth(int *int_array, uint32_t array_size, int n);
void print_array(uint32_t size, int *arr);

int main(int argc, char **argv)
{
    int valid = arg_test(argc, argv);
    // Test function for atoi
    conversion_test(argc, argv);
    
    int nth = -3;
 
    if(valid) {
        int *int_array = NULL;
        uint32_t array_size = 0;
        load_data(&int_array, &array_size);

        // This function prints the content of the array - debugging tool
        print_array(array_size, int_array);

        // TODO: Insert your code here (1)
        int n = atoi(argv[1]);

	// Input must be greater than 0
	if (n < 1)
	{
	    printf("Some error!\n");
	    exit(EXIT_FAILURE);
	}

        // ------------------------

        nth = find_nth(int_array, array_size, n);

        if(nth >= 0) {
            printf("---- Answer ----\n");
            printf("The nth value is %d\n", int_array[nth]);
            printf("--------\n");
        } else if(nth == -1) {
            printf("n is too large!\n");
        } else if(nth == -2) {
            printf("Some error!\n");
        } else {
            // Do nothing
        }
    } else {
        // Do nothing
    }
    
    return 0;
}



int arg_test(int argc, char **argv)
{
    int return_val = 0;
    if(argc < 2) {
        fprintf(stderr, "Error: no input entered\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else if(argc > 2) {
        fprintf(stderr, "Error: too many inputs\n");
        fprintf(stderr, "usage: %s <n>\n", argv[0]);
        fprintf(stderr, "\n");
    } else {
        return_val = 1;
    }
    return return_val;
}

void conversion_test()
{
    printf("---- ATOI Sample Usage ----\n");
    char *num_str = "101";
    int num = atoi(num_str);
    printf("The number is %d\n", num);
    printf("--------\n\n");
}

void load_data(int **int_array, uint32_t *array_size)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
    }
    fclose(fp);

    int *tmp_array = (int*) malloc(sizeof(int) * cnt);
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        tmp_array[cnt] = tmp;
        cnt++;
    }
    fclose(fp);
    
    *int_array = tmp_array;
    *array_size = cnt;
}

// Given n as input, find the nth largest value
// in the list of integers loaded from the file.
// If n is larger than the number of integers,
// return -1.
// Return -2 for any other errors.
// NOTE 1:
// The file used for grading will be different from
// the file given with the homework - it will have
// different number of integers and different integer
// values

int compare(const void *a, const void *b)
{
    // Helper function to compare values for qsort()
    return ( *(int*)a - *(int*)b );
}

int find_nth(int *int_array, uint32_t array_size, int n)
{
    // TODO: Insert your code here (2)
    // Create a copy array and sort it
    int j = 0;
    int *copy = (int*) malloc(sizeof(int) * array_size);

    for (int i = 0; i < array_size; i++)
    {
	copy[i] = int_array[i];
    }

    // Using qsort to sort array in-place
    qsort(copy, array_size, sizeof(int), compare);

    // Remove duplicates
    for (int i = 1; i < array_size; i++)
    {
	if (copy[i] != copy[j])
	{
	    j++;
	    copy[j] = copy[i];	// Move to front
	}
    }

    // New array size for copy array
    int copy_array_size = j + 1;

    // n can't be less than 1, nor greater than the total number of integers
    if (n <= 0)
	return -2;
    else if (n > copy_array_size)
	return -1;
    else {
	// Return the index of the nth largest integer
	int nth = copy[copy_array_size - n];

	for (int i = 0; i < array_size; i++)
	{
	    if (int_array[i] == nth)
		return i;
	}
    }

    return -3;
    // ------------------------

}

void print_array(uint32_t size, int *arr)
{
   printf("---- Print Array ----\n");
    printf("This file has %d elements\n", size);
    printf("#\tValue\n");
    for(int i = 0; i < size; i++) {
        printf("%d\t%d\n", i, arr[i]);
    }
   printf("--------\n\n");
}

