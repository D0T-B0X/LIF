#ifndef CSV_UTILS_H
#define CSV_UTILS_H

/**
 * Reads nodes and values from a CSV file
 * @param nodes Array to store node values
 * @param values Array to store function values
 * @param size Number of nodes to read
 */
void get_nodes_values(float* nodes, double* values, const char* filepath);

/**
 * Adds interpolation results to a CSV file for visualization
 * @param target The x-value (node) being interpolated
 * @param accuracy Error percentage
 * @param first Flag to indicate first entry (header creation)
 * @param value Actual function value
 * @param approx Approximated value from interpolation
 */
void add_approximation(float target, double accuracy, int first, double value, double approx, const char* filepath);

/**
 * Parses a string to a floating-point number
 * @param value String representation of a number
 * @return Parsed double value
 */
double parse_number(char* value);

#endif