#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * char *
 * __stpcpy_chk (char *dest, const char *src, size_t destlen)
 * {
 *   size_t len = strlen (src);
 *   if (len >= destlen)
 *     __chk_fail ();
 *
 *   return memcpy (dest, src, len + 1) + len;
 * }
 *
 * __fortify_function char *
 * __NTH (stpcpy (char *__restrict __dest, const char *__restrict __src))
 * {
 *   return __builtin___stpcpy_chk (__dest, __src, __bos (__dest));
 *  }
 *
 */

int main(int argc, char ** argv) {
  DECL_BUF(buffer, 3)
#ifdef STATIC_CHECK
  stpcpy(buffer, "bonjour");
#endif
  char from[] = "bonjour";

  from[3] = 0;
  stpcpy(buffer, "yo");
  puts(buffer);

  from[argc] = 0;
  if (argc > 1) {
    CHK_FAIL_START
    stpcpy(buffer, from);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}
