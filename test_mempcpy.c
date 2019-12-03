#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

/* reference implementation
 *
 * void *
 * __mempcpy_chk (void *dstpp, const void *srcpp, size_t len, size_t dstlen)
 * {
 *   if (__glibc_unlikely (dstlen < len))
 *     __chk_fail ();
 *
 *   return __mempcpy (dstpp, srcpp, len);
 * }
 *
 * __fortify_function void *
 * __NTH (mempcpy (void *__restrict __dest, const void *__restrict __src, size_t __len))
 * {
 *   return __builtin___mempcpy_chk (__dest, __src, __len, __bos0 (__dest));
 * }
 *
 */

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  mempcpy(buffer, "yo", 4);
#endif
  mempcpy(buffer, "yo", 3);
  puts(buffer);
  mempcpy(buffer, "yo", argc);
  puts(buffer);
  return 0;
}
