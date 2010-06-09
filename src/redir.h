/* 
 * Copyright (C) 2003, 2004, 2005 Mondru AB.
 * Copyright (C) 2007-2010 Coova Technologies, LLC. <support@coova.com>
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


#ifndef _REDIR_H
#define _REDIR_H

#include "dhcp.h"
#include "session.h"
#include "conn.h"

#define REDIR_TERM_INIT       0  /* Nothing done yet */
#define REDIR_TERM_GETREQ     1  /* Before calling redir_getreq */
#define REDIR_TERM_GETSTATE   2  /* Before calling cb_getstate */
#define REDIR_TERM_PROCESS    3  /* Started to process request */
#define REDIR_TERM_RADIUS     4  /* Calling radius */
#define REDIR_TERM_REPLY      5  /* Sending response to client */

#define REDIR_LOGIN           1
#define REDIR_PRELOGIN        2
#define REDIR_LOGOUT          3
#define REDIR_CHALLENGE       4
#define REDIR_ABORT           5
#define REDIR_ABOUT           6
#define REDIR_STATUS          7
#define REDIR_SPLASH          8
#define REDIR_MACREAUTH       9
#define REDIR_WWW            20
#define REDIR_MSDOWNLOAD     25
#define REDIR_ADMIN_CONN     30
#define REDIR_ALREADY        50 /* Reply to /logon while allready logged on */
#define REDIR_FAILED_REJECT  51 /* Reply to /logon if authentication reject */
#define REDIR_FAILED_OTHER   52 /* Reply to /logon if authentication timeout */
#define REDIR_SUCCESS        53 /* Reply to /logon if authentication successful */
#define REDIR_LOGOFF         54 /* Reply to /logff */
#define REDIR_NOTYET         55 /* Reply to /prelogin or any GET request */
#define REDIR_ABORT_ACK      56 /* Reply to /abortlogin */
#define REDIR_ABORT_NAK      57 /* Reply to /abortlogin */

#define REDIR_FMT_DEFAULT     0
#define REDIR_FMT_JSON        1

/* bit masks */
#define REDIR_MSG_OPT_REDIR   1
#define REDIR_MSG_OPT_PARAMS  2
#define REDIR_MSG_NSESSIONID  4

struct redir_conn_t {
  /* 
   *  Parameters from HTTP request 
   */
  unsigned short type;                 /* REDIR_LOGOUT, LOGIN, PRELOGIN, CHALLENGE, MSDOWNLOAD */
  unsigned char format;                /* REDIR_FMT_DEFAULT, REDIR_FMT_JSON */
  char useragent[REDIR_USERAGENTSIZE]; /* Browser User-Agent */
  char httpcookie[REDIR_COOKIESIZE];   /* Browser Cookies */
  char lang[REDIR_LANGSIZE];           /* Query string parameter for language */
  char wwwfile[REDIR_USERNAMESIZE];    /* File request, i.e. PATH_INFO */

  /*
   *  Authentication state information
   */
  int chap; /* 0 if using normal password; 1 if using CHAP */
  int response; /* 0: No radius response yet; 1:Reject; 2:Accept; 3:Timeout */
  uint8_t chappassword[RADIUS_CHAPSIZE];
  uint8_t password[RADIUS_PWSIZE];
  int password_len;
  uint8_t chap_ident;
  
  /* 
   *  RADIUS session parameters 
   */
  struct in_addr nasip;
  uint32_t nasport;
  uint8_t hismac[PKT_ETH_ALEN];/* His MAC address */
  uint8_t ourmac[PKT_ETH_ALEN];/* Our MAC address */
  struct in_addr ourip;        /* IP address to listen to */
  struct in_addr hisip;        /* Client IP address */

#define USING_SSL (1<<0)
  uint8_t flags;

  /*
   *  RADIUS Reply-Message
   */
  char replybuf[RADIUS_ATTR_VLEN+1];
  char *reply;

  /*
   *  Chilli Session parameters and status
   */
  struct session_params s_params;
  struct session_state s_state;
};

/* HTTP request parsing context */
struct redir_httpreq_t {
  char allow_post:1;
  char is_post:1;

  char host[256];
  char path[256];
  char qs[REDIR_USERURLSIZE];

  bstring data_in;

  size_t clen;
};

typedef struct _redir_request {
  int index;

  int uiidx;

  char inuse:1;
  char proxy:1;
  
  bstring url;
  bstring data;
  bstring post;
  bstring wbuf;

  time_t last_active;

  struct sockaddr_in baddr;
  
  struct conn_t conn;
  
#ifdef HAVE_SSL
  openssl_con *sslcon;
#endif
  int socket_fd;

#define REDIR_SOCKET_FD (1<<0)
#define REDIR_CONN_FD   (1<<1)
  char state;

  struct _redir_request *prev, *next;

} redir_request;

struct redir_socket_t {
  int fd[2];
#ifdef HAVE_SSL
  openssl_con *sslcon;
#endif
};

struct redir_t {
  int fd[2];             /* File descriptors */
  int debug;
#if defined(USING_IPC_UNIX)
  int msgfd;
#else
  int msgid;             /* Message Queue */
#endif
  struct in_addr addr;
  int port;
  int uiport;
  
  int starttime;
  
  char *url;
  char *homepage;
  char *secret;
  char *ssid;
  char *vlan;
  char *nasmac;
  char *nasip;
  struct in_addr radiuslisten;

  unsigned char nas_hwaddr[6];   /* Hardware address of NAS */
  
  int (*cb_getstate) (struct redir_t *redir, 
		      struct sockaddr_in *address,
		      struct sockaddr_in *baddress,
		      struct redir_conn_t *conn);

  int (*cb_handle_url) (struct redir_t *redir, 
			struct redir_conn_t *conn,
			struct redir_httpreq_t *httpreq,
			struct redir_socket_t *socket,
			struct sockaddr_in *peer, 
			redir_request *rreq);
};

struct redir_msg_data {
  uint16_t opt;
  struct sockaddr_in address;
  struct sockaddr_in baddress;
  struct redir_state redir;
  struct session_params params;
};

struct redir_msg_t {
  long mtype;
  struct redir_msg_data mdata;
};

#define REDIR_MSG_STATUS_TYPE 1000

int redir_md_param(bstring str, char *secret, char *amp);

int redir_new(struct redir_t **redir, struct in_addr *addr, int port, int uiport);

int redir_free(struct redir_t *redir);

void redir_set(struct redir_t *redir, uint8_t *hwaddr, int debug);

int redir_accept(struct redir_t *redir, int idx);

int redir_setchallenge(struct redir_t *redir, struct in_addr *addr, uint8_t *challenge);

int redir_set_cb_getstate(struct redir_t *redir,
  int (*cb_getstate) (struct redir_t *redir, 
		      struct sockaddr_in *address,
		      struct sockaddr_in *baddress,
		      struct redir_conn_t *conn));

int redir_main(struct redir_t *redir, int infd, int outfd, 
	       struct sockaddr_in *address, 
	       struct sockaddr_in *baddress,
	       int isui, redir_request *rreq);

int redir_json_fmt_redir(struct redir_conn_t *conn, bstring json, 
			 char *userurl, char *redirurl, uint8_t *hismac);

int redir_json_fmt_session(struct redir_conn_t *conn, bstring json, int init);

int redir_chartohex(unsigned char *src, char *dst, size_t len);

int redir_urlencode(bstring src, bstring dst);

int redir_listen(struct redir_t *redir);

pid_t redir_fork(int in, int out);

int redir_ipc(struct redir_t *redir);

#endif	/* !_REDIR_H */
