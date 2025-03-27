#include <stdio.h>
#include <stdlib.h>

// function description after the main function
double lagrange_interpolation(int* nodes, double* values, int target, int nLength);
void get_nodes_values(int* nodes, double* values);
int parse_node(char* node);
double parse_value(char *value);

int main(void) {

    // take size of the data 
    // (number of nodes) as user input
    int size;
    printf("How many nodes does your datasheet have: ");
    scanf("%d", &size);

    // take the target node as user input
    int target;
    printf("Enter target node: ");
    scanf("%d", &target);

    // dynamically allocate memory for nodes and values
    int* nodes = (int *)malloc(size * sizeof(int));
    double* values = (double *)malloc(size * sizeof(double));
    if(nodes == NULL || values == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // extract nodes and values and insert them
    // in the pre defined arrays
    get_nodes_values(nodes, values);

    // debugging
    printf("nodes: \n");
    for(int i = 0; i < size; i++) {
        printf("%d\n", *(nodes + i));
    }
    printf("values: \n");
    for(int i = 0; i < size; i++) {
        printf("%.3lf\n", values[i]);
    }

    // calculate the approximate value at the target node
    double approximation = lagrange_interpolation(nodes, values, target, size);

    printf("The approximate value at [%d] is: %.3lf\n", target, approximation);

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
double lagrange_interpolation(int* nodes, double* values, int target, int nLength) {
    double phiX = 0;

    for(int i = 0; i < nLength; i++) {
        double numerator = 1.0f;
        double denominator = 1.0f;

        for(int x = 0; x < nLength; x++) {
            // if x = i, then skip iteration, removing 
            // this will cause a divide by zero error
            if(x == i) continue;

            // numerator is the product of
            // target x value - the nodes
            numerator *= target - nodes[x];

            // denominator is the product of 
            // each node - the other nodes
            denominator *= nodes[i] - nodes[x];
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
void get_nodes_values(int* nodes, double* values) {
    
    // file pointer
    FILE* file;

    // open csv file in parent/data/
    file = fopen("../data/nodes_values.csv", "r");
    if(file == NULL) {
        printf("File failed to open\n");
        exit(1);
    }

    // char c will read each 
    // character from the file
    char c;

    // this loop is run to skip the head line: x,y
    while((c = fgetc(file)) != EOF && c != '\n');

    // node character to be added to nodeStr
    char nc;
    // value character to be added to valueStr
    char vc;
    // bool var that checks if the 
    // next iteration has a node character
    // this var starts with reading a node
    int isNode = 1;
    // same as above for value
    int isValue = 0;
    // moves the value array
    int vCount = 0;
    // same as above for nodes
    int nCount = 0;
    // reallocation iteration counter 
    // to increase size as needed
    int rCount = 0;

    // run loop until end of file
    while((c = fgetc(file)) != EOF) {

        // node extraction
        if(isNode) {
            // dynamically assign array to store characters as a string
            char* nodeStr = (char *)malloc(10 * sizeof(char));
            // node chacarter count i.e length of the node string
            int ncCount = 0;
            nodeStr[ncCount++] = c;
            // run loop until a comma is encountered
            while((nc = fgetc(file)) != ',') {
                // add each character to node string
                *(nodeStr + ncCount++) = nc;
                // if the string size is too low then 
                // expand the string size
                if(ncCount % 10 == 0) {
                    char* temp = (char *)realloc(nodeStr, (++rCount * 10) * sizeof(char));
                    if(temp == NULL) {
                        free(nodeStr);
                        printf("memory reallocation failed please try again.\n");
                        exit(1);
                    }
                    nodeStr = temp;
                }
            }
            // null terminator to mark end of string
            nodeStr[ncCount] = '\0';
            // resize string to shrink down to its correct length
            char* temp = (char *)realloc(nodeStr, (ncCount + 1) * sizeof(char));
            if(temp == NULL) {
                free(nodeStr);
                printf("memory reallocation failed please try again.\n");
                exit(1);
            }
            nodeStr = temp;
            // get the numerical value out of the node string
            int node = parse_node(nodeStr);
            // add that numerical value to the nodes array
            nodes[nCount++] = node;
            isNode = 0;
            isValue = 1;
            free(nodeStr);
        }

        // value extraction
        rCount = 0; // reset reallocation count
        // same process as node
        if(isValue) {
            char* valueStr = (char *)malloc(10 * sizeof(char));
            int vcCount = 0;
            while((vc = fgetc(file)) != '\n' && vc != EOF) {
                *(valueStr + vcCount++) = vc;
                if(vcCount % 10 == 0) {
                    char* temp = (char *)realloc(valueStr, (++rCount * 10) * sizeof(char));
                    if(temp == NULL) {
                        free(valueStr);
                        printf("memory reallocation failed please try again.\n");
                        exit(1);
                    }
                    valueStr = temp;
                }
            }
            valueStr[vcCount] = '\0';
            char* temp = (char *)realloc(valueStr, (vcCount + 1) * sizeof(char));
            if(temp == NULL) {
                free(valueStr);
                printf("memory reallocation failed please try again.\n");
                exit(1);
            }
            valueStr = temp;
            double value = parse_value(valueStr);
            values[vCount++] = value;
            isValue = 0;
            isNode = 1;
            free(valueStr);
        }

        // node after every newline
        if(c == '\n') {
            isNode = 1;
            isValue = 0;
        }
        // value after every comma
        if(c == ',') {
            isValue = 1;
            isNode = 0;
        }
    }

    // close file to prevent memory leaks
    fclose(file);
}

// function made for consistency with 
// parse_value (not necessary)
int parse_node(char* node) {
    return atoi(node);
}

/* converts string input into its double numerical value
Function Parameters:
[char *value]: string input which holds the numerical
               data in the form of a string
*/
double parse_value(char* value) {
    double num = 0.0f;
    int isDec = 0;
    double dec = 0.1f;

    for (int i = 0; value[i] != '\0'; i++) {
        // if a '.' is encountered then it is a decimal number
        if(value[i] == '.') isDec = 1;

        // only parse digits
        if(value[i] >= '0' && value[i] <= '9') {
            // get the digits from the ascii value
            int dig = value[i] - '0';

            // if decimal section then parse accordingly
            if(isDec) {
                num = num + (dig * dec);
                dec *= 0.1f;
            } else { // normal parsing for integer section of the number
                num = (num * 10) + dig;
            }
        }
    }

    return num;
}