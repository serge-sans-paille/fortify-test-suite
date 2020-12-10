#include <string.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * void *
 * MEMMOVE_CHK (void *dest, const void *src, size_t len, size_t destlen)
 * {
 *   if (__glibc_unlikely (destlen < len))
 *       __chk_fail ();
 *
 *   return memmove (dest, src, len);
 * }
 *
 * __fortify_function void *
 * __NTH (memmove (void *__dest, const void *__src, size_t __len))
 * {
 *   return __builtin___memmove_chk (__dest, __src, __len, __bos0 (__dest));
 * }
 */


int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  memmove(buffer, "yo", 4);
#endif
  memmove(buffer, "yo", 3);
  puts(buffer);
  if (argc > 1) {
    CHK_FAIL_START
    memmove(buffer, "yo", argc);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}

