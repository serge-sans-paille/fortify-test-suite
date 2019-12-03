#include <string.h>
#include <stdio.h>

/* reference implementation
 *
 * int
 * ___snprintf_chk (char *s, size_t maxlen, int flag, size_t slen,
 * 		 const char *format, ...)
 * {
 *   if (__glibc_unlikely (slen < maxlen))
 *     __chk_fail ();
 *
 *   // For flag > 0 (i.e. __USE_FORTIFY_LEVEL > 1) request that %n can only come from read-only format strings.
 *   unsigned int mode = (flag > 0) ? PRINTF_FORTIFY : 0;
 *   va_list ap;
 *   int ret;
 *
 *   va_start (ap, format);
 *   ret = __vsnprintf_internal (s, maxlen, format, ap, mode);
 *   va_end (ap);
 *
 *   return ret;
 * }
 *
 * __fortify_function int
 * __NTH (snprintf (char *__restrict __s, size_t __n, const char *__restrict __fmt, ...))
 * {
 *   return __builtin___snprintf_chk (__s, __n, __USE_FORTIFY_LEVEL - 1, __bos (__s), __fmt, __va_arg_pack ());
 * }
 */

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  snprintf(buffer, 4, "%d", argc);
#endif
  snprintf(buffer, 3, "%d", argc);
  puts(buffer);
  snprintf(buffer, argc, "%d", argc);
  puts(buffer);
  return 0;
}
