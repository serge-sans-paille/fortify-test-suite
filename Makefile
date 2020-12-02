PKGNAME=fortify-test-suite

ifdef SYSROOT
	USE_SYSROOT = -isysroot $(SYSROOT)
else
	USE_SYSROOT =
endif

DEFAULT_CFLAGS = $(CFLAGS) -O1 $(USE_SYSROOT)
CFLAGS_STATIC=$(DEFAULT_CFLAGS) -DSTATIC_CHECK -Werror
STATIC_CHECK ?= false
COMPILERS = gcc clang

TARGETS=test_memcpy test_memmove test_mempcpy test_memset test_snprintf test_sprintf test_stpcpy test_strcat test_strcpy test_strncat test_strncpy test_vsnprintf test_vsprintf

check:$(patsubst %,check-%,$(COMPILERS))

check-target = check-$(1):$(patsubst test_%,run_%.$(1),$(TARGETS)); \
	@echo "===== $$@ OK ====="

$(call check-target,gcc)
$(call check-target,clang)

check-single = test-$(1):$(foreach c,$(COMPILERS),run_$(1).$(c))

$(call check-single,memcpy)
$(call check-single,memmove)
$(call check-single,mempcpy)
$(call check-single,memset)
$(call check-single,snprintf)
$(call check-single,sprintf)
$(call check-single,stpcpy)
$(call check-single,strcat)
$(call check-single,strcpy)
$(call check-single,strncat)
$(call check-single,strncpy)
$(call check-single,vsnprintf)
$(call check-single,vsprintf)

FORTIFY_LEVELS = 1 2

run_%:$(foreach l,$(FORTIFY_LEVELS),runone_%_$(l))
	true

runone_%:test_%
	./$<
	! ./$< 1 1 1
	! ./$< 1 1 1 1
	@echo "$< OK"

static-build-cmd = ! $$(STATIC_CHECK) || $(1) \
		-D_FORTIFY_SOURCE=$(2) $$(CFLAGS_STATIC) $$< 2>&1 \
		| grep ' error: ';

build-cmd = $(1) -D_FORTIFY_SOURCE=$(2) $$(DEFAULT_CFLAGS) $$< -o $$@

build-target = test_%.$(1)_$(2):test_%.c; \
	$(call static-build-cmd,$(1),$(2)) \
	$(call build-cmd,$(1),$(2))

$(call build-target,gcc,1)
$(call build-target,gcc,2)
$(call build-target,clang,1)
$(call build-target,clang,2)

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

