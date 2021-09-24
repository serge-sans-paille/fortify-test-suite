#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "test_common.c"

/* reference implementation
 *
 *
 *
 *   __fortify_function int
 *   open (const char *__path, int __oflag, ...)
 *   {
 *     if (__va_arg_pack_len () > 1)
 *       __open_too_many_args ();
 *
 *     if (__builtin_constant_p (__oflag))
 *       {
 *         if (__OPEN_NEEDS_MODE (__oflag) && __va_arg_pack_len () < 1)
 *     {
 *       __open_missing_mode ();
 *       return __open_2 (__path, __oflag);
 *     }
 *         return __open_alias (__path, __oflag, __va_arg_pack ());
 *       }
 *
 *     if (__va_arg_pack_len () < 1)
 *       return __open_2 (__path, __oflag);
 *
 *     return __open_alias (__path, __oflag, __va_arg_pack ());
 *   }
 *
 *
 */

int main(int argc, char ** argv) {
#ifdef STATIC_CHECK
  open("/tmp/averylongtestname", O_RDONLY, 1 /* extra unused argument*/, 2);
#endif
  return 0;
}
