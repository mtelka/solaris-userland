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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		Kerberos
COMPONENT_MINOR=	1.13
COMPONENT_VERSION=	1.13.3
COMPONENT_PROJECT_URL=	http://web.mit.edu/kerberos/
COMPONENT_SRC=		krb5-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5d4af08ead9b7a1e9493cfd65e821234f151a46736e1ce586f886c8a8e65fabe
COMPONENT_ARCHIVE_URL=	\
	$(COMPONENT_PROJECT_URL)dist/krb5/$(COMPONENT_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/kerberos

TPNO=	26018

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Encoding rules for IPS: MIT KerberosV5 <x>.<y>[.<z>] => IPS <x>.<y>.[<z>|0].0
IPS_COMPONENT_VERSION=	1.13.3.0

# The configure script is not at the top of the source directory.
CONFIGURE_SCRIPT=	$(SOURCE_DIR)/src/configure

# We need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

# Include openldap headers instead of obsolete mozilla ldap headers.
CPPFLAGS += -I$(USRINCDIR)/openldap

# Temporary solution until we can fix this upstream with MIT, which currently
# depends on implicit binding of libc.  Here we explicitly link with libc to
# satisfy this dependency.
# If you make changes to LDFLAGS, check krb5-config and 052-krb5-config.patch.
LDFLAGS += -lc -z defs

CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += DEFKTNAME="FILE:$(ETCDIR)/krb5/krb5.keytab"
CONFIGURE_ENV += DEFCKTNAME="FILE:/var/user/%{username}/client.keytab"

# Other CONFIGURE_OPTIONS assignments coming from make-rules/configure.mk
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS.32 += --libexecdir=$(USRLIBDIR)
CONFIGURE_OPTIONS.64 += --libexecdir=$(USRLIBDIR)/$(MACH64)
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/kerberosv5
# to avoid executing subprocesses from /usr/[s]bin/$(MACH64):
CONFIGURE_OPTIONS += --bindir=$(USRBINDIR)
CONFIGURE_OPTIONS += --sbindir=$(USRSBINDIR)
CONFIGURE_OPTIONS += --with-crypto-impl=openssl
CONFIGURE_OPTIONS += --with-ldap
CONFIGURE_OPTIONS += --with-prng-alg=os
CONFIGURE_OPTIONS += --with-tcl=$(USRDIR)
CONFIGURE_OPTIONS += --without-system-verto

COMPONENT_PRE_CONFIGURE_ACTION = \
	cd $(SOURCE_DIR)/src/ && $(SOURCE_DIR)/src/util/reconf

PROTOULD = $(PROTOUSRLIBDIR)

COMPONENT_TEST_ARGS += LD_LIBRARY_PATH="$(PROTOULD):$(PROTOULD)/$(MACH64):"

# MIT's test suite is not well suited for master results processing/filtering
# but since the test implementation will return failure to the uland build,
# this is good enough.  The following disables master results processing.
COMPONENT_TEST_CREATE_TRANSFORMS=
COMPONENT_TEST_PERFORM_TRANSFORM=
COMPONENT_TEST_COMPARE=

# We don't ship Solaris specific files as patches to ease maintenance.
# We rather copy the files to the right directories.
COMPONENT_PREP_ACTION= \
	$(CP) Solaris/getuid.c $(SOURCE_DIR)/src/lib/krb5/os/; \
	$(CP) Solaris/g_utils.c $(SOURCE_DIR)/src/lib/gssapi/mechglue/; \
	$(CP) Solaris/kadm_host_srv_names.c $(SOURCE_DIR)/src/lib/kadm5/; \
	$(CP) Solaris/kt_findrealm.c $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/kt_solaris.c $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/kt_solaris.h $(SOURCE_DIR)/src/lib/krb5/keytab/; \
	$(CP) Solaris/libgss_stubs.c $(SOURCE_DIR)/src/lib/gssapi/mechglue/; \
	$(CP) Solaris/missing_interfaces.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/privacy_allowed.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/prof_solaris.c $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/prof_solaris.h $(SOURCE_DIR)/src/lib/krb5/; \
	$(CP) Solaris/rc_mem.c $(SOURCE_DIR)/src/lib/krb5/rcache; \
	$(CP) Solaris/rc_mem.h $(SOURCE_DIR)/src/lib/krb5/rcache; \
	$(CP) Solaris/safechown.c $(SOURCE_DIR)/src/lib/krb5/os; \
	$(CP) Solaris/util_ordering.c $(SOURCE_DIR)/src/lib/gssapi/generic

# We move xdr_alloc.c and supporting dyn code from libgssrpc directly
# into libkadm5srv_mit. kadmind is the only consumer anyway.
SRCLIB=$(SOURCE_DIR)/src/lib
COMPONENT_PREP_ACTION += ;\
	$(CP) $(SRCLIB)/rpc/xdr_alloc.c $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyn.c $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyn.h $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dynP.h $(SRCLIB)/kadm5/srv/; \
	$(CP) $(SRCLIB)/rpc/dyntest.c $(SRCLIB)/kadm5/srv/; \

# Common flags used to create the filter libs below
FILTLIBFLAGS = -G -Bdirect -z defs -z text

$(BUILD_32): COMPONENT_POST_BUILD_ACTION= \
	$(CC) -o $(BUILD_DIR)/$(MACH32)/lib/libgss.so.1 \
	    -hlibgss.so.1 $(FILTLIBFLAGS) -lc \
	    -M$(COMPONENT_DIR)/Solaris/libgss.mapfile-vers \
	    -R$(USRLIBDIR)/krb5 \
	    -z discard-unused=dependencies \
	    -L $(BUILD_DIR)/$(MACH32)/lib -lkrb5support \
	    $(BUILD_DIR)/$(MACH32)/lib/gssapi/mechglue/libgss_stubs.o && \
	$(CC) -o $(BUILD_DIR)/$(MACH32)/lib/libkrb5.so.1 \
	    -hlibkrb5.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkrb5.mapfile-vers \
	    $(BUILD_DIR)/$(MACH32)/lib/krb5/missing_interfaces.o \
	    $(BUILD_DIR)/$(MACH32)/lib/krb5/privacy_allowed.o && \
	$(LD) -o $(BUILD_DIR)/$(MACH32)/lib/libkadm5clnt.so.1 \
	    -hlibkadm5clnt.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkadm5clnt.mapfile-vers;

$(BUILD_64): COMPONENT_POST_BUILD_ACTION= \
	$(CC) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libgss.so.1 \
	    -hlibgss.so.1 $(FILTLIBFLAGS) -lc \
	    -M$(COMPONENT_DIR)/Solaris/libgss.mapfile-vers \
	    -R$(USRLIBDIR)/krb5/$(MACH64) \
	    -z discard-unused=dependencies \
	    -L $(BUILD_DIR)/$(MACH64)/lib -lkrb5support \
	    $(BUILD_DIR)/$(MACH64)/lib/gssapi/mechglue/libgss_stubs.o && \
	$(CC) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libkrb5.so.1 \
	    -hlibkrb5.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkrb5.mapfile-vers \
	    $(BUILD_DIR)/$(MACH64)/lib/krb5/missing_interfaces.o \
	    $(BUILD_DIR)/$(MACH64)/lib/krb5/privacy_allowed.o && \
	$(LD) -m64 -o $(BUILD_DIR)/$(MACH64)/lib/libkadm5clnt.so.1 \
	    -hlibkadm5clnt.so.1 $(FILTLIBFLAGS) \
	    -M$(COMPONENT_DIR)/Solaris/libkadm5clnt.mapfile-vers;

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION= \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libgss.so.1 \
		$(PROTO_DIR)$(USRLIBDIR); \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libkrb5.so.1 \
		$(PROTO_DIR)$(USRLIBDIR); \
	$(CP) $(BUILD_DIR)/$(MACH32)/lib/libkadm5clnt.so.1 \
		$(PROTO_DIR)$(USRLIBDIR);

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION= \
	$(MKDIR) -p $(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libgss.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libkrb5.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64); \
	$(CP) $(BUILD_DIR)/$(MACH64)/lib/libkadm5clnt.so.1 \
		$(PROTO_DIR)$(USRLIBDIR)/$(MACH64);

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:	$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# build does this always
test:	$(TEST_32_and_64)

REQUIRED_PACKAGES += developer/test/dejagnu
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
