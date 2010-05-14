/* 
 * Copyright (C) 2003, 2004, 2005 Mondru AB.
 * Copyright (C) 2006 PicoPoint B.V.
 * Copyright (C) 2007-2009 Coova Technologies, LLC. <support@coova.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "pkt.h"
#include "garden.h"

struct options_t {
  int initialized;
  int foreground;
  int debug;
  /* conf */
  uid_t uid;
  gid_t gid;
  int interval;
  char *pidfile;
  char *statedir;
  char *binconfig;
  char *ethers;

  /* TUN parameters */
  struct in_addr net;            /* Network IP address */
  char netc[OPT_IPADDRLEN];

  struct in_addr mask;           /* Network mask */
  char maskc[OPT_IPADDRLEN];

  char * tundev;
  char * dynip;                  /* Dynamic IP address pool */
  char * statip;                 /* Static IP address pool */
  int autostatip;                /* Automatically assign "Static" IP addresses */
  struct in_addr anyipexclude_addr; /* Exclude a given subnet addres from uamanyip */
  struct in_addr anyipexclude_mask; /* Exclude a given subnet mask from uamanyip */
  struct in_addr dns1;           /* Primary DNS server IP address */
  struct in_addr dns2;           /* Secondary DNS server IP address */
  char * domain;                 /* Domain to use for DNS lookups */
  char * ipup;                   /* Script to run after link-up */
  char * ipdown;                 /* Script to run after link-down */
  char * conup;                  /* Script to run after session/connection-up */
  char * condown;                /* Script to run after session/connection-down */
  int txqlen;

  int ringsize;
  int sndbuf;
  int rcvbuf;

  /* Radius parameters */
  struct in_addr radiuslisten;   /* IP address to listen to */
  struct in_addr radiusserver1;  /* IP address of radius server 1 */
  struct in_addr radiusserver2;  /* IP address of radius server 2 */
  uint16_t radiusauthport;       /* Authentication UDP port */
  uint16_t radiusacctport;       /* Accounting UDP port */
  char* radiussecret;            /* Radius shared secret */
  char* radiusnasid;             /* Radius NAS-Identifier */
  char* radiuslocationid;        /* WISPr location ID */
  char* radiuslocationname;      /* WISPr location name */
  char* locationname;            /* Location name */
  int radiusnasporttype;         /* NAS-Port-Type */
  uint16_t coaport;              /* UDP port to listen to */
  int coanoipcheck;              /* Allow disconnect from any IP */
  int logfacility;
  int radiustimeout;             /* Retry timeout in milli seconds */
  int radiusretry;               /* Total amount of retries */
  int radiusretrysec;            /* Amount of retries after we switch to secondary */

  /* Radius proxy parameters */
  int proxyport;                 /* UDP port to listen to */
  struct in_addr proxylisten;    /* IP address to listen to */
  struct in_addr proxyaddr;      /* IP address of proxy client(s) */
  struct in_addr proxymask;      /* IP mask of proxy client(s) */
  char* proxysecret;             /* Proxy shared secret */

  struct in_addr postauth_proxyip;  /* IP address to proxy http to */
  int postauth_proxyport;           /* TCP port to proxy to */

  /* DHCP parameters */
  char *dhcpif;                  /* Interface: eth1 */
  char *routeif;                 /* Interface: eth0 (optional) */
  uint8_t dhcpmac[PKT_ETH_ALEN]; /* Interface MAC address */
  struct in_addr dhcplisten;     /* IP address to listen to */
  int lease;                     /* DHCP lease time */
  int dhcpstart;
  int dhcpend;

  /* XXX */
  uint8_t nexthop[PKT_ETH_ALEN];
#ifdef ENABLE_NETNAT
  struct in_addr natip;
#endif

  uint16_t mtu;                  /* Max MTU */

  struct in_addr dhcprelayip;    /* IP address of DHCP relay header (default to uamlisten) */
  struct in_addr dhcpgwip;       /* IP address of DHCP gateway to relay to */
  uint16_t dhcpgwport;           /* Port of DHCP gateway to relay to */
  uint16_t tcpwin;               /* TCP Window (zero to leave unchanged) */
  uint16_t tcpmss;               /* TCP Maximum Segment Size (zero to leave unchanged) */

  /* UAM parameters */
  struct in_addr uamserver[UAMSERVER_MAX]; /* IP address of UAM server */
  int uamserverlen;              /* Number of UAM servers */
  int uamserverport;             /* Port of UAM server */
  char* uamsecret;               /* Shared secret */
  char* uamurl;                  /* URL of authentication server */
  char* uamaaaurl;               /* URL to use for HTTP based AAA */
  char* uamhomepage;             /* URL of redirection homepage */
  char* wisprlogin;              /* Specific WISPr login url */
  char* usestatusfile;           /* Specific status file to use */
  int uamhomepageport;		 /* Port of redirection homepage */

  struct in_addr uamlisten;      /* IP address of local authentication */
  int uamport;                   /* TCP port to listen to */
  int uamuiport;                 /* TCP port to listen to */
  int max_clients;               /* Max subscriber/clients */

  struct in_addr uamlogout;      /* IP address of HTTP auto-logout */
  struct in_addr uamalias;       /* IP address of UAM Alias */
  char *uamaliasname;            /* Simple hostname (no dots) DNS name for uamalias */
  char *uamhostname;             /* Simple hostname (no dots) DNS name for uamlisten */

  /* booleans */
  uint8_t allowdyn:1;               /* Allow dynamic address allocation */
  uint8_t allowstat:1;              /* Allow static address allocation */
  uint8_t dhcpusemac:1;             /* Use given MAC or interface default */
  uint8_t noc2c:1;
  uint8_t framedservice:1;
  uint8_t usetap:1;
  uint8_t eapolenable:1;            /* Use eapol */
  uint8_t swapoctets:1;
  uint8_t chillixml:1;
  uint8_t pap_always_ok:1;          /* Obsolete */
  uint8_t mschapv2:1;               /* Use and support MSCHAPv2 */
  uint8_t uamanydns:1;              /* Allow any dns server */
  uint8_t uamanyip:1;               /* Allow any ip address */
  uint8_t uamnatanyip:1;            /* Provide NAT for Any IP clients */
  uint8_t dnsparanoia:1;            /* Filter DNS for questionable content (dns tunnels) */
  uint8_t no_uamwispr:1;            /* Do not have ChilliSpot return WISPr blocks */
  uint8_t acct_update:1;            /* Allow for session parameter updates in accounting response */
  uint8_t wpaguests:1;              /* Allow WPS "Guest" access */
  uint8_t openidauth:1;             /* Allow OpenID authentication */
  uint8_t macauth:1;                /* Use MAC authentication */
  uint8_t macreauth:1;              /* Use MAC re-authentication on /prelogin */
  uint8_t macauthdeny:1;            /* Deny any access to those given Access-Reject */
  uint8_t macallowlocal:1;          /* Do not use RADIUS for authenticating the macallowed */
  uint8_t radiusoriginalurl:1;      /* Send ChilliSpot-OriginalURL in AccessRequest */
  uint8_t dhcpradius:1;             /* Send certain DHCP options in RADIUS attributes */
  uint8_t has_nexthop:1;            /* Has a nexthop entry */
  uint8_t ieee8021q:1;              /* check for VLAN tags */
  uint8_t dhcp_broadcast:1;         /* always broadcast DHCP (when not relaying) */
  uint8_t seskeepalive:1;           /* Keep sessions alive during shutdown */
  uint8_t strictmacauth:1;          /* Be strict about DHCP macauth (don't reply DHCP until we get RADIUS) */
  uint8_t dhcpmacset:1;             /* Set the dhcpif interface with the dhcpmac */
  uint8_t uamallowpost:1;           /* Set to true if the UAMPORT is allowed to access a POST */
  uint8_t redirssl:1;               /* Enable redirection of SSL/HTTPS port (requires SSL support) */
  uint8_t uamuissl:1;               /* Enable SSL/HTTPS on uamuiport (requires SSL support) */
  uint8_t domaindnslocal:1;         /* Wildcard option to consider all hostnames *.domain local */
  uint8_t radsec:1;                 /* Use RadSec tunneling */
  uint8_t proxymacaccept:1;         /* Auto-accept non-EAP requests on proxy port */
  /* */

  pass_through pass_throughs[MAX_PASS_THROUGHS];
  size_t num_pass_throughs;

#ifdef ENABLE_CHILLIREDIR
  regex_pass_through regex_pass_throughs[MAX_REGEX_PASS_THROUGHS];
  size_t regex_num_pass_throughs;
#endif

  char* uamdomains[MAX_UAM_DOMAINS];

  /* MAC Authentication */
  uint8_t macok[MACOK_MAX][PKT_ETH_ALEN]; /* Allowed MACs */
  int macoklen;                   /* Number of MAC addresses */
  char* macsuffix;               /* Suffix to add to MAC address */
  char* macpasswd;               /* Password to use for MAC authentication */  

  uint64_t defsessiontimeout;
  uint64_t defbandwidthmaxdown;
  uint64_t defbandwidthmaxup;
  uint32_t defidletimeout;
  uint16_t definteriminterval;

  uint32_t challengetimeout;
  uint32_t challengetimeout2;

#ifdef ENABLE_PROXYVSA
#define PROXYVSA_ATTR_CNT 4
  struct {
    uint32_t attr_vsa;
    uint8_t attr;
  } proxy_loc[PROXYVSA_ATTR_CNT];
#endif

#ifdef HAVE_SSL
  char *sslkeyfile;
  char *sslkeypass;
  char *sslcertfile;
  char *sslcafile;
#endif

  /* local content */
  char *wwwdir;
  char *wwwbin;
  char *uamui;
  char *localusers;

  /* Admin RADIUS Authentication & Configuration */
  char *adminuser;
  char *adminpasswd;
  char *adminupdatefile;
  char *rtmonfile;

  /* Location-awareness */
  char *ssid;
  char *vlan;
  char *nasmac;
  char *nasip;

  /* Command-Socket */
  char *cmdsocket;

#ifdef ENABLE_LEAKYBUCKET
  uint32_t bwbucketupsize;
  uint32_t bwbucketdnsize;
  uint32_t bwbucketminsize;
#endif

#ifdef USING_IPC_UNIX
  char *unixipc;
#endif

#ifdef HAVE_NETFILTER_COOVA
  char *kname;
#endif

  char * _data; /* actual data buffer for loaded options */
};

int options_mkdir(char *path);
int options_fromfd(int fd, bstring bt);
int options_binload(char *file);
int option_aton(struct in_addr *addr, struct in_addr *mask, char *pool, int number);
int process_options(int argc, char **argv, int minimal);
void reprocess_options(int argc, char **argv);
int reload_options(int argc, char **argv);
int options_save(char *file, bstring bt);
void options_init();
void options_destroy();

#ifndef MAIN_FILE /* all main() files must implement _options */
extern struct options_t _options;
#endif


#endif /*_OPTIONS_H */
