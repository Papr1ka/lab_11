#ifndef SORTS_H
#define SORTS_H

#include <iostream>

using namespace std;

void makaka_sort(int size, int *array_ptr, int *iterations, int *swipes);
void bubble_sort(int size, int *array_ptr, int *iterations, int *swipes);
void gnome_sort(int size, int *array_ptr, int *iterations, int *swipes);
void hair_sort(int size, int *array_ptr, int *iterations, int *swipes);
void quick_sort(int *numbers, int left, int right, int *iterations, int *swipes);

#endif // SORTS_H

