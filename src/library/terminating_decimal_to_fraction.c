#include "arithmetica.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void
terminating_decimal_to_fraction (const char *decimal_in, char *numerator_out,
                                 char *denominator_out)
{
  size_t din_size = strlen (decimal_in);
  char *numerator = strdup(decimal_in);
  char *denominator = (char *)calloc (din_size + 1, 1);
  

  size_t decimalPlaces = 0;
  unsigned char inDecimals = 0;
  for (size_t i = 0; i < strlen (decimal_in); i++)
    {
      if (inDecimals)
        {
          decimalPlaces++;
          numerator[i - 1] = numerator[i];
        }
      if (decimal_in[i] == '.')
        inDecimals = 1;
    }

  if (inDecimals)
    numerator[strlen (numerator) - 1] = 0;

  denominator[0] = '1';
  for (size_t i = 1; i <= decimalPlaces; i++)
    denominator[i] = '0';

  // simplifying the fraction
  char *gcd = (char *)calloc (strlen (decimal_in) + 1, 1);
  igcd (numerator, denominator, gcd);
  divide (numerator, gcd, numerator_out, 0);
  divide (denominator, gcd, denominator_out, 0);

  free (numerator);
  free (denominator);
  free (gcd);
}