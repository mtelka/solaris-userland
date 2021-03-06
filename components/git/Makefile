#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		git
COMPONENT_VERSION=	2.12.0
COMPONENT_PROJECT_URL=	http://git-scm.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1821766479062d052cc1897d0ded95212e81e5c7f1039786bc4aec2225a32027
COMPONENT_ARCHIVE_URL=	https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	5350

TPNO=			34354

#
# man pages are a separate archive
#
COMPONENT_SRC_1 =	$(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.xz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:8b8356f8d50eff6499c5d05e87c106a7b1b48bd16de1742fa022631909804773
COMPONENT_ARCHIVE_URL_1 = https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1 =		-r $(COMPONENT_SRC_1)
PKG_PROTO_DIRS +=	$(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/common.mk

PKG_HARDLINKS +=	usr/lib/git-core/git
PKG_HARDLINKS +=	usr/lib/git-core/git-cvsserver
PKG_HARDLINKS +=	usr/lib/git-core/git-gui
PKG_HARDLINKS +=	usr/lib/git-core/git-remote-ftps
PKG_HARDLINKS +=	usr/lib/git-core/git-shell
PKG_HARDLINKS +=	usr/lib/git-core/git-upload-pack

PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib
CONFIGURE_SCRIPT    =	$(@D)/configure
CPPFLAGS += "-I/usr/include/pcre"

CONFIGURE_OPTIONS  +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS  +=	--libexecdir=$(USRLIBDIR)
CONFIGURE_OPTIONS  +=	--with-libpcre
CONFIGURE_OPTIONS  +=	--with-perl=$(PERL)
CONFIGURE_OPTIONS  +=	--with-python=$(PYTHON.$(PYTHON_VERSION))

# Build fails if environment variable PROFILE is set.
COMPONENT_BUILD_ENV+=	PROFILE=
COMPONENT_INSTALL_ENV+=	PROFILE=
COMPONENT_TEST_ENV+=	PROFILE=

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS+=	V=1

PERL_CONFIG = $(shell $(PERL) -MConfig -e 'print "$$Config{$(1)}"')

# We want the perl modules to install the vendor_perl directory, and their
# manpages to install in the normal perl manpage directory, but the default
# behavior is to put the modules in /usr/lib.  Setting these four variables
# massages the perl to get files to go where we want.
COMPONENT_INSTALL_ARGS+=	INSTALL="$(INSTALL)"
COMPONENT_INSTALL_ARGS+=	VENDORPREFIX=$(call PERL_CONFIG,installvendorlib)
COMPONENT_INSTALL_ARGS+=	PERLPREFIX=$(call PERL_CONFIG,installprefix)
COMPONENT_INSTALL_ARGS+=	INSTALLVENDORLIB='$$(VENDORPREFIX)'
COMPONENT_INSTALL_ARGS+=	INSTALLVENDORMAN3DIR='$$(INSTALLMAN3DIR)'

# get rid of terminal escape codes in test output
COMPONENT_TEST_ENV = TERM=dumb

# Some tests (like t5539-fetch-http-shallow.sh) fail if the proxies are set.
COMPONENT_TEST_ENV += http_proxy=
COMPONENT_TEST_ENV += https_proxy=
COMPONENT_TEST_ENV += HTTP_PROXY=
COMPONENT_TEST_ENV += HTTPS_PROXY=

# Some tests (like t9402-git-cvsserver-refs.sh) need GNU diff.
COMPONENT_TEST_ENV += PATH="$(GNUBIN):$(PATH)"

# many failures; keep going; later versions of git are much cleaner
COMPONENT_TEST_ARGS += -k -i
# If GITTEST_JOBS is set, then run the jobs in parallel (to that number)
COMPONENT_TEST_ARGS += $(if $(GITTEST_JOBS),-j$(GITTEST_JOBS),)
COMPONENT_TEST_TARGETS = test
# Enable tests requiring Apache
COMPONENT_TEST_TARGETS += LIB_HTTPD_PATH=/usr/apache2/2.4/bin/httpd
COMPONENT_TEST_TARGETS += LIB_HTTPD_MODULE_PATH=/usr/apache2/2.4/libexec
# Put each test result in a file; necessary if jobs run in parallel
COMPONENT_TEST_TARGETS += GIT_TEST_OPTS=--tee
COMPONENT_TEST_TARGETS += DEFAULT_TEST_TARGET=test-noclean
# Compile the test results and put that into the test output file instead
COMPONENT_POST_TEST_ACTION = \
	(cd $(COMPONENT_TEST_DIR)/t/test-results; for i in *.out; do \
		echo "*** $${i%.out}.sh ***"; \
		cat $$i; \
	done; \
	cd ..; \
	$(GMAKE) -s aggregate-results) &> $(COMPONENT_TEST_OUTPUT)

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git.
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))
COMPONENT_PRE_CONFIGURE_ACTION += ; (cd $(@D); $(GMAKE) configure)


REQUIRED_PACKAGES += crypto/gnupg
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += web/server/apache-24
