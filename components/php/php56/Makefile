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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

include $(WS_COMPONENTS)/php/php-metadata.mk

COMPONENT_NAME=		php
COMPONENT_VERSION=	$(UL_PHP_VERSION)
COMPONENT_PROJECT_URL=	http://php.net/
COMPONENT_SRC=		$(PHP_COMPONENT_SRC)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=\
    sha256:0af0045745d61eeb74a3ea744529a2481b27cb689da720e6c0250675043724e4
COMPONENT_ARCHIVE_URL=	http://php.net/get/$(COMPONENT_ARCHIVE)/from/this/mirror
COMPONENT_BUGDB=	utility/php
TPNO=			22435

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

include $(PHP_TOP_DIR)/php.mk

# We patch configure.in to allow building just modules (no SAPI's), e.g. intl.
# Since we are sharing the source, regenerate configure here.
COMPONENT_PREP_ACTION += (cd $(SOURCE_DIR) ; autoconf) ;

ASLR_MODE = $(ASLR_ENABLE)

include enable-extensions.mk

CONFIGURE_OPTIONS += --enable-dtrace
REQUIRED_PACKAGES += system/dtrace
COMPONENT_BUILD_ENV += PATH="$$PATH:/usr/sbin"

# .conf files go under /etc, not /usr
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/php/$(UL_PHP_MINOR_VERSION)
# var doesn't go under /usr either!
CONFIGURE_OPTIONS +=	--localstatedir=/var/php/$(UL_PHP_MINOR_VERSION)
# Nor does php.ini and its friends.
CONFIGURE_OPTIONS +=	--with-config-file-path=/etc/php/$(UL_PHP_MINOR_VERSION)
CONFIGURE_OPTIONS +=	--with-config-file-scan-dir=/etc/php/$(UL_PHP_MINOR_VERSION)/conf.d
# Nor does PEAR (default: $PREFIX/lib/php)
CONFIGURE_OPTIONS +=	--with-pear=/var/php/$(UL_PHP_MINOR_VERSION)/pear

PROTOUSRPHPVERDIR = $(PROTO_DIR)/$(CONFIGURE_PREFIX)
# Adapted from PHP 5.3 Makefile.
# Creates alternate versions of the scripts needed for building extensions
# separately, since the generated versions of these scripts hardcode configuring
# for a PHP that is installed on the system.
COMPONENT_POST_INSTALL_ACTION += \
	( set -e; \
	mkdir -p proto-scripts; \
	cat $(BUILD_DIR_64)/scripts/phpize | \
	 sed -e "s,^\#!/bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^includedir=.*%includedir=$(PROTOUSRPHPVERDIR)/include/php%" | \
	 sed -e "s%^phpdir=.*%phpdir=$(SOURCE_DIR)%"  | \
	 sed -e "s%phpdir/phpize.m4%phpdir/scripts/phpize.m4%" | \
	 sed -e "s%$PHP_AUTOCONF   || exit 1%$PHP_AUTOCONF -f   || exit 1%" | \
	 sed -e "s%$PHP_AUTOHEADER || exit 1%$PHP_AUTOHEADER -f || exit 1%" | \
	 sed -e 's%(cd "$$phpdir" && cp $$FILES_BUILD "$$builddir"/build)%(cd "$$phpdir/build" \&\& cp $$FILES_BUILD "$$builddir"/build)%' | \
	 sed -e "s%^builddir=.*%builddir=$(BUILD_DIR_64)%" \
	 > proto-scripts/phpize-proto ; \
	chmod 755 proto-scripts/phpize-proto ) ; \
	( set -e; \
	 cat $(BUILD_DIR_64)/scripts/php-config | \
	 sed -e "s,^\#! /bin/sh,\#!$(CONFIG_SHELL)," | \
	 sed -e "s%^prefix=.*%prefix=$(PROTOUSRPHPVERDIR)%" | \
	 sed -e "s%^include_dir=.*%include_dir=$(PROTOUSRPHPVERDIR)/include/php%" \
	 > proto-scripts/php-config-proto ; \
	chmod 755 proto-scripts/php-config-proto ) ;

CLEAN_PATHS += proto-scripts

# For picking up php.ini-development and -production
PKG_PROTO_DIRS +=      $(COMPONENT_SRC)

configure:		$(CONFIGURE_64)
build:			$(BUILD_64)
install:		$(INSTALL_64)

# The test results are unstable between runs
$(SKIP_TEST_AT_TOP_LEVEL)
test:			$(TEST_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/libxml2