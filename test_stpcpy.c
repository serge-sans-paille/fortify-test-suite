#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  stpcpy(buffer, "bonjour");
#endif
  char from[] = "bonjour";
  from[argc] = 0;
  stpcpy(buffer, from);
  puts(buffer);

  from[3] = 0;
  stpcpy(buffer, "yo");
  puts(buffer);
  return 0;
}
