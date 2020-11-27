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

