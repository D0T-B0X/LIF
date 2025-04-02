#include "csv_utils.h"
#include <stdio.h>
#include <stdlib.h>

void get_nodes_values(float* nodes, double* values, const char* filepath) {
    
    // file pointer
    FILE* file;

    // open csv file in parent/data/
    file = fopen(filepath, "r");
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
            float node = (float)parse_number(nodeStr);
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
            double value = parse_number(valueStr);
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

double parse_number(char* value) {
    double num = 0.0f;
    int isDec = 0;
    double dec = 0.1f;
    int isNeg = 0;

    if(value[0] == '-') isNeg = 1;

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

    // if a '-' is the first character
    // then the number is made negative
    if(isNeg) num *= -1.0f;

    return num;
}

void add_approximation(float target, double accuracy, int first, double value, double approx, const char* filepath) {
    
    FILE* file;

    // opens file in append mode for non first iterations
    if(!first){
        file = fopen(filepath, "a");
        if(file == NULL) {
            printf("File failed to open\n");
            exit(1);
        }
     } else { // delete any old data on the first iteration and start anew
        file = fopen(filepath, "w");
        if(file == NULL) {
            printf("File failed to open");
            exit(1);
        }
    }

    // adds csv labels on the first iteration and following values
    // for the remaining iterations
    if(first) fprintf(file, "nodes,error,value,approx\n%.3f,%.15lf,%.15lf,%.15lf\n", target, accuracy, value, approx);
    else fprintf(file, "%.3f,%.15lf,%.15lf,%.15lf\n", target, accuracy, value, approx);
    fclose(file);
}