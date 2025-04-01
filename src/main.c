#include "csv_utils.h"
#include <stdio.h>
#include <stdlib.h>

// function description after the main function
double lagrange_interpolation(float* nodes, double* values, int target, int nLength);

int main(void) {

    // take size of the data 
    // (number of nodes) as user input
    int size;
    printf("How many nodes does your datasheet have: ");
    scanf("%d", &size);

    // dynamically allocate memory for nodes and values
    float* nodes = (float *)malloc(size * sizeof(float));
    double* values = (double *)malloc(size * sizeof(double));
    if(nodes == NULL || values == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // extract nodes and values and insert them
    // in the pre defined arrays
    get_nodes_values(nodes, values);

    // flag to check for first iteration in csv creation
    int first = 1;

    // this for loop adds an entry for every node in the range
    // and calculates its approximate value and error percentage
    // it then adds those values in a new csv file for visualization
    for(int i = 0; i < size; i++) {
        if(i > 0) first = 0;

        double approx = lagrange_interpolation(nodes, values, i, size);
        double error = (values[i] - approx) / values[i] * 100;

        if(error < 0) error *= -1.0f;
        
        add_approximation(nodes[i], error, first, values[i], approx);
    }

    // free memory to prevent leaks
    free(nodes);
    free(values);
    return 0;
}

/* largrange interpolation function
Function Parameters:
[int* nodes]:     This array of integers should have all the nodes/arguments
[double* values]: An array of type double that should have the respective y
                  values for the given x values in 'nodes'
[int target]:     The position for which the approximation needs to be made
[int nLength]:    The total number of nodes given for this approximation
*/
double lagrange_interpolation(float* nodes, double* values, int target, int nLength) {
    double phiX = 0;
    float targetNode = nodes[target];

    for(int i = 0; i < nLength; i++) {
        if(nodes[i] == targetNode) continue;

        double numerator = 1.0f;
        double denominator = 1.0f;

        for(int x = 0; x < nLength; x++) {
            // if x = i, then skip iteration, removing 
            // this will cause a divide by zero error
            if(x == i || nodes[x] == targetNode) continue;

            // numerator is the product of
            // target x value - the nodes
            numerator *=  (targetNode - nodes[x]);

            // denominator is the product of 
            // each node - the other nodes
            denominator *= (nodes[i] - nodes[x]);
        }

        // lagrange basis polynomial
        double lx = numerator / denominator;
        // y value for the respective x values
        double y = values[i];

        // the lagrange phi(x) approximation function
        phiX += lx * y;
    }

    return phiX;
}

/* nodes and values extraction
Function Parameters:
[int* nodes]:     integer array that will store all nodes
                  should be pre defined. (obvious)
[double* values]: double array that will stores all values
                  should also be pre defined.
*/
