#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "test_common.c"

/* reference implementation
 * int
 * ___vsnprintf_chk (char *s, size_t maxlen, int flag, size_t slen,
 * 		  const char *format, va_list ap)
 * {
 *   if (__glibc_unlikely (slen < maxlen))
 *     __chk_fail ();
 *
 *   // For flag > 0 (i.e. __USE_FORTIFY_LEVEL > 1) request that %n can only come from read-only format strings.
 *   unsigned int mode = (flag > 0) ? PRINTF_FORTIFY : 0;
 *
 *   return __vsnprintf_internal (s, maxlen, format, ap, mode);
 * }
 *
 *
 * __fortify_function int
 * __NTH (vsnprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, __gnuc_va_list __ap))
 * {
 *   return __builtin___vsnprintf_chk (__s, __n, __USE_FORTIFY_LEVEL - 1, __bos (__s), __fmt, __ap);
 * }
 */

int aux(int argc, char ** argv, ...) {
  char buffer[3] = {0};
  va_list ap;
  va_start(ap, argv);


#ifdef STATIC_CHECK
  vsnprintf(buffer, 4, "%d", ap);
#endif
  vsnprintf(buffer, 3, "%d", ap);
  puts(buffer);
  if (argc > 1) {
    CHK_FAIL_START
    vsnprintf(buffer, argc, "%d", ap);
    CHK_FAIL_END
  }
  puts(buffer);
  va_end(ap);
  return ret;
}

int main(int argc, char ** argv) {
  return aux(argc, argv, argc);
}
