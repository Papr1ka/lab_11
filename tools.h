#ifndef TOOLS_H
#define TOOLS_H
#include <limits.h>

int min(int size, int *array);
int max(int size, int *array);
double avg(int size, int *array);
int find_binary(int size, int *array, int value);

long long sum(int size, int *array);
long long multiply(int size, int *array);

bool is_sorted(int size, int *array);
bool is_owerflow_operation_multiply(signed long long si_a, signed int si_b);
bool is_owerflow_operation_sum(signed long long si_a, signed int si_b);


#endif // TOOLS_H
