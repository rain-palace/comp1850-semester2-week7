/* Program to compute summary statistics for numbers in a file */

#include <math.h>
#include <stdio.h>

#define MAX_LENGTH 80
#define MAX_SIZE 10000


void read_data(const char* filename, float data[], int* size)
{
    char line[MAX_LENGTH];
    float value;

    *size = 0;
    FILE* infile = fopen(filename, "r");

    if (infile != NULL) {
        for (int i = 0; i < MAX_SIZE; ++i) {
            if (fgets(line, MAX_LENGTH, infile) == NULL) {
                break;
            }

            sscanf(line, "%f", &value);
            if(value>=0){
            data[i] = value;
            (*size)++;
            }
        }

        fclose(infile);
    }
}


float mean_value(const float data[], int size)
{
    float sum_values = 0.0f;

    for (int i = 0; i < size; ++i) {
        sum_values += data[i];
    }

    return sum_values / size;
}


float standard_deviation(const float data[], int size, float mean)
{
    float sum_squared_diff = 0.0f;

    for (int i = 0; i < size; ++i) {
        float diff_mean = data[i] - mean;
        sum_squared_diff += diff_mean * diff_mean;
    }

    return sqrtf(sum_squared_diff / size);
}


void display_stats(float mean, float std_dev)
{
    printf("Mean    = %.3f\n", mean);
    printf("Std dev = %.3f\n", std_dev);
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./stats <filename>\n");
        return 1;
    }

    int size;
    float data[MAX_SIZE];

    read_data(argv[1], data, &size);

    float mean = mean_value(data, size);
    float std_dev = standard_deviation(data, size, mean);

    display_stats(mean, std_dev);

    return 0;
}
