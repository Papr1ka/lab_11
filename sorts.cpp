#include "sorts.h"

void makaka_sort(int size, int *array_ptr, int *iterations, int *swipes)
{
    bool sorted = false;
    int pos1, pos2;
    int temp;
    int counter = 0;
    while (counter < 1000)
    {
        sorted = true;
        for (int i = 0; i < size - 1; i++)
        {
            *iterations += 1;
            if (array_ptr[i] > array_ptr[i + 1])
            {
                sorted = false;
                break;
            }
        }
        if (sorted)
        {
            break;
        }
        else
        {
            *iterations += 1;
            pos1 = rand() % size;
            pos2 = rand() % size;
            temp = array_ptr[pos1];
            array_ptr[pos1] = array_ptr[pos2];
            array_ptr[pos2] = temp;
            *swipes += 1;
        }
        counter++;
    }
    if (counter >= 1000)
    {
        *swipes = 1000;
    }
}


void quick_sort(int *numbers, int left, int right, int *iterations, int *swipes)
{
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = numbers[left];

    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
        {
            right--;
            *iterations += 1;
        }

        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
            *swipes += 1;
        }

        while ((numbers[left] <= pivot) && (left < right))
        {
            left++;
            *iterations += 1;
        }

        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
            *swipes += 1;
            *iterations += 1;
        }
    }

    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;

    if (left < pivot)
    {
        quick_sort(numbers, left, pivot - 1, iterations, swipes);
    }
    if (right > pivot)
    {
        quick_sort(numbers, pivot + 1, right, iterations, swipes);
    }
}


void bubble_sort(int size, int *array_ptr, int *iterations, int *swipes)
{
    int temp;
    for (int i = size; i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
        {
            if (array_ptr[j] > array_ptr[j + 1])
            {
                temp = array_ptr[j];
                array_ptr[j] = array_ptr[j + 1];
                array_ptr[j + 1] = temp;
                *swipes += 1;
            }
            *iterations += 1;
        }
    }
}


void gnome_sort(int size, int *array_ptr, int *iterations, int *swipes)
{
    int i = 0;
    int temp;
    while (i < size - 1)
    {
        *iterations += 1;
        if (array_ptr[i] > array_ptr[i + 1])
        {
            *swipes += 1;
            temp = array_ptr[i];
            array_ptr[i] = array_ptr[i + 1];
            array_ptr[i + 1] = temp;
            if (i > 0)
            {
                i--;
            }
        }
        else
        {
            i++;
        }
    }
}

void hair_sort(int size, int *array_ptr, int *iterations, int *swipes)
{
    int step = size - 1;
    bool flag = true;
    int i;
    int temp;
    while (step > 1 or flag)
    {
        if (step > 1)
        {
            step = step / 1.247;
        }
        flag = false;
        i = 0;
        while (i + step < size)
        {
            *iterations += 1;
            if (array_ptr[i] > array_ptr[i + step])
            {
                temp = array_ptr[i];
                array_ptr[i] = array_ptr[i + step];
                array_ptr[i + step] = temp;
                flag = true;
                *swipes += 1;
            }
            i++;
        }
    }
}
