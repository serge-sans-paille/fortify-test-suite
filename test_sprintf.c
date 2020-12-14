#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 * int
 * ___sprintf_chk (char *s, int flag, size_t slen, const char *format, ...)
 * {
 *   // For flag > 0 (i.e. __USE_FORTIFY_LEVEL > 1) request that %n can only come from read-only format strings.
 *   unsigned int mode = (flag > 0) ? PRINTF_FORTIFY : 0;
 *   va_list ap;
 *   int ret;
 *
 *   // Regardless of the value of flag, let __vsprintf_internal know that this is a call from *printf_chk.
 *   mode |= PRINTF_CHK;
 *
 *   if (slen == 0)
 *     __chk_fail ();
 *
 *   va_start (ap, format);
 *   ret = __vsprintf_internal (s, slen, format, ap, mode);
 *   va_end (ap);
 *
 *   return ret;
 * }
 *
 * __fortify_function int
 * __NTH (sprintf (char *__restrict __s, const char *__restrict __fmt, ...))
 * {
 *   return __builtin___sprintf_chk (__s, __USE_FORTIFY_LEVEL - 1, __bos (__s), __fmt, __va_arg_pack ());
 * }
 *
 */

int main(int argc, char ** argv) {
  DECL_BUF(buffer, 3)
#ifdef STATIC_CHECK
  sprintf(buffer, "hello");
#endif
  // FIXME: no check for slen == 0
  sprintf(buffer, "%d", argc);
  puts(buffer);
  if (argc > 1) {
    CHK_FAIL_START
    sprintf(buffer, "!%d", 8 + argc);
    CHK_FAIL_END
  }
  puts(buffer);
  return ret;
}
