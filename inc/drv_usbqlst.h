/* (c) 2008 Jungo Ltd. All Rights Reserved. Jungo Confidential */
/*
 * Copyright (c) 2004 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) and by Charles M. Hannum.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _JMS_QUIRKS_H_
#define _JMS_QUIRKS_H_

struct umass_devdescr_t {
    u32    vid;
#       define VID_WILDCARD     0xffffffff
#       define VID_EOT          0xfffffffe
    u32    pid;
#       define PID_WILDCARD     0xffffffff
#       define PID_EOT          0xfffffffe
    u32    rid;
#       define RID_WILDCARD     0xffffffff
#       define RID_EOT          0xfffffffe

    /* wire and command protocol */
    u16    proto;
#       define UMASS_PROTO_BBB          0x0001  /* USB wire protocol */
#       define UMASS_PROTO_CBI          0x0002
#       define UMASS_PROTO_CBI_I        0x0004
#       define UMASS_PROTO_WIRE         0x00ff  /* USB wire protocol mask */
#       define UMASS_PROTO_SCSI         0x0100  /* command protocol */
#       define UMASS_PROTO_ATAPI        0x0200
#       define UMASS_PROTO_UFI          0x0400
#       define UMASS_PROTO_RBC          0x0800
#       define UMASS_PROTO_COMMAND      0xff00  /* command protocol mask */

    /* Device specific quirks */
    u16    quirks;
};

#define NO_QUIRKS                0x0000
    /* The drive does not support Test Unit Ready. Convert to Start Unit
    */
#define NO_TEST_UNIT_READY       0x0001
    /* The drive does not reset the Unit Attention state after REQUEST
     * SENSE has been sent. The INQUIRY command does not reset the UA
     * either, and so CAM runs in circles trying to retrieve the initial
     * INQUIRY data.
     */
#define RS_NO_CLEAR_UA           0x0002
    /* The drive does not support START STOP.  */
#define NO_START_STOP            0x0004
    /* Don't ask for full inquiry data (255b).  */
#define FORCE_SHORT_INQUIRY      0x0008
    /* Needs to be initialised the Shuttle way */
#define SHUTTLE_INIT             0x0010
    /* Drive needs to be switched to alternate iface 1 */
#define ALT_IFACE_1              0x0020
    /* Drive does not do 1Mb/s, but just floppy speeds (20kb/s) */
#define FLOPPY_SPEED             0x0040
    /* The device can't count and gets the residue of transfers wrong */
#define IGNORE_RESIDUE           0x0080
    /* No GetMaxLun call */
#define NO_GETMAXLUN             0x0100
    /* The device uses a weird CSWSIGNATURE. */
#define WRONG_CSWSIG             0x0200
    /* Device cannot handle INQUIRY so fake a generic response */
#define NO_INQUIRY               0x0400
    /* Device cannot handle INQUIRY EVPD, return CHECK CONDITION */
//#define NO_INQUIRY_EVPD          0x0800
	/* Roy, The device respond to request sense take time above 3 seconds */
#define LONG_INQUIRY_TIMEOUT 	0x0800
    /* The device has Residue endianess in BE */
#define SWAP_RESIDUE             0x1000
/* The device does not support MODE_SENSE */
#define NO_MODE_SENSE                   0x2000
/* Roy, The device should be operate full speed only with us */ 
#define FULL_SPEED_CONFIG		0X4000
/* Roy, The device respond to request sense take time above 3 seconds */
#define LONG_REQUEST_SENSE_TIMEOUT 0x8000
//uint16_t umass_get_quirks(void *dev_h);

void USB_SetQuirkList(struct umass_devdescr_t *QuirkList);

#endif

