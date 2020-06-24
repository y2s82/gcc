#include <stddef.h>
#include "omp-tools.h"
#include "libgompd.h"
#include "plugin-suffix.h"


const char *ompd_dll_locations[2] = { "libgompd" SONAME_SUFFIX (1), NULL };

ompd_rc_t ompd_get_api_version(ompd_word_t *version)
{
  *version = OMPD_VERSION;
  return ompd_rc_ok;
}

ompd_rc_t ompd_get_version_string(const char **string)
{
  *string = "GNU OpenMP Runtime implementing OpenMP 5.0" ompd_str2(OMPD_VERSION);
  return ompd_rc_ok;
}

ompd_rc_t ompd_initialize ( ompd_word_t api_version, const ompd_callbacks_t *callbacks )
{
  /* initialized flag */
  static int ompd_initialized = 0;

  if (ompd_initialized)
      return ompd_rc_error;




  /* set initialized flag */
  ompd_initialized = 1;

  return ompd_rc_ok;
}
