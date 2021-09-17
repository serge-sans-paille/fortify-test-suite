#include <stdio.h>
#include <wchar.h>
#include "test_common.c"

/* reference implementation
 *
 *
 * __fortify_function wchar_t *
 * __NTH (wmempcpy (wchar_t *__restrict __s1, const wchar_t *__restrict __s2,
 * 		 size_t __n))
 * {
 *   if (__bos0 (__s1) != (size_t) -1)
 *     {
 *       if (!__builtin_constant_p (__n))
 * 	return __wmempcpy_chk (__s1, __s2, __n,
 * 			       __bos0 (__s1) / sizeof (wchar_t));
 *
 *       if (__n > __bos0 (__s1) / sizeof (wchar_t))
 * 	return __wmempcpy_chk_warn (__s1, __s2, __n,
 * 				    __bos0 (__s1) / sizeof (wchar_t));
 *     }
 *   return __wmempcpy_alias (__s1, __s2, __n);
 * }
 *
 */

int main(int argc, char ** argv) {
  wchar_t buffer[4] = {0};
#ifdef STATIC_CHECK
  wmemcpy(buffer, L"y", 5);
#endif
  wmemcpy(buffer, L"y", 4);
  fputws(buffer, stdout);
  if (argc > 1) {
    CHK_FAIL_START
    wmemcpy(buffer, L"y", argc);
    CHK_FAIL_END
  }
  fputws(buffer, stdout);
  return ret;
}
