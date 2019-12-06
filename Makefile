PKGNAME=fortify-test-suite

GCC ?= gcc
CLANG ?= clang
CFLAGS ?=-D_FORTIFY_SOURCE=1 -O1
CFLAGS_STATIC=$(CFLAGS) -DSTATIC_CHECK -Werror
STATIC_CHECK ?= false


TARGETS=test_memcpy test_memmove test_mempcpy test_memset test_snprintf test_sprintf test_stpcpy test_strcat test_strcpy test_strncat test_strncpy test_vsnprintf test_vsprintf

check:check-gcc check-clang

check-gcc:$(patsubst test_%,run_%.gcc, $(TARGETS))
	@echo "===== GCC OK ====="
check-clang:$(patsubst test_%,run_%.clang, $(TARGETS))
	@echo "===== CLANG OK ====="

test_memcpy:run_memcpy.gcc run_memcpy.clang
test_memmove:run_memmove.gcc run_memmove.clang
test_mempcpy:run_mempcpy.gcc run_mempcpy.clang
test_memset:run_memset.gcc run_memset.clang
test_snprintf:run_snprintf.gcc run_snprintf.clang
test_sprintf:run_sprintf.gcc run_sprintf.clang
test_stpcpy:run_stpcpy.gcc run_stpcpy.clang
test_strcat:run_strcat.gcc run_strcat.clang
test_strcpy:run_strcpy.gcc run_strcpy.clang
test_strncat:run_strncat.gcc run_strncat.clang
test_strncpy:run_strncpy.gcc run_strncpy.clang
test_vsnprintf:run_vsnprintf.gcc run_vsnprintf.clang
test_vsprintf:run_vsnprintf.gcc run_vsnprintf.clang

run_%:test_%
	./$<
	! ./$< 1 1 1
	! ./$< 1 1 1 1
	@echo "$< OK"

test_%.gcc:test_%.c
	! $(STATIC_CHECK) || $(GCC) $(CFLAGS_STATIC) $< 2>&1 | grep ' error: '
	$(GCC) $(CFLAGS) $< -o $@

test_%.clang:test_%.c
	! $(STATIC_CHECK) || $(CLANG) $(CFLAGS_STATIC) $< 2>&1 | grep ' error: '
	$(CLANG) $(CFLAGS) $< -o $@

clean:
	for target in $(TARGETS); do $(RM) $$target.gcc $$target.clang ; done
	$(RM) $(PKGNAME).tgz

dist: $(PKGNAME).tgz

$(PKGNAME).tgz: $(patsubst %,%.c, $(TARGETS)) Makefile README.rst
	$(RM) -rf $(PKGNAME)
	mkdir $(PKGNAME)
	cp $^ $(PKGNAME)/
	tar czf $@ $(PKGNAME)/
	$(RM) -rf $(PKGNAME)

