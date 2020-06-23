#include <string.h>
#include <stdlib.h>
#include "omp-tools.h"
#include "libgompd.h"
//#include "plugin-suffix.h"

ompd_rc_t ompd_get_api_version(ompd_word_t *version)
{
    *version = OMPD_VERSION;
    return ompd_rc_ok;
}

ompd_rc_t ompd_get_version_string(const char **string)
{
    string = str(OMPD_VERSION);
    return ompd_rc_ok;
}

ompd_rc_t ompd_initialize ( ompd_word_t api_version, const ompd_callbacks_t *callbacks )
{
    /* initialized flag */
    static int ompd_initialized = 0;

    if (ompd_initialized)
        return ompd_rc_error;

    /* compute library name and locations */
    const char *prefix = "libgompd.";
    const char *suffix = SONAME_SUFFIX (1);
    size_t prefix_len, suffix_len;
    prefix_len = strlen(prefix);
    suffix_len = strlen(suffix);
    char *ompd_name = (char *) malloc (prefix_len + suffix_len + 1);
    memcpy (ompd_name, prefix, prefix_len);
    memcpy (ompd_name + prefix_len, suffix, suffix_len + 1);

    /* set dll locations */
    const char *my_dll_locations[2] = {ompd_name, NULL};

    ompd_dll_locations = my_dll_locations;

    /* set initialized flag */
    ompd_initialized = 1;

    return ompd_rc_ok;
}
