/*  Test that the omp-tools.h will compile successfully with omp.h .  */

/* { dg-do compile } */
#include "omp-tools.h"
#include "omp.h"

int
main ()
{
  return 0;
}
