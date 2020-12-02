PKGNAME=fortify-test-suite

ifdef SYSROOT
	USE_SYSROOT = -isysroot $(SYSROOT)
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

TARGETS=memcpy memmove mempcpy memset snprintf sprintf stpcpy strcat strcpy strncat strncpy vsnprintf vsprintf

check:$(patsubst %,check-%,$(COMPILERS))

define check-target =
check-$(1):$(patsubst %,run_%.$(1),$(TARGETS))
	@echo "===== $$@ OK ====="
endef

$(foreach c,$(COMPILERS),$(eval $(call check-target,$(c))))

# Per-function test targets, e.g. test-memcpy.
define check-single =
test-$(1):$(foreach c,$(COMPILERS),run_$(1).$(c))
endef

$(foreach t,$(TARGETS),$(eval $(call check-single,$(t))))

run_%:$(foreach l,$(FORTIFY_LEVELS),runone_%_$(l))
	true

runone_%:test_%
	$(Q)./$<
	$(Q)! ./$< 1 1 1
	$(Q)! ./$< 1 1 1 1
	$(Q)echo "$< OK"

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

dist: $(PKGNAME).tgz

$(PKGNAME).tgz: $(patsubst %,test_%.c, $(TARGETS)) Makefile README.rst
	$(RM) -rf $(PKGNAME)
	mkdir $(PKGNAME)
	cp $^ $(PKGNAME)/
	tar czf $@ $(PKGNAME)/
	$(RM) -rf $(PKGNAME)

