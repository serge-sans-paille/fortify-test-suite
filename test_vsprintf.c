/* reference implementation
 *
 * int
 * ___vsprintf_chk (char *s, int flag, size_t slen, const char *format,
 * 		 va_list ap)
 * {
 *   // For flag > 0 (i.e. __USE_FORTIFY_LEVEL > 1) request that %n can only come from read-only format strings.
 *   unsigned int mode = (flag > 0) ? PRINTF_FORTIFY : 0;
 *
 *   // Regardless of the value of flag, let __vsprintf_internal know that this is a call from *printf_chk.
 *   mode |= PRINTF_CHK;
 *
 *   if (slen == 0)
 *     __chk_fail ();
 *
 *   return __vsprintf_internal (s, slen, format, ap, mode);
 * }
 *
 * __fortify_function int 
 * __NTH (vsprintf (char *__restrict __s, const char *__restrict __fmt, __gnuc_va_list __ap))
 * {
 *   return __builtin___vsprintf_chk (__s, __USE_FORTIFY_LEVEL - 1, __bos (__s), __fmt, __ap);
 * }
 */

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "test_common.c"

int aux0(int argc, char ** argv, ...) {
  va_list ap;
  va_start(ap, argv);
  char buffer[3];
#ifdef STATIC_CHECK
  vsprintf(buffer, "bonjour", ap);
#endif
  va_end(ap);
  return 0;
}
int aux1(int argc, char ** argv, ...) {
  va_list ap;
  int ret = 0;
  va_start(ap, argv);
  char buffer[3];
  if (argc > 1) {
    CHK_FAIL_START
    vsprintf(buffer, "!%d", ap);
    CHK_FAIL_END
  }
  puts(buffer);
  va_end(ap);
  return ret;
}
int aux2(int argc, char ** argv, ...) {
  va_list ap;
  va_start(ap, argv);
  char buffer[3];
  vsprintf(buffer, "%d", ap);
  puts(buffer);
  va_end(ap);
  return 0;
}

int main(int argc, char ** argv) {
  // FIXME: no check for slen == 0
  return aux0(argc, argv, "hello")
    + aux1(argc, argv, 8 + argc)
    + aux2(argc, argv, argc)
    ;
}
