/* reference implementation
 *
 * char *
 * __strcpy_chk (char *dest, const char *src, size_t destlen)
 * {
 *   size_t len = strlen (src);
 *   if (len >= destlen)
 *     __chk_fail ();
 *
 *   return memcpy (dest, src, len + 1);
 * }
 *
 * __fortify_function char *
 * __NTH (strcpy (char *__restrict __dest, const char *__restrict __src))
 * {
 *   return __builtin___strcpy_chk (__dest, __src, __bos (__dest));
 *  }
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  strcpy(buffer, "bonjour");
#endif
  char from[] = "bonjour";
  from[argc] = 0;
  strcpy(buffer, from);
  puts(buffer);

  from[3] = 0;
  strcpy(buffer, "yo");
  puts(buffer);
  return 0;
}
