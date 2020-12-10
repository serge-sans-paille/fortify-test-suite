#include <string.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * __fortify_function void *
 * __NTH (mempcpy (void *__restrict __dest, const void *__restrict __src, size_t __len))
 * {
 *   return __builtin___mempcpy_chk (__dest, __src, __len, __bos0 (__dest));
 * }
 *
 * __fortify_function void *
 * __NTH (memset (void *__dest, int __ch, size_t __len))
 * {
 *   // GCC-5.0 and newer implements these checks in the compiler, so we don't need them here.
 * #if !__GNUC_PREREQ (5,0)
 *  if (__builtin_constant_p (__len) && __len == 0
 *          && (!__builtin_constant_p (__ch) || __ch != 0))
 *    {
 *       __warn_memset_zero_len ();
 *       return __dest;
 *    }
 * #endif
 *   return __builtin___memset_chk (__dest, __ch, __len, __bos0 (__dest));
 *  }
 */


int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  memset(buffer, argc, 0);
  memset(buffer, 0, 4);
#endif
  memset(buffer, 0, 3);
  puts(buffer);
  if (argc > 1) {
    CHK_FAIL_START
    memset(buffer, 0, argc);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}
