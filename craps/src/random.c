#include "random.h"

#include <stdlib.h>
#include <time.h>

int randomInRange(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}