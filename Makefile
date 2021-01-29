PKGNAME=fortify-test-suite

ifdef SYSROOT
	# We can't just use --sysroot or -isysroot because clang and gcc don't
	# agree on how those options should behave.  Instead just use -I and -L
	# since that covers our use case of getting the right glibc headers and
	# libs.  It's just that we won't be able to test any startup code
	# changes, but it's not something _FORTIFY_SOURCE will touch anyway.
	USE_SYSROOT = -isystem $(SYSROOT)/usr/include \
		      -isystem $(SYSROOT)/include \
		      -L$(SYSROOT)/lib64 -L$(SYSROOT)/lib \
		      -L$(SYSROOT)/usr/lib64 -L$(SYSROOT)/usr/lib
else
	USE_SYSROOT =
endif

ifeq (1,$(V))
	Q =
else
	Q = @
endif

DEFAULT_CFLAGS = $(CFLAGS) -O1 $(USE_SYSROOT)
CFLAGS_STATIC=$(DEFAULT_CFLAGS) -DSTATIC_CHECK -Werror
STATIC_CHECK ?= false
COMPILERS = gcc clang
FORTIFY_LEVELS = 1 2

TARGETS=memcpy memmove mempcpy memset snprintf sprintf stpcpy stpncpy strcat \
	strcpy strncat strncpy vsnprintf vsprintf

check:$(patsubst %,check-%,$(COMPILERS)) test_common.c

check-%:check-%.result
	$(Q)cat $^

define check-target =
check-$(1).result: $(patsubst %,run_%.$(1),$(TARGETS))
	$(Q){ echo "===== $$@ SUMMARY ====="; \
	      printf "PASSED: "; cat *$(1)*.test-result | grep -c OK; \
	      printf "FAILED: "; cat *$(1)*.test-result | grep -c FAILED; \
	      true; } > $$@
endef

$(foreach c,$(COMPILERS),$(eval $(call check-target,$(c))))

# Per-function test targets, e.g. test-memcpy.
define check-single =
test-$(1):$(foreach c,$(COMPILERS),run_$(1).$(c))
endef

$(foreach t,$(TARGETS),$(eval $(call check-single,$(t))))

run_%:$(foreach l,$(FORTIFY_LEVELS),runone_%_$(l).test-result)
	@true

runone_%.test-result:test_%
	$(Q){ ./$< > /dev/null; \
	      ./$< 1 1 1 > /dev/null; \
	      ./$< 1 1 1 1 > /dev/null; } \
	    && { echo "$< OK" | tee $@; } \
	    || { echo "$< FAILED" | tee $@; }

static-build-cmd = ! $$(STATIC_CHECK) || $(1) \
		-D_FORTIFY_SOURCE=$(2) $$(CFLAGS_STATIC) $$< 2>&1 \
		| grep ' error: ';

build-cmd = $(1) -D_FORTIFY_SOURCE=$(2) $$(DEFAULT_CFLAGS) $$< -o $$@

# Targets for all combinations of compiler and fortification levels.
define build-target =
test_%.$(1)_$(2):test_%.c
	$(Q)$(call static-build-cmd,$(1),$(2))
	$(Q)$(call build-cmd,$(1),$(2))
endef

$(foreach c,$(COMPILERS),$(foreach l,$(FORTIFY_LEVELS),$(eval \
	$(call build-target,$(c),$(l)))))

clean:
	for target in $(TARGETS); do $(RM) $(patsubst %,test_$$target.%*,$(COMPILERS)) ; done
	$(RM) $(PKGNAME).tgz
	$(RM) *.result

dist: $(PKGNAME).tgz

$(PKGNAME).tgz: $(patsubst %,test_%.c, $(TARGETS)) Makefile README.rst
	$(RM) -rf $(PKGNAME)
	mkdir $(PKGNAME)
	cp $^ $(PKGNAME)/
	tar czf $@ $(PKGNAME)/
	$(RM) -rf $(PKGNAME)

