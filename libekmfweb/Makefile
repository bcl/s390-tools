include ../common.mak

ifneq (${HAVE_OPENSSL},0)
	ifneq (${HAVE_JSONC},0)
		ifneq (${HAVE_LIBCURL},0)
			BUILD_TARGETS += libekmfweb.so
			INSTALL_TARGETS += install-libekmfweb.so
		else
			BUILD_TARGETS += skip-libekmfweb-curl
			INSTALL_TARGETS += skip-libekmfweb-curl
		endif
	else
		BUILD_TARGETS += skip-libekmfweb-jsonc
		INSTALL_TARGETS += skip-libekmfweb-jsonc
	endif
else
	BUILD_TARGETS += skip-libekmfweb-openssl
	INSTALL_TARGETS += skip-libekmfweb-openssl
endif

libs = $(rootdir)/libutil/libutil.a

detect-openssl-version.dep:
	echo "#include <openssl/opensslv.h>" > detect-openssl-version.dep
	echo "#include <openssl/evp.h>" >> detect-openssl-version.dep
	echo "#if OPENSSL_VERSION_NUMBER < 0x10101000L" >> detect-openssl-version.dep
	echo "  #error openssl version 1.1.1 is required" >> detect-openssl-version.dep
	echo "#endif" >> detect-openssl-version.dep
	echo "static void __attribute__((unused)) test(void) {" >> detect-openssl-version.dep
	echo "    EVP_PKEY_meth_remove(NULL);" >> detect-openssl-version.dep
	echo "}" >> detect-openssl-version.dep

check-dep-libekmfweb: detect-openssl-version.dep
	$(call check_dep, \
		"libekmfweb", \
		"detect-openssl-version.dep", \
		"openssl-devel version >= 1.1.1", \
		"HAVE_OPENSSL=0", \
		-I. -lcrypto)
	$(call check_dep, \
		"libekmfweb", \
		"json-c/json.h", \
		"json-c-devel", \
		"HAVE_JSONC=0")
	$(call check_dep, \
		"libekmfweb", \
		"curl/curl.h", \
		"libcurl-devel", \
		"HAVE_LIBCURL=0")
	touch check-dep-libekmfweb

skip-libekmfweb-openssl:
	echo "  SKIP    libekmfweb due to HAVE_OPENSSL=0"

skip-libekmfweb-jsonc:
	echo "  SKIP    libekmfweb due to HAVE_JSONC=0"

skip-libekmfweb-curl:
	echo "  SKIP    libekmfweb due to HAVE_LIBCURL=0"

all: $(BUILD_TARGETS)

ekmfweb.o: check-dep-libekmfweb ekmfweb.c utilities.h cca.h $(rootdir)include/ekmfweb/ekmfweb.h
utilities.o: check-dep-libekmfweb utilities.c utilities.h $(rootdir)include/ekmfweb/ekmfweb.h
cca.o: check-dep-libekmfweb cca.c cca.h utilities.h $(rootdir)include/ekmfweb/ekmfweb.h

libekmfweb.so: ALL_CFLAGS += -fPIC
libekmfweb.so: LDLIBS = -ljson-c -lcrypto -lssl -lcurl -ldl -shared
libekmfweb.so: LDFLAGS = -shared -Wl,--version-script=libekmfweb.map \
	-Wl,-z,defs,-Bsymbolic
libekmfweb.so: ekmfweb.o utilities.o cca.o
	$(LINK) $(ALL_LDFLAGS) $^ $(LDLIBS) -o $@

install-libekmfweb.so: libekmfweb.so
	$(INSTALL) -g $(GROUP) -o $(OWNER) -m 755 -T libekmfweb.so $(DESTDIR)$(LIB64DIR)/libekmfweb.so
	$(INSTALL) -d -m 770 $(DESTDIR)$(USRINCLUDEDIR)/ekmfweb
	$(INSTALL) -g $(GROUP) -o $(OWNER) -m 755 $(rootdir)include/ekmfweb/ekmfweb.h $(DESTDIR)$(USRINCLUDEDIR)/ekmfweb

install: all $(INSTALL_TARGETS)

clean:
	rm -f *.o libekmfweb.so check-dep-libekmfweb detect-openssl-version.dep

.PHONY: all install clean skip-libekmfweb-openssl skip-libekmfweb-jsonc \
	skip-libekmfweb-curl install-libekmfweb.so
