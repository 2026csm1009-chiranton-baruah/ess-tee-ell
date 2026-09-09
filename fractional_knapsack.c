#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int weight;
    int value;
    double ratio;
} Item;

int compare(const void *a, const void *b)
{
    Item *x = (Item *)a;
    Item *y = (Item *)b;

    if (x->ratio < y->ratio)
        return 1;
    if (x->ratio > y->ratio)
        return -1;

    return 0;
}

double fractionalKnapsack(Item items[], int n, int capacity)
{
    double totalValue = 0.0;

    // Calculate value/weight ratio
    for (int i = 0; i < n; i++)
        items[i].ratio =
            (double)items[i].value / items[i].weight;

    // Sort by decreasing ratio
    qsort(items, n, sizeof(Item), compare);

    // Pick items greedily
    for (int i = 0; i < n && capacity > 0; i++)
    {
        if (items[i].weight <= capacity)
        {
            // Take entire item
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        else
        {
            // Take fraction of item
            totalValue +=
                items[i].ratio * capacity;

            capacity = 0;
        }
    }

    return totalValue;
}

int main()
{
    int n, capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    Item items[n];

    printf("Enter weight and value of each item:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",
              &items[i].weight,
              &items[i].value);
    }

    double answer =
        fractionalKnapsack(items, n, capacity);

    printf("Maximum value = %.2f\n", answer);

    return 0;
}
