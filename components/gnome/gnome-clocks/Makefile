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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=             64
COMPILER=               gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-clocks
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Gnome-Clocks
COMPONENT_ARCHIVE_HASH= \
	sha256:ca0818ec89e3539201da6b5388365e3d66df815198beccc90e2be44c7822baa0
COMPONENT_BUGDB=	gnome/applications

TPNO=			25788

TEST_TARGET = $(NO_TESTS)

# Needs gsound, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

CONFIGURE_OPTIONS += --disable-static

# Assumes GNU msgfmt in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Delete when libgweather is installed on the build server
WEATHER_BASE = $(WS_COMPONENTS)/gnome/libgweather/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(WEATHER_BASE)$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS += -L $(WEATHER_BASE)$(USRLIB.$(BITS))

CPPFLAGS += -I$(WEATHER_BASE)/usr/include/libgweather-3.0

# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/gnome/libgweather/build/manifest-$(MACH)-libgweather.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n -e '/GSED/d' -e 's/REQUIRED_PACKAGES +=//p' ../libgweather/Makefile)
#end Delete


REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/geoclue
REQUIRED_PACKAGES += library/desktop/geocode-glib
REQUIRED_PACKAGES += library/desktop/gsound
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += system/library/math