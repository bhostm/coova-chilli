/* 
 * Packet Headers
 * Copyright (C) 2003, 2004, 2005 Mondru AB.
 * Copyright (C) 2007-2009 Coova Technologies, LLC. <support@coova.com>
 *
 * The contents of this file may be used under the terms of the GNU
 * General Public License Version 2, provided that the above copyright
 * notice and this permission notice is included in all copies or
 * substantial portions of the software.
 * 
 */


#ifndef _PKT_H
#define _PKT_H

#define PKT_ETH_ALEN              6 /* Ethernet Address Length */
#define PKT_ETH_HLEN             14 /* Ethernet Header Length */

#define PKT_ETH_PROTO_IP     0x0800
#define PKT_ETH_PROTO_ARP    0x0806
#define PKT_ETH_PROTO_EAPOL  0x888e

#define PKT_ETH_8021Q_TPID   0x8100

#define PKT_IP_PLEN            1500 /* IP Payload Length */
#define PKT_IP_VER_HLEN        0x45 
#define PKT_IP_ALEN               4
#define PKT_IP_HLEN              20

#define PKT_IP_PROTO_ICMP         1 /* ICMP Protocol number */
#define PKT_IP_PROTO_TCP          6 /* TCP Protocol number */
#define PKT_IP_PROTO_UDP         17 /* UDP Protocol number */
#define PKT_IP_PROTO_GRE         47 /* GRE Protocol number */

#define PKT_UDP_HLEN              8
#define PKT_TCP_HLEN             20
#define PKT_DOT1X_HLEN            4

#define PKT_EAP_PLEN           1500 /* Dot1x Payload length */

#define DHCP_TAG_VLEN           255 /* Tag value always shorter than this */
#define EAPOL_TAG_VLEN          255 /* Tag value always shorter than this */

#define DHCP_HTYPE_ETH            1
#define DHCP_CHADDR_LEN          16 /* Length of client hardware address */
#define DHCP_SNAME_LEN           64 /* Length of server host name */
#define DHCP_FILE_LEN           128 /* Length of boot file name*/
#define DHCP_OPTIONS_LEN        312 /* Length of optional parameters field */
#define DHCP_MIN_LEN   28+16+64+128 /* Length of packet excluding options */
#define DHCP_LEN  (DHCP_MIN_LEN+DHCP_OPTIONS_LEN)

#define PKT_BUFFER (PKT_IP_PLEN+PKT_ETH_HLEN+4)


struct pkt_ethhdr_t {
  uint8_t  dst[PKT_ETH_ALEN];
  uint8_t  src[PKT_ETH_ALEN];
  uint16_t prot;
} __attribute__((packed));


struct pkt_ethhdr8021q_t {
  uint8_t  dst[PKT_ETH_ALEN];
  uint8_t  src[PKT_ETH_ALEN];
  uint16_t tpid;
  uint16_t pcp_cfi_vid;
  uint16_t prot;
} __attribute__((packed));


struct pkt_iphdr_t {
  uint8_t  version_ihl;
  uint8_t  tos;
  uint16_t tot_len;
  uint16_t id;
  uint16_t frag_off;
  uint8_t  ttl;
  uint8_t  protocol;
  uint16_t check;
  uint32_t saddr;
  uint32_t daddr;
} __attribute__((packed));


struct pkt_ipphdr_t {
  /* Convenience structure:
     Same as pkt_iphdr_t, but also
     with ports (UDP and TCP packets) */
  uint8_t  version_ihl;
  uint8_t  tos;
  uint16_t tot_len;
  uint16_t id;
  uint16_t frag_off;
  uint8_t  ttl;
  uint8_t  protocol;
  uint16_t check;
  uint32_t saddr;
  uint32_t daddr;
  uint16_t sport;
  uint16_t dport;
} __attribute__((packed));


/*
  0      7 8     15 16    23 24    31  
  +--------+--------+--------+--------+ 
  |     Source      |   Destination   | 
  |      Port       |      Port       | 
  +--------+--------+--------+--------+ 
  |                 |                 | 
  |     Length      |    Checksum     | 
  +--------+--------+--------+--------+ 
  |                                     
  |          data octets ...            
  +---------------- ...                 
  
  User Datagram Header Format
*/

struct pkt_udphdr_t {
  uint16_t src;
  uint16_t dst;
  uint16_t len;
  uint16_t check;
} __attribute__((packed));

/*
  TCP Header Format

    0                   1                   2                   3   
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Sequence Number                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Acknowledgment Number                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Data |           |U|A|P|R|S|F|                               |
   | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
   |       |           |G|K|H|T|N|N|                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Checksum            |         Urgent Pointer        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             data                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

struct pkt_tcphdr_t {
  uint16_t src;
  uint16_t dst;
  uint32_t seq;
  uint32_t ack;
  uint8_t  offres;
  uint8_t  flags;
  uint16_t win;
  uint16_t check;
  uint16_t urgent;
  uint8_t options[4];
} __attribute__((packed));

#define TCPHDR_FLAG_FIN (1<<0)
#define TCPHDR_FLAG_SYN (1<<1)
#define TCPHDR_FLAG_RST (1<<2)
#define TCPHDR_FLAG_PSH (1<<3)
#define TCPHDR_FLAG_ACK (1<<4)
#define TCPHDR_FLAG_URG (1<<5)

#define tcphdr_fin(hdr) (((hdr)->flags & TCPHDR_FLAG_FIN)==TCPHDR_FLAG_FIN)
#define tcphdr_syn(hdr) (((hdr)->flags & TCPHDR_FLAG_SYN)==TCPHDR_FLAG_SYN)
#define tcphdr_rst(hdr) (((hdr)->flags & TCPHDR_FLAG_RST)==TCPHDR_FLAG_RST)

/*
  0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     op (1)    |   htype (1)   |   hlen (1)    |   hops (1)    |
   +---------------+---------------+---------------+---------------+
   |                            xid (4)                            |
   +-------------------------------+-------------------------------+
   |           secs (2)            |           flags (2)           |
   +-------------------------------+-------------------------------+
   |                          ciaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          yiaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          siaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          giaddr  (4)                          |
   +---------------------------------------------------------------+
   |                                                               |
   |                          chaddr  (16)                         |
   |                                                               |
   |                                                               |
   +---------------------------------------------------------------+
   |                                                               |
   |                          sname   (64)                         |
   +---------------------------------------------------------------+
   |                                                               |
   |                          file    (128)                        |
   +---------------------------------------------------------------+
   |                                                               |
   |                          options (variable)                   |
   +---------------------------------------------------------------+
*/

struct dhcp_packet_t { /* From RFC 2131 */
  uint8_t op;       /* 1 Message op code / message type.  1 = BOOTREQUEST, 2 = BOOTREPLY */
  uint8_t htype;    /* 1 Hardware address type, see ARP section in "Assigned Numbers" RFC */
  uint8_t hlen;     /* 1 Hardware address length (e.g. '6' for 10mb ethernet).*/
  uint8_t hops;     /* 1 Client sets to zero, optionally used by relay agents when booting via a relay agent.*/
  uint32_t xid;     /* 4 Transaction ID, a random number chosen by the client, used by the client and
		       server to associate messages and responses between a client and a server. */
  uint16_t secs;    /* 2 Filled in by client, seconds elapsed since client began address acquisition or renewal process.*/
  uint8_t flags[2]; /* 2  Flags (see figure 2).*/
  uint32_t ciaddr;  /* 4 Client IP address; only filled in if client is in BOUND, RENEW or REBINDING state
		       and can respond to ARP requests.*/
  uint32_t yiaddr;  /* 4 'your' (client) IP address.*/
  uint32_t siaddr;  /* 4 IP address of next server to use in bootstrap; returned in DHCPOFFER, DHCPACK by server.*/
  uint32_t giaddr;  /* 4 Relay agent IP address, used in booting via a relay agent.*/
  uint8_t chaddr[DHCP_CHADDR_LEN];   /* 16 Client hardware address.*/
  uint8_t sname[DHCP_SNAME_LEN];     /* 64 Optional server host name, null terminated string.*/
  uint8_t file[DHCP_FILE_LEN];       /* 128 Boot file name, null terminated string; "generic" name or null in
					DHCPDISCOVER, fully qualified directory-path name in DHCPOFFER.*/
  uint8_t options[DHCP_OPTIONS_LEN]; /* var Optional parameters field.  See the options documents for a list
					of defined options.*/
} __attribute__((packed));


struct dhcp_tag_t {
  uint8_t t;
  uint8_t l;
  uint8_t v[DHCP_TAG_VLEN];
} __attribute__((packed));


struct arp_packet_t { /* From RFC 826 */
  uint16_t hrd; /* 16.bit: (ar$hrd) Hardware address space (e.g.,
		    Ethernet, Packet Radio Net.) */
  uint16_t pro; /* 16.bit: (ar$pro) Protocol address space.  For
		    Ethernet hardware, this is from the set of type
		    fields ether_typ$<protocol>. */
  uint8_t hln;  /* 8.bit: (ar$hln) byte length of each hardware address */
  uint8_t pln;  /* 8.bit: (ar$pln) byte length of each protocol address */
  uint16_t op;  /* 16.bit: (ar$op)  opcode (ares_op$REQUEST | ares_op$REPLY) */
  uint8_t sha[PKT_ETH_ALEN]; /* nbytes: (ar$sha) Hardware address of
		    sender of this packet, n from the ar$hln field. */
  uint8_t spa[PKT_IP_ALEN];  /* mbytes: (ar$spa) Protocol address of
		    sender of this packet, m from the ar$pln field. */
  uint8_t tha[PKT_ETH_ALEN]; /* nbytes: (ar$tha) Hardware address of
		  target of this packet (if known). */
  uint8_t tpa[PKT_IP_ALEN]; /* mbytes: (ar$tpa) Protocol address of
				 target.*/
} __attribute__((packed));


struct dns_packet_t { /* From RFC 1035 */
  uint16_t id;      /* 16 bit: Generated by requester. Copied in reply */
  uint16_t flags;   /* 16 bit: Flags */
  uint16_t qdcount; /* 16 bit: Number of questions */
  uint16_t ancount; /* 16 bit: Number of answer records */
  uint16_t nscount; /* 16 bit: Number of name servers */
  uint16_t arcount; /* 16 bit: Number of additional records */
  uint8_t  records[PKT_IP_PLEN];
} __attribute__((packed));


struct pkt_dot1xhdr_t {
  uint8_t  ver;
  uint8_t  type;
  uint16_t len;
} __attribute__((packed));

struct eap_packet_t {
  uint8_t  code;
  uint8_t  id;
  uint16_t length;
  uint8_t  type;
  uint8_t  payload[PKT_EAP_PLEN];
} __attribute__((packed));


#define is_8021q(pkt) (((struct pkt_ethhdr8021q_t *)pkt)->tpid == htons(PKT_ETH_8021Q_TPID))
#define get8021q(pkt) (((struct pkt_ethhdr8021q_t *)pkt)->pcp_cfi_vid)

#define sizeofeth2(is8021q)   (PKT_ETH_HLEN+((is8021q)?4:0))
#define sizeofip2(is8021q)    (sizeofeth2(is8021q)+PKT_IP_HLEN)
#define sizeofdot1x2(is8021q) (sizeofeth2(is8021q)+PKT_DOT1X_HLEN)
#define sizeofudp2(is8021q)   (sizeofip2(is8021q)+PKT_UDP_HLEN)
#define sizeoftcp2(is8021q)   (sizeofip2(is8021q)+PKT_TCP_HLEN)

#define sizeofeth(pkt)   sizeofeth2(is_8021q(pkt))
#define sizeofip(pkt)    sizeofip2(is_8021q(pkt))
#define sizeofdot1x(pkt) sizeofdot1x2(is_8021q(pkt))
#define sizeofudp(pkt)   sizeofudp2(is_8021q(pkt))
#define sizeoftcp(pkt)   sizeoftcp2(is_8021q(pkt))
#define sizeofarp(pkt)   (sizeofeth(pkt)+sizeof(struct arp_packet_t))

#define ethhdr(pkt)      ((struct pkt_ethhdr_t *)pkt)
#define ethhdr8021q(pkt) ((struct pkt_ethhdr8021q_t *)pkt)
#define copy_ethproto(o,n)  \
  if (is_8021q(o)) { \
    ((struct pkt_ethhdr8021q_t *)n)->tpid = htons(PKT_ETH_8021Q_TPID); \
    ((struct pkt_ethhdr8021q_t *)n)->pcp_cfi_vid = ((struct pkt_ethhdr8021q_t *)o)->pcp_cfi_vid; \
    ((struct pkt_ethhdr8021q_t *)n)->prot = ((struct pkt_ethhdr8021q_t *)o)->prot; \
  } else { \
    ((struct pkt_ethhdr_t *)n)->prot = ((struct pkt_ethhdr_t *)o)->prot; \
  }

#define ipphdr(pkt)   ((struct pkt_ipphdr_t *)   (((uint8_t*)(pkt)) + sizeofeth(pkt)))
#define iphdr(pkt)    ((struct pkt_iphdr_t *)   (((uint8_t*)(pkt)) + sizeofeth(pkt)))
#define udphdr(pkt)   ((struct pkt_udphdr_t *)  (((uint8_t*)(pkt)) + sizeofip(pkt)))
#define tcphdr(pkt)   ((struct pkt_tcphdr_t *)  (((uint8_t*)(pkt)) + sizeofip(pkt)))
#define dot1xhdr(pkt) ((struct pkt_dot1xhdr_t *)(((uint8_t*)(pkt)) + sizeofeth(pkt)))
#define dhcppkt(pkt)  ((struct dhcp_packet_t *) (((uint8_t*)(pkt)) + sizeofudp(pkt)))
#define arppkt(pkt)   ((struct arp_packet_t *)  (((uint8_t*)(pkt)) + sizeofeth(pkt)))
#define dnspkt(pkt)   ((struct dns_packet_t *)  (((uint8_t*)(pkt)) + sizeofudp(pkt)))
#define eappkt(pkt)   ((struct eap_packet_t *)  (((uint8_t*)(pkt)) + sizeofdot1x(pkt)))

struct eapol_tag_t {
  uint8_t t;
  uint8_t l;
  uint8_t v[EAPOL_TAG_VLEN];
} __attribute__((packed));

int chksum(struct pkt_iphdr_t *iph);
int pkt_shape(uint8_t *packet, size_t *length);

#endif
