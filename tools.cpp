#include <iostream>

int min(int size, int *array)
{
    int min = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

int max(int size, int *array)
{
    int max = array[0];
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

double avg(int size, int *array)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return (double) sum / (double) size;
}

bool is_sorted(int size, int *array)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

int find_binary(int size, int *array, int value)
{
    int l = 0;
    int r = size;
    while (l < r)
    {
        int pivot = (l + r) / 2;
        if (array[pivot] > value)
        {
            r = pivot - 1;
        }
        else if (array[pivot] < value)
        {
            l = pivot + 1;
        }
        else if (array[pivot] == value)
        {
            return pivot;
        }
    }
    if (array[l] == value)
    {
        return l;
    }
    else
    {
        return -1;
    }
}

bool is_owerflow_operation_multiply(signed long long si_a, signed int si_b) {
  if (si_a > 0) {
    if (si_b > 0) {
      if (si_a > (LONG_LONG_MAX / si_b)) {
          return true;
      }
    } else {
      if (si_b < (LONG_LONG_MIN / si_a)) {
          return true;
      }
    }
  } else {
    if (si_b > 0) {
      if (si_a < (LONG_LONG_MIN / si_b)) {
          return true;
      }
    } else {
      if ( (si_a != 0) && (si_b < (LONG_LONG_MAX / si_a))) {
          return true;
      }
    }
  }
  return false;
}

bool is_owerflow_operation_sum(signed long long si_a, signed int si_b) {
  if (((si_b > 0) && (si_a > (LONG_LONG_MAX - si_b))) ||
      ((si_b < 0) && (si_a < (LONG_LONG_MIN - si_b)))) {
    return true;
  } else {
    return false;
  }
}

long long sum(int size, int *array)
{
    long long result = 0;
    for (int i = 0; i < size; i++)
    {
        if (is_owerflow_operation_sum(result, array[i]))
        {
            throw 1;
        }
        else
        {
            result += array[i];
        }
    }
    return result;
}

long long multiply(int size, int *array)
{
    bool zero_exists = false;
    for (int i = 0; i < size; i++)
    {
        if (array[i] == 0)
        {
            zero_exists = true;
            break;
        }
    }
    long long result = 1;
    if (zero_exists)
    {
        result = 0;
    }
    else
    {
        result = 1;
        for (int i = 0; i < size; i++)
        {
            if (is_owerflow_operation_multiply(result, array[i]))
            {
                throw 1;
            }
            else
            {
                result *= array[i];
            }
        }
    }
    return result;
}
