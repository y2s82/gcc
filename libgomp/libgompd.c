#include "omp-tools.h"
#include "libgompd.h"

void ompd_init()
{
    static int ompd_initialized = 0;

    if (ompd_initialized)
        return;

    ompd_initialized = 1;
    ompd_dell_locations = { "libgompd" SONAME_SUFFIX (1), NULL };
}
