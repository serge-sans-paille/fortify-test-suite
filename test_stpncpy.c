#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * char *
 * __stpncpy_chk (char *dest, const char *src, size_t destlen)
 * {
 *   size_t len = strlen (src);
 *   if (len >= destlen)
 *     __chk_fail ();
 *
 *   return memcpy (dest, src, len + 1) + len;
 * }
 *
 * __fortify_function char *
 * __NTH (stpncpy (char *__restrict __dest, const char *__restrict __src))
 * {
 *   return __builtin___stpncpy_chk (__dest, __src, __bos (__dest));
 *  }
 *
 */

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  stpncpy(buffer, "bonjour");
#endif
  char from[] = "bonjour";

  from[3] = 0;
  stpncpy(buffer, "yo", 2);
  puts(buffer);

  if (argc > 1) {
    CHK_FAIL_START
    stpncpy(buffer, from, argc);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}
