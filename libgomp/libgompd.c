#include "omp-tools.h"
#include "libgompd.h"
#include "plugin-suffix.h"

void ompd_init()
{
    static int ompd_initialized = 0;

    const char *prefix = "libgompd.";
    const char *suffix = SONAME_SUFFIX (1);

    if (ompd_initialized)
        return;

    size_t prefix_len, suffix_len;
    prefix_len = strlen(prefix);
    suffix_len = strlen(suffix);

    ompd_name = (char *) malloc (prefix_len + suffix_len + 1);
    memcpy (ompd_name, prefix, prefix_len);
    memcpy (ompd_name + prefix_len, suffix, suffix_len + 1);

    ompd_dell_locations = { ompd_name, NULL };

    ompd_initialized = 1;
}
