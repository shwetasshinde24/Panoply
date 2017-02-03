/* FreeTDS - Library of routines accessing Sybase and Microsoft databases
 * Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005  Brian Bruns
 * Copyright (C) 2010, 2011  Frediano Ziglio
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _tds_h_
#define _tds_h_

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif




#include <freetds/version.h>
#include "enclave_net_wrapper.h"

#include <freetds/sysdep_private.h>
#include <freetds/thread.h>
#include <freetds/bool.h>

#include <freetds/pushvis.h>

#ifdef __cplusplus
extern "C"
{
#if 0
}
#endif
#endif

#ifndef STDIO_WRAPPER
#define STDIO_WRAPPER
# define SGX_STDIN 1
# define SGX_STDOUT 2
# define SGX_STDERR 3
# define FILE_IS_NULL(FILE) FILE<=0
typedef int SGX_WRAPPER_FILE;
#endif

#define strcpy(A,B) strncpy(A,B,strlen(B)+1)
#define strcat(A,B) strncat(A,B,strlen(B)+1)




#include <freetds/proto.h>



/**
 * The following little table is indexed by precision and will
 * tell us the number of bytes required to store the specified
 * precision.
 */
extern const int tds_numeric_bytes_per_prec[];


#define TDS_NO_MORE_RESULTS  ((TDSRET)1)
#define TDS_SUCCESS          ((TDSRET)0)
#define TDS_FAIL             ((TDSRET)-1)
#define TDS_CANCELLED        ((TDSRET)-2)
#define TDS_FAILED(rc) ((rc)<0)
#define TDS_SUCCEED(rc) ((rc)>=0)

#define TDS_INT_CONTINUE 1
#define TDS_INT_CANCEL 2
#define TDS_INT_TIMEOUT 3


#define TDS_NO_COUNT         -1

#define TDS_ROW_RESULT        4040
#define TDS_PARAM_RESULT      4042
#define TDS_STATUS_RESULT     4043
#define TDS_MSG_RESULT        4044
#define TDS_COMPUTE_RESULT    4045
#define TDS_CMD_DONE          4046
#define TDS_CMD_SUCCEED       4047
#define TDS_CMD_FAIL          4048
#define TDS_ROWFMT_RESULT     4049
#define TDS_COMPUTEFMT_RESULT 4050
#define TDS_DESCRIBE_RESULT   4051
#define TDS_DONE_RESULT       4052
#define TDS_DONEPROC_RESULT   4053
#define TDS_DONEINPROC_RESULT 4054
#define TDS_OTHERS_RESULT     4055

/* field related to connection */
struct tds_connection
{
	TDS_USMALLINT tds_version;
	TDS_UINT product_version;	/**< version of product (Sybase/MS and full version) */
	char *product_name;

	TDS_SYS_SOCKET s;		/**< tcp socket, INVALID_SOCKET if not connected */
	TDSPOLLWAKEUP wakeup;
	const TDSCONTEXT *tds_ctx;

	/** environment is shared between all sessions */
	TDSENV env;

	/**
	 * linked list of cursors allocated for this connection
	 * contains only cursors allocated on the server
	 */
	TDSCURSOR *cursors;
	/**
	 * list of dynamic allocated for this connection
	 * contains only dynamic allocated on the server
	 */
	TDSDYNAMIC *dyns;

	int char_conv_count;
	TDSICONV **char_convs;

	TDS_UCHAR collation[5];
	TDS_UCHAR tds72_transaction[8];

	TDS_CAPABILITIES capabilities;
	unsigned int emul_little_endian:1;
	unsigned int use_iconv:1;
	unsigned int tds71rev1:1;
	unsigned int pending_close:1;	/**< true is connection has pending closing (cursors or dynamic) */
#if ENABLE_ODBC_MARS
	unsigned int mars:1;

	TDSSOCKET *in_net_tds;
	TDSPACKET *packets;
	TDSPACKET *recv_packet;
	TDSPACKET *send_packets;
	unsigned send_pos, recv_pos;

	tds_mutex list_mtx;
#define BUSY_SOCKET ((TDSSOCKET*)(TDS_UINTPTR)1)
#define TDSSOCKET_VALID(tds) (((TDS_UINTPTR)(tds)) > 1)
	struct tds_socket **sessions;
	unsigned num_sessions;
	unsigned num_cached_packets;
	TDSPACKET *packet_cache;
#endif

	int spid;
	int client_spid;

	void *tls_session;
#if defined(HAVE_GNUTLS)
	void *tls_credentials;
#elif defined(HAVE_OPENSSL)
	void *tls_ctx;
#else
	void *tls_dummy;
#endif
	TDSAUTHENTICATION *authentication;
	char *server;
};
/**
 * Information for a server connection
 */
struct tds_socket
{
#if ENABLE_ODBC_MARS
	TDSCONNECTION *conn;
#else
	TDSCONNECTION conn[1];
#endif

	/** Input buffer.
	 * Points to receiving packet buffer.
	 * As input buffer contains just the raw packet actually this pointer
	 * is the address of recv_packet->buf.
	 */
	unsigned char *in_buf;

	/** Output buffer.
	 * Points to sending packet buffer.
	 * Output buffer can contain additional data before the raw TDS packet
	 * so this buffer can point some bytes after send_packet->buf.
	 */
	unsigned char *out_buf;

	/** Maximum size of packet pointed by out_buf.
	 * The buffer is actually a bit larger to make possible to do some
	 * optimizations (at least TDS_ADDITIONAL_SPACE bytes).
	 */
	unsigned int out_buf_max;
	unsigned in_pos;		/**< current position in in_buf */
	unsigned out_pos;		/**< current position in out_buf */
	unsigned in_len;		/**< input buffer length */
	unsigned char in_flag;		/**< input buffer type */
	unsigned char out_flag;		/**< output buffer type */

	void *parent;

#if ENABLE_ODBC_MARS
	short sid;
	tds_condition packet_cond;
	TDS_UINT recv_seq;
	TDS_UINT send_seq;
	TDS_UINT recv_wnd;
	TDS_UINT send_wnd;
#endif
	/* packet we received */
	TDSPACKET *recv_packet;
	/** packet we are preparing to send */
	TDSPACKET *send_packet;

	/**
	 * Current query information. 
	 * Contains information in process, both normal and compute results.
	 * This pointer shouldn't be freed; it's just an alias to another structure.
	 */
	TDSRESULTINFO *current_results;
	TDSRESULTINFO *res_info;
	TDS_UINT num_comp_info;
	TDSCOMPUTEINFO **comp_info;
	TDSPARAMINFO *param_info;
	TDSCURSOR *cur_cursor;		/**< cursor in use */
	TDS_TINYINT bulk_query;		/**< true is query sent was a bulk query so we need to switch state to QUERYING */
	TDS_TINYINT has_status; 	/**< true is ret_status is valid */
	TDS_INT ret_status;     	/**< return status from store procedure */
	TDS_STATE state;
	volatile 
	unsigned char in_cancel; 	/**< indicate we are waiting a cancel reply; discard tokens till acknowledge; 
	1 mean we have to send cancel packet, 2 already sent. */

	TDS_INT8 rows_affected;		/**< rows updated/deleted/inserted/selected, TDS_NO_COUNT if not valid */
	TDS_INT query_timeout;

	TDSDYNAMIC *cur_dyn;		/**< dynamic structure in use */

	TDSLOGIN *login;	/**< config for login stuff. After login this field is NULL */

	void (*env_chg_func) (TDSSOCKET * tds, int type, char *oldval, char *newval);
	TDS_OPERATION current_op;

	int option_value;
	tds_mutex wire_mtx;
};


enum tds_token_results
{
	TDS_TOKEN_RES_OTHERS,
	TDS_TOKEN_RES_ROWFMT,
	TDS_TOKEN_RES_COMPUTEFMT,
	TDS_TOKEN_RES_PARAMFMT,
	TDS_TOKEN_RES_DONE,
	TDS_TOKEN_RES_ROW,
	TDS_TOKEN_RES_COMPUTE,
	TDS_TOKEN_RES_PROC,
	TDS_TOKEN_RES_MSG,
	TDS_TOKEN_RES_ENV,
};

#define TDS_TOKEN_FLAG(flag) TDS_RETURN_##flag = (1 << (TDS_TOKEN_RES_##flag*2)), TDS_STOPAT_##flag = (2 << (TDS_TOKEN_RES_##flag*2))

enum tds_token_flags
{
	TDS_HANDLE_ALL = 0,
	TDS_TOKEN_FLAG(OTHERS),
	TDS_TOKEN_FLAG(ROWFMT),
	TDS_TOKEN_FLAG(COMPUTEFMT),
	TDS_TOKEN_FLAG(PARAMFMT),
	TDS_TOKEN_FLAG(DONE),
	TDS_TOKEN_FLAG(ROW),
	TDS_TOKEN_FLAG(COMPUTE),
	TDS_TOKEN_FLAG(PROC),
	TDS_TOKEN_FLAG(MSG),
	TDS_TOKEN_FLAG(ENV),
	TDS_TOKEN_RESULTS = TDS_RETURN_ROWFMT|TDS_RETURN_COMPUTEFMT|TDS_RETURN_DONE|TDS_STOPAT_ROW|TDS_STOPAT_COMPUTE|TDS_RETURN_PROC,
	TDS_TOKEN_TRAILING = TDS_STOPAT_ROWFMT|TDS_STOPAT_COMPUTEFMT|TDS_STOPAT_ROW|TDS_STOPAT_COMPUTE|TDS_STOPAT_MSG|TDS_STOPAT_OTHERS
};

/**
 * Flags returned in TDS_DONE token
 */
enum tds_end
{
	  TDS_DONE_FINAL 	= 0x00	/**< final result set, command completed successfully. */
	, TDS_DONE_MORE_RESULTS = 0x01	/**< more results follow */
	, TDS_DONE_ERROR 	= 0x02	/**< error occurred */
	, TDS_DONE_INXACT 	= 0x04	/**< transaction in progress */
	, TDS_DONE_PROC 	= 0x08	/**< results are from a stored procedure */
	, TDS_DONE_COUNT 	= 0x10	/**< count field in packet is valid */
	, TDS_DONE_CANCELLED 	= 0x20	/**< acknowledging an attention command (usually a cancel) */
	, TDS_DONE_EVENT 	= 0x40	/*   part of an event notification. */
	, TDS_DONE_SRVERROR 	= 0x100	/**< SQL server server error */
	
	/* after the above flags, a TDS_DONE packet has a field describing the state of the transaction */
	, TDS_DONE_NO_TRAN 	= 0	/* No transaction in effect */
	, TDS_DONE_TRAN_SUCCEED = 1	/* Transaction completed successfully */
	, TDS_DONE_TRAN_PROGRESS= 2	/* Transaction in progress */
	, TDS_DONE_STMT_ABORT 	= 3	/* A statement aborted */
	, TDS_DONE_TRAN_ABORT 	= 4	/* Transaction aborted */
};


/*
 * TDSERRNO is emitted by libtds to the client library's error handler
 * (which may in turn call the client's error handler).
 * These match the db-lib msgno, because the same values have the same meaning
 * in db-lib and ODBC.  ct-lib maps them to ct-lib numbers (todo). 
 */
typedef enum {	TDSEOK    = TDS_SUCCESS, 
		TDSEVERDOWN    =  100,
		TDSEICONVIU    = 2400, 
		TDSEICONVAVAIL = 2401, 
		TDSEICONVO     = 2402, 
		TDSEICONVI     = 2403, 
		TDSEICONV2BIG  = 2404,
		TDSEPORTINSTANCE	= 2500,
		TDSESYNC = 20001, 
		TDSEFCON = 20002, 
		TDSETIME = 20003, 
		TDSEREAD = 20004, 
		TDSEWRIT = 20006, 
		TDSESOCK = 20008, 
		TDSECONN = 20009, 
		TDSEMEM  = 20010,
		TDSEINTF = 20012,	/* Server name not found in interface file */
		TDSEUHST = 20013,	/* Unknown host machine name. */
		TDSEPWD  = 20014, 
		TDSESEOF = 20017, 
		TDSERPND = 20019, 
		TDSEBTOK = 20020, 
		TDSEOOB  = 20022, 
		TDSECLOS = 20056,
		TDSEUSCT = 20058, 
		TDSEUTDS = 20146, 
		TDSEEUNR = 20185, 
		TDSECAP  = 20203, 
		TDSENEG  = 20210, 
		TDSEUMSG = 20212, 
		TDSECAPTYP  = 20213, 
		TDSECONF = 20214,
		TDSEBPROBADTYP = 20250,
		TDSECLOSEIN = 20292 
} TDSERRNO;


enum {
	TDS_CUR_ISTAT_UNUSED    = 0x00,
	TDS_CUR_ISTAT_DECLARED  = 0x01,
	TDS_CUR_ISTAT_OPEN      = 0x02,
	TDS_CUR_ISTAT_CLOSED    = 0x04,
	TDS_CUR_ISTAT_RDONLY    = 0x08,
	TDS_CUR_ISTAT_UPDATABLE = 0x10,
	TDS_CUR_ISTAT_ROWCNT    = 0x20,
	TDS_CUR_ISTAT_DEALLOC   = 0x40
};

/* string types */
#define TDS_NULLTERM -9


typedef union tds_option_arg
{
	TDS_TINYINT ti;
	TDS_INT i;
	TDS_CHAR *c;
} TDS_OPTION_ARG;


typedef enum tds_encryption_level {
	TDS_ENCRYPTION_OFF, TDS_ENCRYPTION_REQUEST, TDS_ENCRYPTION_REQUIRE
} TDS_ENCRYPTION_LEVEL;

#define TDS_ZERO_FREE(x) do {free((x)); (x) = NULL;} while(0)
#define TDS_VECTOR_SIZE(x) (sizeof(x)/sizeof(x[0]))
#ifdef offsetof
#define TDS_OFFSET(str, field) offsetof(str, field)
#else
#define TDS_OFFSET(str, field) (((char*)&((str*)0)->field)-((char*)0))
#endif

#if defined(__GNUC__) && __GNUC__ >= 3
# define TDS_LIKELY(x)	__builtin_expect(!!(x), 1)
# define TDS_UNLIKELY(x)	__builtin_expect(!!(x), 0)
#else
# define TDS_LIKELY(x)	(x)
# define TDS_UNLIKELY(x)	(x)
#endif

#if ENABLE_EXTRA_CHECKS
# if defined(__GNUC__) && __GNUC__ >= 2
# define TDS_COMPILE_CHECK(name,check) \
    extern int name[(check)?1:-1] __attribute__ ((unused))
# else
# define TDS_COMPILE_CHECK(name,check) \
    extern int name[(check)?1:-1]
# endif
# define TDS_EXTRA_CHECK(stmt) stmt
#else
# define TDS_COMPILE_CHECK(name,check) \
    extern int disabled_check_##name
# define TDS_EXTRA_CHECK(stmt)
#endif

#if ENABLE_EXTRA_CHECKS && defined(__GNUC__) && __GNUC__ >= 4
#define TDS_WUR __attribute__ ((__warn_unused_result__))
#else
#define TDS_WUR
#endif

/*
 * TODO use system macros for optimization
 * See mcrypt for reference and linux kernel source for optimization
 * check if unaligned access and use fast write/read when implemented
 */
#define TDS_BYTE_SWAP16(value)                 \
         (((((unsigned short)value)<<8) & 0xFF00)   | \
          ((((unsigned short)value)>>8) & 0x00FF))

#define TDS_BYTE_SWAP32(value)                     \
         (((((unsigned long)value)<<24) & 0xFF000000)  | \
          ((((unsigned long)value)<< 8) & 0x00FF0000)  | \
          ((((unsigned long)value)>> 8) & 0x0000FF00)  | \
          ((((unsigned long)value)>>24) & 0x000000FF))

#define is_end_token(x) (x==TDS_DONE_TOKEN    || \
			x==TDS_DONEPROC_TOKEN    || \
			x==TDS_DONEINPROC_TOKEN)

enum {
	TDS_TYPEFLAG_INVALID  = 0,
	TDS_TYPEFLAG_NULLABLE = 1,
	TDS_TYPEFLAG_FIXED    = 2,
	TDS_TYPEFLAG_VARIABLE = 4,
	TDS_TYPEFLAG_COLLATE  = 8,
	TDS_TYPEFLAG_ASCII    = 16,
	TDS_TYPEFLAG_UNICODE  = 32,
	TDS_TYPEFLAG_NUMERIC  = 64,
	TDS_TYPEFLAG_DATETIME = 128,
};

extern const unsigned char tds_type_flags_ms[256];
#if 0
extern const unsigned char tds_type_flags_syb[256];
extern const char *const tds_type_names[256];
#endif

#define is_fixed_type(x)      ((tds_type_flags_ms[x] & TDS_TYPEFLAG_FIXED)    != 0)
#define is_nullable_type(x)   ((tds_type_flags_ms[x] & TDS_TYPEFLAG_NULLABLE) != 0)
#define is_variable_type(x)   ((tds_type_flags_ms[x] & TDS_TYPEFLAG_VARIABLE) != 0)


#define is_blob_type(x)       ((x)==SYBTEXT || (x)==SYBIMAGE || (x)==SYBNTEXT)
#define is_blob_col(x)        ((x)->column_varint_size > 2)
/* large type means it has a two byte size field */
/* define is_large_type(x) (x>128) */
#define is_numeric_type(x)    ((x)==SYBNUMERIC || (x)==SYBDECIMAL)
/** return true if type is a datetime (but not date or time) */
#define is_datetime_type(x)   ((tds_type_flags_ms[x] & TDS_TYPEFLAG_DATETIME) != 0)
#define is_unicode_type(x)    ((tds_type_flags_ms[x] & TDS_TYPEFLAG_UNICODE) != 0)
#define is_collate_type(x)    ((tds_type_flags_ms[x] & TDS_TYPEFLAG_COLLATE) != 0)
#define is_ascii_type(x)      ((tds_type_flags_ms[x] & TDS_TYPEFLAG_ASCII) != 0)
#define is_char_type(x)       ((tds_type_flags_ms[x] & (TDS_TYPEFLAG_ASCII|TDS_TYPEFLAG_UNICODE)) != 0)
#define is_similar_type(x, y) (is_char_type(x) && is_char_type(y))





#define TDS_DBG_LOGIN   __FILE__, ((__LINE__ << 4) | 11)
#define TDS_DBG_HEADER  __FILE__, ((__LINE__ << 4) | 10)
#define TDS_DBG_FUNC    __FILE__, ((__LINE__ << 4) |  7)
#define TDS_DBG_INFO2   __FILE__, ((__LINE__ << 4) |  6)
#define TDS_DBG_INFO1   __FILE__, ((__LINE__ << 4) |  5)
#define TDS_DBG_NETWORK __FILE__, ((__LINE__ << 4) |  4)
#define TDS_DBG_WARN    __FILE__, ((__LINE__ << 4) |  3)
#define TDS_DBG_ERROR   __FILE__, ((__LINE__ << 4) |  2)
#define TDS_DBG_SEVERE  __FILE__, ((__LINE__ << 4) |  1)

#define TDS_DBGFLAG_FUNC    0x80
#define TDS_DBGFLAG_INFO2   0x40
#define TDS_DBGFLAG_INFO1   0x20
#define TDS_DBGFLAG_NETWORK 0x10
#define TDS_DBGFLAG_WARN    0x08
#define TDS_DBGFLAG_ERROR   0x04
#define TDS_DBGFLAG_SEVERE  0x02
#define TDS_DBGFLAG_ALL     0xfff
#define TDS_DBGFLAG_LOGIN   0x0800
#define TDS_DBGFLAG_HEADER  0x0400
#define TDS_DBGFLAG_PID     0x1000
#define TDS_DBGFLAG_TIME    0x2000
#define TDS_DBGFLAG_SOURCE  0x4000
#define TDS_DBGFLAG_THREAD  0x8000

#if 0
/**
 * An attempt at better logging.
 * Using these bitmapped values, various logging features can be turned on and off.
 * It can be especially helpful to turn packet data on/off for security reasons.
 */
enum TDS_DBG_LOG_STATE
{
	  TDS_DBG_LOGIN =  (1 << 0)	/**< for diagnosing login problems;                                       
				 	   otherwise the username/password information is suppressed. */
	, TDS_DBG_API =    (1 << 1)	/**< Log calls to client libraries */
	, TDS_DBG_ASYNC =  (1 << 2)	/**< Log asynchronous function starts or completes. */
	, TDS_DBG_DIAG =   (1 << 3)	/**< Log client- and server-generated messages */
	, TDS_DBG_error =  (1 << 4)
	/* TODO:  ^^^^^ make upper case when old #defines (above) are removed */
	/* Log FreeTDS runtime/logic error occurs. */
	, TDS_DBG_PACKET = (1 << 5)	/**< Log hex dump of packets to/from the server. */
	, TDS_DBG_LIBTDS = (1 << 6)	/**< Log calls to (and in) libtds */
	, TDS_DBG_CONFIG = (1 << 7)	/**< replaces TDSDUMPCONFIG */
	, TDS_DBG_DEFAULT = 0xFE	/**< all above except login packets */
};
#endif

#include <freetds/tds_struct.h>

typedef int (*err_handler_t) (const TDSCONTEXT *, TDSSOCKET *, TDSMESSAGE *);



#define tds_get_ctx(tds) ((tds)->conn->tds_ctx)
#define tds_set_ctx(tds, val) do { ((tds)->conn->tds_ctx) = (val); } while(0)
#define tds_get_parent(tds) ((tds)->parent)
#define tds_set_parent(tds, val) do { ((tds)->parent) = (val); } while(0)
#define tds_get_s(tds) ((tds)->conn->s)
#define tds_set_s(tds, val) do { ((tds)->conn->s) = (val); } while(0)


/* config.c */
const TDS_COMPILETIME_SETTINGS *tds_get_compiletime_settings(void);
typedef void (*TDSCONFPARSE) (const char *option, const char *value, void *param);
// 
int tds_read_conf_section(SGX_WRAPPER_FILE in, const char *section, TDSCONFPARSE tds_conf_parse, void *parse_param);
int tds_read_conf_file(TDSLOGIN * login, const char *server);
void tds_parse_conf_section(const char *option, const char *value, void *param);
TDSLOGIN *tds_read_config_info(TDSSOCKET * tds, TDSLOGIN * login, TDSLOCALE * locale);
void tds_fix_login(TDSLOGIN* login);
TDS_USMALLINT * tds_config_verstr(const char *tdsver, TDSLOGIN* login);
struct addrinfo *tds_lookup_host(const char *servername);
TDSRET tds_lookup_host_set(const char *servername, struct addrinfo **addr);
//extern const char *tds_addrinfo2str(struct addrinfo *addr, char *name, int namemax);

TDSRET tds_set_interfaces_file_loc(const char *interfloc);
extern const char STD_DATETIME_FMT[];
int tds_parse_boolean(const char *value, int default_value);
int tds_config_boolean(const char *option, const char *value, TDSLOGIN * login);

TDSLOCALE *tds_get_locale(void);
TDSRET tds_alloc_row(TDSRESULTINFO * res_info);
TDSRET tds_alloc_compute_row(TDSCOMPUTEINFO * res_info);
BCPCOLDATA * tds_alloc_bcp_column_data(unsigned int column_size);
TDSDYNAMIC *tds_lookup_dynamic(TDSCONNECTION * conn, const char *id);
/*@observer@*/ const char *tds_prtype(int token);
int tds_get_varint_size(TDSCONNECTION * conn, int datatype);
int tds_get_cardinal_type(int datatype, int usertype);


/* iconv.c */
TDSRET tds_iconv_open(TDSCONNECTION * conn, const char *charset, int use_utf16);
void tds_iconv_close(TDSCONNECTION * conn);
void tds_srv_charset_changed(TDSCONNECTION * conn, const char *charset);
void tds7_srv_charset_changed(TDSCONNECTION * conn, int sql_collate, int lcid);
int tds_iconv_alloc(TDSCONNECTION * conn);
void tds_iconv_free(TDSCONNECTION * conn);
TDSICONV *tds_iconv_from_collate(TDSCONNECTION * conn, TDS_UCHAR collate[5]);


/* mem.c */
void tds_free_socket(TDSSOCKET * tds);
void tds_free_all_results(TDSSOCKET * tds);
void tds_free_results(TDSRESULTINFO * res_info);
void tds_free_param_results(TDSPARAMINFO * param_info);
void tds_free_param_result(TDSPARAMINFO * param_info);
void tds_free_msg(TDSMESSAGE * message);
void tds_cursor_deallocated(TDSCONNECTION *conn, TDSCURSOR *cursor);
void tds_release_cursor(TDSCURSOR **pcursor);
void tds_free_bcp_column_data(BCPCOLDATA * coldata);
TDSRESULTINFO *tds_alloc_results(TDS_USMALLINT num_cols);
TDSCOMPUTEINFO **tds_alloc_compute_results(TDSSOCKET * tds, TDS_USMALLINT num_cols, TDS_USMALLINT by_cols);
TDSCONTEXT *tds_alloc_context(void * parent);
void tds_free_context(TDSCONTEXT * locale);
TDSPARAMINFO *tds_alloc_param_result(TDSPARAMINFO * old_param);
void tds_free_input_params(TDSDYNAMIC * dyn);
void tds_release_dynamic(TDSDYNAMIC ** dyn);
static inline
void tds_release_cur_dyn(TDSSOCKET * tds)
{
	tds_release_dynamic(&tds->cur_dyn);
}
void tds_dynamic_deallocated(TDSCONNECTION *conn, TDSDYNAMIC *dyn);
void tds_set_cur_dyn(TDSSOCKET *tds, TDSDYNAMIC *dyn);
TDSSOCKET *tds_realloc_socket(TDSSOCKET * tds, size_t bufsize);
char *tds_alloc_client_sqlstate(int msgno);
char *tds_alloc_lookup_sqlstate(TDSSOCKET * tds, int msgno);
TDSLOGIN *tds_alloc_login(int use_environment);
TDSDYNAMIC *tds_alloc_dynamic(TDSCONNECTION * conn, const char *id);
void tds_free_login(TDSLOGIN * login);
TDSLOGIN *tds_init_login(TDSLOGIN * login, TDSLOCALE * locale);
TDSLOCALE *tds_alloc_locale(void);
void *tds_alloc_param_data(TDSCOLUMN * curparam);
void tds_free_locale(TDSLOCALE * locale);
TDSCURSOR * tds_alloc_cursor(TDSSOCKET * tds, const char *name, TDS_INT namelen, const char *query, TDS_INT querylen);
void tds_free_row(TDSRESULTINFO * res_info, unsigned char *row);
TDSSOCKET *tds_alloc_socket(TDSCONTEXT * context, unsigned int bufsize);
TDSSOCKET *tds_alloc_additional_socket(TDSCONNECTION *conn);
void tds_set_current_results(TDSSOCKET *tds, TDSRESULTINFO *info);
void tds_detach_results(TDSRESULTINFO *info);
void * tds_realloc(void **pp, size_t new_size);
#define TDS_RESIZE(p, n_elem) \
	tds_realloc((void **) &(p), sizeof(*(p)) * (size_t) (n_elem))
#define tds_new(type, n) ((type *) malloc(sizeof(type) * (n)))
#define tds_new0(type, n) ((type *) calloc(n, sizeof(type)))

TDSPACKET *tds_alloc_packet(void *buf, unsigned len);
TDSPACKET *tds_realloc_packet(TDSPACKET *packet, unsigned len);
void tds_free_packets(TDSPACKET *packet);
TDSBCPINFO *tds_alloc_bcpinfo(void);
void tds_free_bcpinfo(TDSBCPINFO *bcpinfo);
void tds_deinit_bcpinfo(TDSBCPINFO *bcpinfo);


/* login.c */
void tds_set_packet(TDSLOGIN * tds_login, int packet_size);
void tds_set_port(TDSLOGIN * tds_login, int port);
bool tds_set_passwd(TDSLOGIN * tds_login, const char *password) TDS_WUR;
void tds_set_bulk(TDSLOGIN * tds_login, TDS_TINYINT enabled);
bool tds_set_user(TDSLOGIN * tds_login, const char *username) TDS_WUR;
bool tds_set_app(TDSLOGIN * tds_login, const char *application) TDS_WUR;
bool tds_set_host(TDSLOGIN * tds_login, const char *hostname) TDS_WUR;
bool tds_set_library(TDSLOGIN * tds_login, const char *library) TDS_WUR;
bool tds_set_server(TDSLOGIN * tds_login, const char *server) TDS_WUR;
bool tds_set_client_charset(TDSLOGIN * tds_login, const char *charset) TDS_WUR;
bool tds_set_language(TDSLOGIN * tds_login, const char *language) TDS_WUR;
void tds_set_version(TDSLOGIN * tds_login, TDS_TINYINT major_ver, TDS_TINYINT minor_ver);
int tds_connect_and_login(TDSSOCKET * tds, TDSLOGIN * login);


/* query.c */
void tds_start_query(TDSSOCKET *tds, unsigned char packet_type);

TDSRET tds_submit_query(TDSSOCKET * tds, const char *query);
TDSRET tds_submit_query_params(TDSSOCKET * tds, const char *query, TDSPARAMINFO * params, TDSHEADERS * head);
TDSRET tds_submit_queryf(TDSSOCKET * tds, const char *queryf, ...);
TDSRET tds_submit_prepare(TDSSOCKET * tds, const char *query, const char *id, TDSDYNAMIC ** dyn_out, TDSPARAMINFO * params);
TDSRET tds_submit_execdirect(TDSSOCKET * tds, const char *query, TDSPARAMINFO * params, TDSHEADERS * head);
TDSRET tds71_submit_prepexec(TDSSOCKET * tds, const char *query, const char *id, TDSDYNAMIC ** dyn_out, TDSPARAMINFO * params);
TDSRET tds_submit_execute(TDSSOCKET * tds, TDSDYNAMIC * dyn);
TDSRET tds_send_cancel(TDSSOCKET * tds);
const char *tds_next_placeholder(const char *start);
int tds_count_placeholders(const char *query);
int tds_needs_unprepare(TDSCONNECTION * conn, TDSDYNAMIC * dyn);
TDSRET tds_deferred_unprepare(TDSCONNECTION * conn, TDSDYNAMIC * dyn);
TDSRET tds_submit_unprepare(TDSSOCKET * tds, TDSDYNAMIC * dyn);
TDSRET tds_submit_rpc(TDSSOCKET * tds, const char *rpc_name, TDSPARAMINFO * params, TDSHEADERS * head);
TDSRET tds_submit_optioncmd(TDSSOCKET * tds, TDS_OPTION_CMD command, TDS_OPTION option, TDS_OPTION_ARG *param, TDS_INT param_size);
TDSRET tds_submit_begin_tran(TDSSOCKET *tds);
TDSRET tds_submit_rollback(TDSSOCKET *tds, int cont);
TDSRET tds_submit_commit(TDSSOCKET *tds, int cont);
TDSRET tds_disconnect(TDSSOCKET * tds);
size_t tds_quote_id(TDSSOCKET * tds, char *buffer, const char *id, int idlen);
size_t tds_quote_string(TDSSOCKET * tds, char *buffer, const char *str, int len);
const char *tds_skip_comment(const char *s);
const char *tds_skip_quoted(const char *s);
size_t tds_fix_column_size(TDSSOCKET * tds, TDSCOLUMN * curcol);
const char *tds_convert_string(TDSSOCKET * tds, TDSICONV * char_conv, const char *s, int len, size_t *out_len);
void tds_convert_string_free(const char *original, const char *converted);
#if !ENABLE_EXTRA_CHECKS
#define tds_convert_string_free(original, converted) \
	do { if (original != converted) free((char*) converted); } while(0)
#endif
TDSRET tds_get_column_declaration(TDSSOCKET * tds, TDSCOLUMN * curcol, char *out);

TDSRET tds_cursor_declare(TDSSOCKET * tds, TDSCURSOR * cursor, TDSPARAMINFO *params, int *send);
TDSRET tds_cursor_setrows(TDSSOCKET * tds, TDSCURSOR * cursor, int *send);
TDSRET tds_cursor_open(TDSSOCKET * tds, TDSCURSOR * cursor, TDSPARAMINFO *params, int *send);
TDSRET tds_cursor_fetch(TDSSOCKET * tds, TDSCURSOR * cursor, TDS_CURSOR_FETCH fetch_type, TDS_INT i_row);
TDSRET tds_cursor_get_cursor_info(TDSSOCKET * tds, TDSCURSOR * cursor, TDS_UINT * row_number, TDS_UINT * row_count);
TDSRET tds_cursor_close(TDSSOCKET * tds, TDSCURSOR * cursor);
TDSRET tds_cursor_dealloc(TDSSOCKET * tds, TDSCURSOR * cursor);
TDSRET tds_deferred_cursor_dealloc(TDSCONNECTION *conn, TDSCURSOR * cursor);
TDSRET tds_cursor_update(TDSSOCKET * tds, TDSCURSOR * cursor, TDS_CURSOR_OPERATION op, TDS_INT i_row, TDSPARAMINFO * params);
TDSRET tds_cursor_setname(TDSSOCKET * tds, TDSCURSOR * cursor);

TDSRET tds_multiple_init(TDSSOCKET *tds, TDSMULTIPLE *multiple, TDS_MULTIPLE_TYPE type, TDSHEADERS * head);
TDSRET tds_multiple_done(TDSSOCKET *tds, TDSMULTIPLE *multiple);
TDSRET tds_multiple_query(TDSSOCKET *tds, TDSMULTIPLE *multiple, const char *query, TDSPARAMINFO * params);
TDSRET tds_multiple_execute(TDSSOCKET *tds, TDSMULTIPLE *multiple, TDSDYNAMIC * dyn);


/* token.c */
TDSRET tds_process_cancel(TDSSOCKET * tds);
int tds_get_token_size(int marker);
TDSRET tds_process_login_tokens(TDSSOCKET * tds);
TDSRET tds_process_simple_query(TDSSOCKET * tds);
int tds5_send_optioncmd(TDSSOCKET * tds, TDS_OPTION_CMD tds_command, TDS_OPTION tds_option, TDS_OPTION_ARG * tds_argument,
			TDS_INT * tds_argsize);
TDSRET tds_process_tokens(TDSSOCKET * tds, /*@out@*/ TDS_INT * result_type, /*@out@*/ int *done_flags, unsigned flag);
int determine_adjusted_size(const TDSICONV * char_conv, int size);


/* data.c */
void tds_set_param_type(TDSCONNECTION * conn, TDSCOLUMN * curcol, TDS_SERVER_TYPE type);
void tds_set_column_type(TDSCONNECTION * conn, TDSCOLUMN * curcol, int type);


/* tds_convert.c */
TDSRET tds_datecrack(TDS_INT datetype, const void *di, TDSDATEREC * dr);
int tds_get_conversion_type(int srctype, int colsize);
extern const char tds_hex_digits[];


/* write.c */
int tds_init_write_buf(TDSSOCKET * tds);
int tds_put_n(TDSSOCKET * tds, const void *buf, size_t n);
int tds_put_string(TDSSOCKET * tds, const char *buf, int len);
int tds_put_int(TDSSOCKET * tds, TDS_INT i);
int tds_put_int8(TDSSOCKET * tds, TDS_INT8 i);
int tds_put_smallint(TDSSOCKET * tds, TDS_SMALLINT si);
/** Output a tinyint value */
#define tds_put_tinyint(tds, ti) tds_put_byte(tds,ti)
int tds_put_byte(TDSSOCKET * tds, unsigned char c);
TDSRET tds_flush_packet(TDSSOCKET * tds);
int tds_put_buf(TDSSOCKET * tds, const unsigned char *buf, int dsize, int ssize);


/* read.c */
unsigned char tds_get_byte(TDSSOCKET * tds);
void tds_unget_byte(TDSSOCKET * tds);
unsigned char tds_peek(TDSSOCKET * tds);
TDS_USMALLINT tds_get_usmallint(TDSSOCKET * tds);
#define tds_get_smallint(tds) ((TDS_SMALLINT) tds_get_usmallint(tds))
TDS_UINT tds_get_uint(TDSSOCKET * tds);
#define tds_get_int(tds) ((TDS_INT) tds_get_uint(tds))
TDS_UINT8 tds_get_uint8(TDSSOCKET * tds);
#define tds_get_int8(tds) ((TDS_INT8) tds_get_uint8(tds))
size_t tds_get_string(TDSSOCKET * tds, size_t string_len, char *dest, size_t dest_size);
TDSRET tds_get_char_data(TDSSOCKET * tds, char *dest, size_t wire_size, TDSCOLUMN * curcol);
void *tds_get_n(TDSSOCKET * tds, /*@out@*/ /*@null@*/ void *dest, size_t n);
extern int tds_get_size_by_type(int servertype);
DSTR* tds_dstr_get(TDSSOCKET * tds, DSTR * s, size_t len);


/* util.c */
int tdserror (const TDSCONTEXT * tds_ctx, TDSSOCKET * tds, int msgno, int errnum);
TDS_STATE tds_set_state(TDSSOCKET * tds, TDS_STATE state);
void tds_swap_bytes(void *buf, int bytes);
#ifdef ENABLE_DEVELOPING
unsigned int tds_gettime_ms(void);
#endif
char *tds_strndup(const void *s, TDS_INTPTR len);


/* log.c */
void tdsdump_off(void);
void tdsdump_on(void);
int tdsdump_isopen(void);
#include <freetds/popvis.h>
int tdsdump_open(const char *filename);
#include <freetds/pushvis.h>
void tdsdump_close(void);
void tdsdump_dump_buf(const char* file, unsigned int level_line, const char *msg, const void *buf, size_t length);
void tdsdump_col(const TDSCOLUMN *col);
#undef tdsdump_log
void tdsdump_log(const char* file, unsigned int level_line, const char *fmt, ...)
#if defined(__GNUC__) && __GNUC__ >= 2
#if defined(__MINGW32__)
	__attribute__ ((__format__ (ms_printf, 3, 4)))
#else
	__attribute__ ((__format__ (__printf__, 3, 4)))
#endif
#endif
;
#define TDSDUMP_LOG_FAST if (TDS_UNLIKELY(tds_write_dump)) tdsdump_log
#define tdsdump_log TDSDUMP_LOG_FAST
#define TDSDUMP_BUF_FAST if (TDS_UNLIKELY(tds_write_dump)) tdsdump_dump_buf
#define tdsdump_dump_buf TDSDUMP_BUF_FAST

extern int tds_write_dump;
extern int tds_debug_flags;
extern int tds_g_append_mode;


/* net.c */
extern TDSERRNO tds_open_socket(TDSSOCKET * tds, struct addrinfo *ipaddr, unsigned int port, int timeout, int *p_oserr);
extern void tds_close_socket(TDSSOCKET * tds);
extern int tds7_get_instance_ports(SGX_WRAPPER_FILE output, struct addrinfo *addr);
extern int tds7_get_instance_port(struct addrinfo *addr, const char *instance);
// char *tds_prwsaerror(int erc);
// void tds_prwsaerror_free(char *s);
int tds_connection_read(TDSSOCKET * tds, unsigned char *buf, int buflen);
int tds_connection_write(TDSSOCKET *tds, const unsigned char *buf, int buflen, int final);
#define TDSSELREAD  POLLIN
#define TDSSELWRITE POLLOUT
int tds_select(TDSSOCKET * tds, unsigned tds_sel, int timeout_seconds);
#if ENABLE_ODBC_MARS
// void tds_connection_close(TDSCONNECTION *conn);
#endif
extern int tds_goodread(TDSSOCKET * tds, unsigned char *buf, int buflen);
extern int tds_goodwrite(TDSSOCKET * tds, const unsigned char *buffer, size_t buflen);
extern void tds_socket_flush(TDS_SYS_SOCKET sock);
extern int tds_socket_set_nonblocking(TDS_SYS_SOCKET sock);
extern int tds_wakeup_init(TDSPOLLWAKEUP *wakeup);
extern void tds_wakeup_close(TDSPOLLWAKEUP *wakeup);
extern void tds_wakeup_send(TDSPOLLWAKEUP *wakeup, char cancel);
static inline TDS_SYS_SOCKET tds_wakeup_get_fd(const TDSPOLLWAKEUP *wakeup)
{
	return wakeup->s_signaled;
}


/* packet.c */
int tds_read_packet(TDSSOCKET * tds);
TDSRET tds_write_packet(TDSSOCKET * tds, unsigned char final);
#if ENABLE_ODBC_MARS
int tds_append_cancel(TDSSOCKET *tds);
TDSRET tds_append_fin(TDSSOCKET *tds);
#else
int tds_put_cancel(TDSSOCKET * tds);
static inline
void tds_connection_close(TDSCONNECTION *connection)
{
	tds_close_socket((TDSSOCKET* ) connection);
}
#endif


/* vstrbuild.c */
TDSRET tds_vstrbuild(char *buffer, int buflen, int *resultlen, const char *text, int textlen, const char *formats, int formatlen,
		  va_list ap);


/* numeric.c */
char *tds_money_to_string(const TDS_MONEY * money, char *s);
TDS_INT tds_numeric_to_string(const TDS_NUMERIC * numeric, char *s);
TDS_INT tds_numeric_change_prec_scale(TDS_NUMERIC * numeric, unsigned char new_prec, unsigned char new_scale);


/* getmac.c */
void tds_getmac(TDS_SYS_SOCKET s, unsigned char mac[6]);


/* challenge.c */
#ifndef HAVE_SSPI
TDSAUTHENTICATION * tds_ntlm_get_auth(TDSSOCKET * tds);
TDSAUTHENTICATION * tds_gss_get_auth(TDSSOCKET * tds);
#else
TDSAUTHENTICATION * tds_sspi_get_auth(TDSSOCKET * tds);
#endif


/* random.c */
extern void tds_random_buffer(unsigned char *out, int len);


/* sec_negotiate.c */
TDSAUTHENTICATION * tds5_negotiate_get_auth(TDSSOCKET * tds);
void tds5_negotiate_set_msg_type(TDSSOCKET * tds, TDSAUTHENTICATION * auth, unsigned msg_type);




TDSRET tds_bcp_init(TDSSOCKET *tds, TDSBCPINFO *bcpinfo);
typedef TDSRET (*tds_bcp_get_col_data) (TDSBCPINFO *bulk, TDSCOLUMN *bcpcol, int offset);
typedef void (*tds_bcp_null_error)   (TDSBCPINFO *bulk, int index, int offset);
TDSRET tds_bcp_send_record(TDSSOCKET *tds, TDSBCPINFO *bcpinfo, tds_bcp_get_col_data get_col_data, tds_bcp_null_error null_error, int offset);
TDSRET tds_bcp_done(TDSSOCKET *tds, int *rows_copied);
TDSRET tds_bcp_start(TDSSOCKET *tds, TDSBCPINFO *bcpinfo);
TDSRET tds_bcp_start_copy_in(TDSSOCKET *tds, TDSBCPINFO *bcpinfo);

TDSRET tds_bcp_fread(TDSSOCKET * tds, TDSICONV * conv, SGX_WRAPPER_FILE stream,
		     const char *terminator, size_t term_len, char **outbuf, size_t * outbytes);

TDSRET tds_writetext_start(TDSSOCKET *tds, const char *objname, const char *textptr, const char *timestamp, int with_log, TDS_UINT size);
TDSRET tds_writetext_continue(TDSSOCKET *tds, const TDS_UCHAR *text, TDS_UINT size);
TDSRET tds_writetext_end(TDSSOCKET *tds);


static inline
bool tds_capability_enabled(const TDS_CAPABILITY_TYPE *cap, unsigned cap_num)
{
	return (cap->values[sizeof(cap->values)-1-(cap_num>>3)] >> (cap_num&7)) & 1;
}
#define tds_capability_has_req(conn, cap) \
	tds_capability_enabled(&conn->capabilities.types[0], cap)

#define IS_TDS42(x) (x->tds_version==0x402)
#define IS_TDS46(x) (x->tds_version==0x406)
#define IS_TDS50(x) (x->tds_version==0x500)
#define IS_TDS70(x) (x->tds_version==0x700)
#define IS_TDS71(x) (x->tds_version==0x701)
#define IS_TDS72(x) (x->tds_version==0x702)
#define IS_TDS73(x) (x->tds_version==0x703)

#define IS_TDS50_PLUS(x) ((x)->tds_version>=0x500)
#define IS_TDS7_PLUS(x)  ((x)->tds_version>=0x700)
#define IS_TDS71_PLUS(x) ((x)->tds_version>=0x701)
#define IS_TDS72_PLUS(x) ((x)->tds_version>=0x702)
#define IS_TDS73_PLUS(x) ((x)->tds_version>=0x703)
#define IS_TDS74_PLUS(x) ((x)->tds_version>=0x704)

#define TDS_MAJOR(x) ((x)->tds_version >> 8)
#define TDS_MINOR(x) ((x)->tds_version & 0xff)

#define IS_TDSDEAD(x) (((x) == NULL) || (x)->state == TDS_DEAD)

/** Check if product is Sybase (such as Adaptive Server Enterrprice). x should be a TDSSOCKET*. */
#define TDS_IS_SYBASE(x) (!((x)->conn->product_version & 0x80000000u))
/** Check if product is Microsft SQL Server. x should be a TDSSOCKET*. */
#define TDS_IS_MSSQL(x) (((x)->conn->product_version & 0x80000000u)!=0)

/** Calc a version number for mssql. Use with TDS_MS_VER(7,0,842).
 * For test for a range of version you can use check like
 * if (tds->product_version >= TDS_MS_VER(7,0,0) && tds->product_version < TDS_MS_VER(8,0,0)) */
#define TDS_MS_VER(maj,min,x) (0x80000000u|((maj)<<24)|((min)<<16)|(x))

/* TODO test if not similar to ms one*/
/** Calc a version number for Sybase. */
#define TDS_SYB_VER(maj,min,x) (((maj)<<24)|((min)<<16)|(x)<<8)

#ifdef __cplusplus
#if 0
{
#endif
}
#endif

#include <freetds/popvis.h>

#define TDS_PUT_INT(tds,v) tds_put_int((tds), ((TDS_INT)(v)))
#define TDS_PUT_SMALLINT(tds,v) tds_put_smallint((tds), ((TDS_SMALLINT)(v)))
#define TDS_PUT_BYTE(tds,v) tds_put_byte((tds), ((unsigned char)(v)))

#endif /* _tds_h_ */
