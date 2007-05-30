/*
 * Copyright (c) 2006 Coova Technologies Ltd
 *
 */

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "../config.h"

/*
 *   I do not like this here, but otherwise
 *   __u64 is not defined. Set by -ansi
 */

#undef __STRICT_ANSI__

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <resolv.h> 
#include <stdarg.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/un.h>

#if defined(__linux__)
#include <asm/types.h>
#include <linux/if.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_tun.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#elif defined (__FreeBSD__)  || defined (__APPLE__)
#include <net/if.h>
#include <net/bpf.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <ifaddrs.h>
#endif

#ifdef HAVE_NET_IF_TUN
#include <net/if_tun.h>
#endif

#ifndef EIDRM
#define EIDRM   EINVAL
#endif
#ifndef ENOMSG
#define ENOMSG  EAGAIN
#endif

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if defined(HAVE_NET_IF_H) && !defined(__linux__)
#include <net/if.h>
#endif

#ifdef HAVE_NET_IF_TUN_H
#include <net/if_tun.h>
#endif

#ifdef HAVE_NET_ETHERNET_H
#include <net/ethernet.h>
#endif

#ifdef HAVE_ASM_TYPES_H
#include <asm/types.h>
#endif

#ifdef HAVE_NET_ROUTE_H
#include <net/route.h>
#endif

#include <net/if_arp.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#ifdef MTRACE
#include <mcheck.h> 
#endif

#ifdef DMALLOC
#include <dmalloc.h>
#endif

#include <stdio.h>
#include <time.h> 
#include <stdint.h>
#include <sys/param.h>
#ifdef linux
# include <endian.h>
#endif

#if (!defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN))
#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(i386) || defined(__i386__) || defined(__i486__) || \
     defined(__i586__) || defined(__i686__) || defined(vax) || defined(MIPSEL))
# define LITTLE_ENDIAN 1
# define BIG_ENDIAN 0
#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) || \
      (defined(sparc) || defined(POWERPC) || defined(mc68000) || defined(sel))
# define LITTLE_ENDIAN 0
# define BIG_ENDIAN 1
#else
# define LITTLE_ENDIAN 0
# define BIG_ENDIAN 0
#endif
#endif

#endif
