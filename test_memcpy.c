#include <string.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 *
 * __fortify_function void *
 * __NTH (memcpy (void *__restrict __dest, const void *__restrict __src,
 * size_t __len))
 * {
 *   return __builtin___memcpy_chk (__dest, __src, __len, __bos0(__dest));
 * }
 *
 * void *
 * __memcpy_chk (void *dstpp, const void *srcpp, size_t len, size_t dstlen)
 * {
 *   if (__glibc_unlikely (dstlen < len))
 *     __chk_fail ();
 *
 *   return memcpy (dstpp, srcpp, len);
 * }
 *
 */

int main(int argc, char ** argv) {
  DECL_BUF(buffer, 3)
#ifdef STATIC_CHECK
  memcpy(buffer, "yo", 4);
#endif
  memcpy(buffer, "yo", 3);
  puts(buffer);
  if (argc > 1) {
    CHK_FAIL_START
    memcpy(buffer, "yo", argc);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}
