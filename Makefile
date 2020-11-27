PKGNAME=fortify-test-suite

CFLAGS ?=-D_FORTIFY_SOURCE=1 -O1
CFLAGS_STATIC=$(CFLAGS) -DSTATIC_CHECK -Werror
STATIC_CHECK ?= false
COMPILERS = gcc clang

TARGETS=test_memcpy test_memmove test_mempcpy test_memset test_snprintf test_sprintf test_stpcpy test_strcat test_strcpy test_strncat test_strncpy test_vsnprintf test_vsprintf

check:$(patsubst %,check-%,$(COMPILERS))

check-target = check-$(1):$(patsubst test_%,run_%.$(1),$(TARGETS)); \
	@echo "===== $$@ OK ====="

$(call check-target,gcc)
$(call check-target,clang)

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

build-target = test_%.$(1):test_%.c; \
	! $(STATIC_CHECK) || $(1) $(CFLAGS_STATIC) $< 2>&1 \
		| grep ' error: '; \
	$(1) $(CFLAGS) $$< -o $$@;

$(call build-target,gcc)
$(call build-target,clang)

clean:
	for target in $(TARGETS); do $(RM) $(patsubst %,$$target.%,$(COMPILERS)) ; done
	$(RM) $(PKGNAME).tgz

dist: $(PKGNAME).tgz

$(PKGNAME).tgz: $(patsubst %,%.c, $(TARGETS)) Makefile README.rst
	$(RM) -rf $(PKGNAME)
	mkdir $(PKGNAME)
	cp $^ $(PKGNAME)/
	tar czf $@ $(PKGNAME)/
	$(RM) -rf $(PKGNAME)

