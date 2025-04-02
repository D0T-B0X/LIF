#include "csv_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function description after the main function
double lagrange_interpolation(float* nodes, double* values, int target, int nLength);

int main(void) {

    // take size of the data 
    // (number of nodes) as user input
    int size_approx;
    printf("How many nodes does your interpolation datasheet have: ");
    scanf("%d", &size_approx);

    // dynamically allocate memory for nodes and values
    float* nodes = (float *)malloc(size_approx * sizeof(float));
    double* values = (double *)malloc(size_approx * sizeof(double));
    if(nodes == NULL || values == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // extract nodes and values and insert them
    // in the pre defined arrays
    get_nodes_values(nodes, values, "../data/nodes_values.csv");

    // flag to check for first iteration in csv creation
    int first = 1;

    // this for loop adds an entry for every node in the range
    // and calculates its approximate value and error percentage
    // it then adds those values in a new csv file for visualization
    for(int i = 0; i < size_approx; i++) {
        if(i > 0) first = 0;

        double approx = lagrange_interpolation(nodes, values, i, size_approx);
        double error;

        if(fabs(values[i]) < 1e-14) {
            if(fabs(approx) < 1e-14) error = 0.0f;
            else error = fabs(approx) * 100.0f;
        }
        else error = fabs((1 - (approx / values[i])) * 100.0f);
        
        add_approximation(nodes[i], error, first, values[i], approx, "../data/accuracy.csv");
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
