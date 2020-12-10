#include <string.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * char *
 * __strncpy_chk (char *s1, const char *s2, size_t n, size_t s1len)
 * {
 *   if (__builtin_expect (s1len < n, 0))
 *     __chk_fail ();
 *
 *   return strncpy (s1, s2, n);
 * }
 *
 * __fortify_function char *
 * __NTH (strncpy (char *__restrict __dest, const char *__restrict __src, size_t __len))
 * {
 *   return __builtin___strncpy_chk (__dest, __src, __len, __bos (__dest));
 * }
 */

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  strncpy(buffer, "bonjour", 4);
#endif

  if (argc > 1) {
    CHK_FAIL_START
    char buffer[3] = {0};
    strncpy(buffer, "bonjour", argc);
    puts(buffer);
    CHK_FAIL_END
  }

  {
    char buffer[3] = {0};
    strncpy(buffer, "yo", 3);
    puts(buffer);
  }
  return ret;
}
