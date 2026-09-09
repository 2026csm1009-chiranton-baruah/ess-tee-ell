#include <stdio.h>
#include <stdlib.h>

/*
    HackerRank:
    Truck Tour

    Each petrol pump contains:
        petrol[i]   = amount of petrol available
        distance[i] = petrol required to reach next pump

    Return the index of the first petrol pump
    from which the truck can complete the circular tour.
*/


/* --------------------------------------------------
   Truck Tour
   -------------------------------------------------- */

int truckTour(int petrol_count, int** petrol) {

    int start = 0;
    long long balance = 0;

    for (int i = 0; i < petrol_count; i++) {

        /*
            Petrol gained at current pump
            minus petrol required to reach next pump
        */
        balance += (*petrol)[i * 2] - (*petrol)[i * 2 + 1];

        /*
            Cannot continue from current start.
        */
        if (balance < 0) {

            start = i + 1;
            balance = 0;
        }
    }

    return start;
}


/* --------------------------------------------------
   Main
   -------------------------------------------------- */

int main() {

    int n;

    scanf("%d", &n);

    /*
        Store each pump as:

        petrol[0] = petrol available at pump 0
        petrol[1] = distance from pump 0 to pump 1

        petrol[2] = petrol available at pump 1
        petrol[3] = distance from pump 1 to pump 2

        ...

    */

    int *petrol = malloc(2 * n * sizeof(int));

    if (petrol == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {

        int p, d;

        scanf("%d %d", &p, &d);

        petrol[i * 2] = p;
        petrol[i * 2 + 1] = d;
    }

    int answer = truckTour(n, &petrol);

    printf("%d\n", answer);

    free(petrol);

    return 0;
}
