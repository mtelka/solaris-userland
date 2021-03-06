/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef __STDCXX_CONFIG_H
#define __STDCXX_CONFIG_H

#if defined(__i386) || defined(__amd64)

#if defined(__amd64)
#include "stdcxx_amd64.h"
#else
#include "stdcxx_i386.h"
#endif

#elif defined(__sparc) || defined(__sparcv9)

#if defined(__sparcv9)
#include "stdcxx_sparcv9.h"
#else
#include "stdcxx_sparc.h"
#endif

#else
#error "Unknown Solaris ISA."
#endif

#endif /* __STDCXX_CONFIG_H */

