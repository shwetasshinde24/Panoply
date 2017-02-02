#ifndef TDS_STRUCT_H
#define TDS_STRUCT_H

#include "tds_sysdep_public.h"
//#include <freetds/thread_enclave.h>

#ifndef TDS_SYS_SOCKET_TYPEDEF
#define TDS_SYS_SOCKET_TYPEDEF
typedef int TDS_SYS_SOCKET;
#endif

/* forward declaration */
typedef struct tdsiconvinfo TDSICONV;
typedef struct tds_connection TDSCONNECTION;
typedef struct tds_socket TDSSOCKET;
typedef struct tds_column TDSCOLUMN;
typedef struct tds_bcpinfo TDSBCPINFO;

/* 
 * All references to data that touch the wire should use the following typedefs.  
 *
 * If you have problems on 64-bit machines and the code is 
 * using a native datatype, please change it to use
 * these. (In the TDS layer only, the API layers have their
 * own typedefs which equate to these).
 */
typedef char TDS_CHAR;					/*  8-bit char     */
typedef unsigned char TDS_UCHAR;			/*  8-bit uchar    */
typedef unsigned char TDS_TINYINT;			/*  8-bit unsigned */
typedef tds_sysdep_int16_type TDS_SMALLINT;		/* 16-bit int      */
typedef unsigned tds_sysdep_int16_type TDS_USMALLINT;	/* 16-bit unsigned */
typedef tds_sysdep_int32_type TDS_INT;			/* 32-bit int      */
typedef unsigned tds_sysdep_int32_type TDS_UINT;	/* 32-bit unsigned */
typedef tds_sysdep_real32_type TDS_REAL;		/* 32-bit real     */
typedef tds_sysdep_real64_type TDS_FLOAT;		/* 64-bit real     */
typedef tds_sysdep_int64_type TDS_INT8;			/* 64-bit integer  */
typedef unsigned tds_sysdep_int64_type TDS_UINT8;	/* 64-bit unsigned */
typedef tds_sysdep_intptr_type TDS_INTPTR;
typedef unsigned tds_sysdep_intptr_type TDS_UINTPTR;

#include <freetds/proto.h>



/**
 * Structure to hold a string.
 * Use tds_dstr_* functions/macros, do not access members directly.
 * There should be always a buffer.
 */
typedef struct tds_dstr {
	size_t dstr_size;
	char dstr_s[1];
} *DSTR;

/**
 * A structure to hold all the compile-time settings.
 * This structure is returned by tds_get_compiletime_settings
 */

typedef struct tds_compiletime_settings
{
	const char *freetds_version;	/* release version of FreeTDS */
	const char *sysconfdir;		/* location of freetds.conf */
	const char *last_update;	/* latest software_version date among the modules */
	int msdblib;		/* for MS style dblib */
	int sybase_compat;	/* enable increased Open Client binary compatibility */
	int threadsafe;		/* compile for thread safety default=no */
	int libiconv;		/* search for libiconv in DIR/include and DIR/lib */
	const char *tdsver;	/* TDS protocol version (4.2/4.6/5.0/7.0/7.1) 5.0 */
	int iodbc;		/* build odbc driver against iODBC in DIR */
	int unixodbc;		/* build odbc driver against unixODBC in DIR */
	int openssl;		/* build against OpenSSL */
	int gnutls;		/* build against GnuTLS */
	int mars;		/* MARS enabled */
} TDS_COMPILETIME_SETTINGS;

typedef int TDSRET;

/**
 * this structure is not directed connected to a TDS protocol but
 * keeps any DATE/TIME information.
 */
typedef struct
{
	TDS_UINT8   time;	/**< time, 7 digit precision */
	TDS_INT      date;	/**< date, 0 = 1900-01-01 */
	TDS_SMALLINT offset;	/**< time offset */
	TDS_USMALLINT time_prec:3;
	TDS_USMALLINT _res:10;
	TDS_USMALLINT has_time:1;
	TDS_USMALLINT has_date:1;
	TDS_USMALLINT has_offset:1;
} TDS_DATETIMEALL;

/** Used by tds_datecrack */
typedef struct tdsdaterec
{
	TDS_INT year;	       /**< year */
	TDS_INT quarter;       /**< quarter (0-3) */
	TDS_INT month;	       /**< month number (0-11) */
	TDS_INT day;	       /**< day of month (1-31) */
	TDS_INT dayofyear;     /**< day of year  (1-366) */
	TDS_INT weekday;       /**< day of week  (0-6, 0 = sunday) */
	TDS_INT hour;	       /**< 0-23 */
	TDS_INT minute;	       /**< 0-59 */
	TDS_INT second;	       /**< 0-59 */
	TDS_INT decimicrosecond;   /**< 0-9999999 */
	TDS_INT timezone;      /**< -840 - 840 minutes from UTC */
} TDSDATEREC;

/**
 * @file tds.h
 * Main include file for libtds
 */

/**
 * \defgroup libtds LibTDS API
 * Callable functions in \c libtds.
 * 
 * The \c libtds library is for use internal to \em FreeTDS.  It is not
 * intended for use by applications.  Although any use is \em permitted, you're
 * encouraged to use one of the established public APIs instead, because their
 * interfaces are stable and documented by the vendors.  
 */



#define TDS_MAX_CAPABILITY	32
#define MAXPRECISION 		77
#define TDS_MAX_CONN		4096
#define TDS_MAX_DYNID_LEN	30

/* defaults to use if no others are found */
#define TDS_DEF_SERVER		"SYBASE"
#define TDS_DEF_BLKSZ		512
#define TDS_DEF_CHARSET		"iso_1"
#define TDS_DEF_LANG		"us_english"
#if TDS42
#define TDS_DEFAULT_VERSION	0x402
#define TDS_DEF_PORT		1433
#elif TDS46
#define TDS_DEFAULT_VERSION	0x406
#define TDS_DEF_PORT		4000
#elif TDS50
#define TDS_DEFAULT_VERSION	0x500
#define TDS_DEF_PORT		4000
#elif TDS70
#define TDS_DEFAULT_VERSION	0x700
#define TDS_DEF_PORT		1433
#elif TDS71
#define TDS_DEFAULT_VERSION	0x701
#define TDS_DEF_PORT		1433
#elif TDS72
#define TDS_DEFAULT_VERSION	0x702
#define TDS_DEF_PORT		1433
#elif TDS73
#define TDS_DEFAULT_VERSION	0x703
#define TDS_DEF_PORT		1433
#elif TDS74
#define TDS_DEFAULT_VERSION	0x704
#define TDS_DEF_PORT		1433
#else
#define TDS_DEFAULT_VERSION	0x000
#define TDS_DEF_PORT		1433
#endif

/* normalized strings from freetds.conf file */
#define TDS_STR_VERSION  "tds version"
#define TDS_STR_BLKSZ    "initial block size"
#define TDS_STR_SWAPDT   "swap broken dates"
#define TDS_STR_DUMPFILE "dump file"
#define TDS_STR_DEBUGLVL "debug level"
#define TDS_STR_DEBUGFLAGS "debug flags"
#define TDS_STR_TIMEOUT  "timeout"
#define TDS_STR_QUERY_TIMEOUT  "query timeout"
#define TDS_STR_CONNTIMEOUT "connect timeout"
#define TDS_STR_HOSTNAME "hostname"
#define TDS_STR_HOST     "host"
#define TDS_STR_PORT     "port"
#define TDS_STR_TEXTSZ   "text size"
/* for big endian hosts */
#define TDS_STR_EMUL_LE	"emulate little endian"
#define TDS_STR_CHARSET	"charset"
#define TDS_STR_CLCHARSET	"client charset"
#define TDS_STR_USE_UTF_16	"use utf-16"
#define TDS_STR_LANGUAGE	"language"
#define TDS_STR_APPENDMODE	"dump file append"
#define TDS_STR_DATEFMT	"date format"
#define TDS_STR_INSTANCE "instance"
#define TDS_STR_ASA_DATABASE	"asa database"
#define TDS_STR_DATABASE	"database"
#define TDS_STR_ENCRYPTION	 "encryption"
#define TDS_STR_USENTLMV2	"use ntlmv2"
#define TDS_STR_USELANMAN	"use lanman"
/* conf values */
#define TDS_STR_ENCRYPTION_OFF	 "off"
#define TDS_STR_ENCRYPTION_REQUEST "request"
#define TDS_STR_ENCRYPTION_REQUIRE "require"
/* Defines to enable optional GSSAPI delegation */
#define TDS_GSSAPI_DELEGATION "enable gssapi delegation"
/* Kerberos realm name */
#define TDS_STR_REALM	"realm"
/* Kerberos SPN */
#define TDS_STR_SPN	"spn"
/* CA file */
#define TDS_STR_CAFILE	"ca file"
/* CRL file */
#define TDS_STR_CRLFILE	"crl file"
/* check SSL hostname */
#define TDS_STR_CHECKSSLHOSTNAME	"check certificate hostname"
/* database filename to attach on login (MSSQL) */
#define TDS_STR_DBFILENAME	"database filename"
/* Application Intent MSSQL 2012 support */
#define TDS_STR_READONLY_INTENT "read-only intent"

/* TODO do a better check for alignment than this */
typedef union
{
	void *p;
	int i;
	TDS_INT8 ui;
} tds_align_struct;

#define TDS_ALIGN_SIZE sizeof(tds_align_struct)

typedef struct tds_capability_type
{
	unsigned char type;
	unsigned char len; /* always sizeof(values) */
	unsigned char values[TDS_MAX_CAPABILITY/2-2];
} TDS_CAPABILITY_TYPE;

typedef struct tds_capabilities
{
	TDS_CAPABILITY_TYPE types[2];
} TDS_CAPABILITIES;

#define TDS_MAX_LOGIN_STR_SZ 128
typedef struct tds_login
{
	DSTR server_name;		/**< server name (in freetds.conf) */
	int port;			/**< port of database service */
	TDS_USMALLINT tds_version;	/**< TDS version */
	int block_size;
	DSTR language;			/* e.g. us-english */
	DSTR server_charset;		/**< charset of server e.g. iso_1 */
	TDS_INT connect_timeout;
	DSTR client_host_name;
	DSTR server_host_name;
	DSTR server_realm_name;		/**< server realm name (in freetds.conf) */
	DSTR server_spn;		/**< server SPN (in freetds.conf) */
	DSTR db_filename;		/**< database filename to attach (MSSQL) */
	DSTR cafile;			/**< certificate authorities file */
	DSTR crlfile;			/**< certificate revocation file */
	DSTR app_name;
	DSTR user_name;	    	/**< account for login */
	DSTR password;	    	/**< password of account login */
	DSTR new_password;	    	/**< new password to set (TDS 7.2+) */

	DSTR library;	/* Ct-Library, DB-Library,  TDS-Library or ODBC */
	TDS_TINYINT encryption_level;

	TDS_INT query_timeout;
	TDS_CAPABILITIES capabilities;
	DSTR client_charset;
	DSTR database;

	struct addrinfo *ip_addrs;	  		/**< ip(s) of server */
	struct addrinfo *connected_addr;	/* ip of connected server */
	DSTR instance_name;
	DSTR dump_file;
	int debug_flags;
	int text_size;

	unsigned char option_flag2;

	unsigned int bulk_copy:1;
	unsigned int suppress_language:1;
	unsigned int emul_little_endian:1;
	unsigned int gssapi_use_delegation:1;
	unsigned int use_ntlmv2:1;
	unsigned int use_lanman:1;
	unsigned int mars:1;
	unsigned int use_utf16:1;
	unsigned int use_new_password:1;
	unsigned int valid_configuration:1;
	unsigned int check_ssl_hostname:1;
	unsigned int readonly_intent:1;
} TDSLOGIN;

typedef struct tds_headers
{
	const char *qn_options;
	const char *qn_msgtext;
	TDS_INT qn_timeout;
	/* TDS 7.4+: trace activity ID char[20] */
} TDSHEADERS;

typedef struct tds_locale
{
	char *language;
	char *server_charset;
	char *date_fmt;
} TDSLOCALE;


/** 
 * Information about blobs (e.g. text or image).
 * current_row contains this structure.
 */
typedef struct tds_blob
{
	TDS_CHAR *textvalue;
	TDS_CHAR textptr[16];
	TDS_CHAR timestamp[8];
	unsigned char valid_ptr;
} TDSBLOB;
/**
 * Store variant informations
 */
typedef struct tds_variant
{
	/* this MUST have same position and place of textvalue in tds_blob */
	TDS_CHAR *data;
	TDS_INT size;
	TDS_INT data_len;
	TDS_UCHAR type;
	TDS_UCHAR collation[5];
} TDSVARIANT;

/**
 * Information relevant to libiconv.  The name is an iconv name, not 
 * the same as found in master..syslanguages. 
 */
typedef struct tds_encoding
{
	/** name of the encoding (ie UTF-8) */
	const char *name;
	unsigned char min_bytes_per_char;
	unsigned char max_bytes_per_char;
	/** internal numeric index into array of all encodings */
	unsigned char canonic;
} TDS_ENCODING;

typedef struct tds_bcpcoldata
{
	TDS_UCHAR *data;
	TDS_INT    datalen;
	TDS_INT    is_null;
} BCPCOLDATA;


/** values for tds->state */
typedef enum tds_states
{
	TDS_IDLE,	/**< no data exmakepected */
	TDS_WRITING,	/**< client is writing data */
	TDS_SENDING,	/**< client would send data */
	TDS_PENDING,	/**< cilent is waiting for data */
	TDS_READING,	/**< client is reading data */
	TDS_DEAD	/**< no connection */
} TDS_STATE;

typedef enum tds_operations
{
	TDS_OP_NONE		= 0,

	/* mssql operations */
	TDS_OP_CURSOR		= TDS_SP_CURSOR,
	TDS_OP_CURSOROPEN	= TDS_SP_CURSOROPEN,
	TDS_OP_CURSORPREPARE	= TDS_SP_CURSORPREPARE,
	TDS_OP_CURSOREXECUTE	= TDS_SP_CURSOREXECUTE,
	TDS_OP_CURSORPREPEXEC	= TDS_SP_CURSORPREPEXEC,
	TDS_OP_CURSORUNPREPARE	= TDS_SP_CURSORUNPREPARE,
	TDS_OP_CURSORFETCH	= TDS_SP_CURSORFETCH,
	TDS_OP_CURSOROPTION	= TDS_SP_CURSOROPTION,
	TDS_OP_CURSORCLOSE	= TDS_SP_CURSORCLOSE,
	TDS_OP_EXECUTESQL	= TDS_SP_EXECUTESQL,
	TDS_OP_PREPARE		= TDS_SP_PREPARE,
	TDS_OP_EXECUTE		= TDS_SP_EXECUTE,
	TDS_OP_PREPEXEC		= TDS_SP_PREPEXEC,
	TDS_OP_PREPEXECRPC	= TDS_SP_PREPEXECRPC,
	TDS_OP_UNPREPARE	= TDS_SP_UNPREPARE,

	/* sybase operations */
	TDS_OP_DYN_DEALLOC	= 100,
} TDS_OPERATION;


typedef struct tds_message
{
	TDS_CHAR *server;
	TDS_CHAR *message;
	TDS_CHAR *proc_name;
	TDS_CHAR *sql_state;
	TDS_INT msgno;
	TDS_INT line_number;
	/* -1 .. 255 */
	TDS_SMALLINT state;
	TDS_TINYINT priv_msg_type;
	TDS_TINYINT severity;
	/* for library-generated errors */
	int oserr;
} TDSMESSAGE;

typedef struct tds_upd_col
{
	struct tds_upd_col *next;	
	TDS_INT colnamelength;
	char * columnname;
} TDSUPDCOL;

typedef enum {
	  TDS_CURSOR_STATE_UNACTIONED = 0   	/* initial value */
	, TDS_CURSOR_STATE_REQUESTED = 1	/* called by ct_cursor */ 
	, TDS_CURSOR_STATE_SENT = 2		/* sent to server */
	, TDS_CURSOR_STATE_ACTIONED = 3		/* acknowledged by server */
} TDS_CURSOR_STATE;

typedef struct tds_cursor_status
{
	TDS_CURSOR_STATE declare;
	TDS_CURSOR_STATE cursor_row;
	TDS_CURSOR_STATE open;
	TDS_CURSOR_STATE fetch;
	TDS_CURSOR_STATE close; 
	TDS_CURSOR_STATE dealloc;
} TDS_CURSOR_STATUS;

typedef enum tds_cursor_operation
{
	TDS_CURSOR_POSITION = 0,
	TDS_CURSOR_UPDATE = 1,
	TDS_CURSOR_DELETE = 2,
	TDS_CURSOR_INSERT = 4
} TDS_CURSOR_OPERATION;

typedef enum tds_cursor_fetch
{
	TDS_CURSOR_FETCH_NEXT = 1,
	TDS_CURSOR_FETCH_PREV,
	TDS_CURSOR_FETCH_FIRST,
	TDS_CURSOR_FETCH_LAST,
	TDS_CURSOR_FETCH_ABSOLUTE,
	TDS_CURSOR_FETCH_RELATIVE
} TDS_CURSOR_FETCH;

typedef TDSRET  tds_func_get_info(TDSSOCKET *tds, TDSCOLUMN *col);
typedef TDSRET  tds_func_get_data(TDSSOCKET *tds, TDSCOLUMN *col);
typedef TDS_INT tds_func_row_len(TDSCOLUMN *col);
typedef unsigned tds_func_put_info_len(TDSSOCKET *tds, TDSCOLUMN *col);
typedef TDSRET  tds_func_put_info(TDSSOCKET *tds, TDSCOLUMN *col);
typedef TDSRET  tds_func_put_data(TDSSOCKET *tds, TDSCOLUMN *col, int bcp7);
typedef int     tds_func_check(const TDSCOLUMN *col);

typedef struct tds_column_funcs
{
	tds_func_get_info *get_info;
	tds_func_get_data *get_data;
	tds_func_row_len  *row_len;
	/**
	 * Returns metadata column information size.
	 * \tds
	 * \param col  column to send
	 */
	tds_func_put_info_len *put_info_len;
	/**
	 * Send metadata column information to server.
	 * \tds
	 * \param col  column to send
	 */
	tds_func_put_info *put_info;
	/**
	 * Send column data to server.
	 * Usually send parameters unless bcp7 is specified, in
	 * this case send BCP for TDS7+ (Sybase use a completely
	 * different format for BCP)
	 * \tds
	 * \param col  column to send
	 * \param bcp7 1 to send BCP column on TDS7+
	 */
	tds_func_put_data *put_data;
#if ENABLE_EXTRA_CHECKS
	/**
	 * Check column is valid.
	 * Some things should be checked:
	 * - column_type and on_server.column_type;
	 * - column_size and on_server.column_size;
	 * - column_cur_size;
	 * - column_prec and column_scale;
	 * - is_XXXX_type macros/functions (nullable/fixed/blob/variable);
	 * - tds_get_size_by_type;
	 * - tds_get_conversion_type.
	 *
	 * \tds
	 * \param col  column to check
	 */
	tds_func_check    *check;
#endif
#if 0
	TDSRET (*convert)(TDSSOCKET *tds, TDSCOLUMN *col);
#endif
} TDSCOLUMNFUNCS;

/** 
 * Metadata about columns in regular and compute rows 
 */
struct tds_column
{
	const TDSCOLUMNFUNCS *funcs;
	TDS_INT column_usertype;
	TDS_INT column_flags;

	TDS_INT column_size;		/**< maximun size of data. For fixed is the size. */

	TDS_TINYINT column_type;	/**< This type can be different from wire type because
	 				 * conversion (e.g. UCS-2->Ascii) can be applied.
					 * I'm beginning to wonder about the wisdom of this, however.
					 * April 2003 jkl
					 */
	TDS_TINYINT column_varint_size;	/**< size of length when reading from wire (0, 1, 2 or 4) */

	TDS_TINYINT column_prec;	/**< precision for decimal/numeric */
	TDS_TINYINT column_scale;	/**< scale for decimal/numeric */

	struct
	{
		TDS_TINYINT column_type;	/**< type of data, saved from wire */
		TDS_INT column_size;
	} on_server;

	TDSICONV *char_conv;	/**< refers to previously allocated iconv information */

	DSTR table_name;
	DSTR column_name;
	DSTR table_column_name;

	unsigned char *column_data;
	void (*column_data_free)(struct tds_column *column);
	unsigned int column_nullable:1;
	unsigned int column_writeable:1;
	unsigned int column_identity:1;
	unsigned int column_key:1;
	unsigned int column_hidden:1;
	unsigned int column_output:1;
	unsigned int column_timestamp:1;
	TDS_UCHAR column_collation[5];

	/* additional fields flags for compute results */
	TDS_TINYINT column_operator;
	TDS_SMALLINT column_operand;

	/* FIXME this is data related, not column */
	/** size written in variable (ie: char, text, binary). -1 if NULL. */
	TDS_INT column_cur_size;

	/* related to binding or info stored by client libraries */
	/* FIXME find a best place to store these data, some are unused */
	TDS_SMALLINT column_bindtype;
	TDS_SMALLINT column_bindfmt;
	TDS_UINT column_bindlen;
	TDS_SMALLINT *column_nullbind;
	TDS_CHAR *column_varaddr;
	TDS_INT *column_lenbind;
	TDS_INT column_textpos;
	TDS_INT column_text_sqlgetdatapos;
	TDS_CHAR column_text_sqlputdatainfo;

	BCPCOLDATA *bcp_column_data;
	/**
	 * The length, in bytes, of any length prefix this column may have.
	 * For example, strings in some non-C programming languages are
	 * made up of a one-byte length prefix, followed by the string
	 * data itself.
	 * If the data do not have a length prefix, set prefixlen to 0.
	 * Currently not very used in code, however do not remove.
	 */
	TDS_INT bcp_prefix_len;
	TDS_INT bcp_term_len;
	TDS_CHAR *bcp_terminator;
};


/** Hold information for any results */
typedef struct tds_result_info
{
	/* TODO those fields can became a struct */
	TDSCOLUMN **columns;
	TDS_USMALLINT num_cols;
	TDS_USMALLINT computeid;
	TDS_INT ref_count;
	TDSSOCKET *attached_to;
	unsigned char *current_row;
	void (*row_free)(struct tds_result_info* result, unsigned char *row);
	TDS_INT row_size;

	TDS_SMALLINT *bycolumns;
	TDS_USMALLINT by_cols;
	TDS_TINYINT rows_exist;
	/* TODO remove ?? used only in dblib */
	TDS_TINYINT more_results;
} TDSRESULTINFO;

typedef struct tds_result_info TDSCOMPUTEINFO;

typedef TDSRESULTINFO TDSPARAMINFO;

/**
 * Holds informations about a cursor
 */
typedef struct tds_cursor
{
	struct tds_cursor *next;	/**< next in linked list, keep first */
	TDS_INT ref_count;		/**< reference counter so client can retain safely a pointer */
	char *cursor_name;		/**< name of the cursor */
	TDS_INT cursor_id;		/**< cursor id returned by the server after cursor declare */
	TDS_TINYINT options;		/**< read only|updatable TODO use it */
	/**
	 * true if cursor was marker to be closed when connection is idle
	 */
	TDS_TINYINT defer_close;
	char *query;                 	/**< SQL query */
	/* TODO for updatable columns */
	/* TDS_TINYINT number_upd_cols; */	/**< number of updatable columns */
	/* TDSUPDCOL *cur_col_list; */	/**< updatable column list */
	TDS_INT cursor_rows;		/**< number of cursor rows to fetch */
	/* TDSPARAMINFO *params; */	/** cursor parameter */
	TDS_CURSOR_STATUS status;
	TDS_USMALLINT srv_status;
	TDSRESULTINFO *res_info;	/** row fetched from this cursor */
	TDS_INT type, concurrency;
} TDSCURSOR;

/**
 * Current environment as reported by the server
 */
typedef struct tds_env
{
	/** packet size (512-65535) */
	int block_size;
	char *language;
	/** character set encoding */
	char *charset;
	/** database name */
	char *database;
} TDSENV;

/**
 * Holds information for a dynamic (also called prepared) query.
 */
typedef struct tds_dynamic
{
	struct tds_dynamic *next;	/**< next in linked list, keep first */
	TDS_INT ref_count;		/**< reference counter so client can retain safely a pointer */
	/** numeric id for mssql7+*/
	TDS_INT num_id;
	/** 
	 * id of dynamic.
	 * Usually this id correspond to server one but if not specified
	 * is generated automatically by libTDS
	 */
	char id[30];
	/**
	 * this dynamic query cannot be prepared so libTDS have to construct a simple query.
	 * This can happen for instance is tds protocol doesn't support dynamics or trying
	 * to prepare query under Sybase that have BLOBs as parameters.
	 */
	TDS_TINYINT emulated;
	/**
	 * true if dynamic was marker to be closed when connection is idle
	 */
	TDS_TINYINT defer_close;
	/* int dyn_state; */ /* TODO use it */
	TDSPARAMINFO *res_info;	/**< query results */
	/**
	 * query parameters.
	 * Mostly used executing query however is a good idea to prepare query
	 * again if parameter type change in an incompatible way (ie different
	 * types or larger size). Is also better to prepare a query knowing
	 * parameter types earlier.
	 */
	TDSPARAMINFO *params;
	/** saved query, we need to know original query if prepare is impossible */
	char *query;
} TDSDYNAMIC;

typedef enum {
	TDS_MULTIPLE_QUERY,
	TDS_MULTIPLE_EXECUTE,
	TDS_MULTIPLE_RPC
} TDS_MULTIPLE_TYPE;

typedef struct tds_multiple
{
	TDS_MULTIPLE_TYPE type;
	unsigned int flags;
} TDSMULTIPLE;

/* forward declaration */
typedef struct tds_context TDSCONTEXT;

struct tds_context
{
	TDSLOCALE *locale;
	void *parent;
	/* handlers */
	int (*msg_handler) (const TDSCONTEXT *, TDSSOCKET *, TDSMESSAGE *);
	int (*err_handler) (const TDSCONTEXT *, TDSSOCKET *, TDSMESSAGE *);
	int (*int_handler) (void *);
};

enum TDS_ICONV_ENTRY
{ 
	  client2ucs2
	, client2server_chardata
	, iso2server_metadata
	, initial_char_conv_count	/* keep last */
};

typedef struct tds_authentication
{
	TDS_UCHAR *packet;
	int packet_len;
	TDSRET (*free)(TDSCONNECTION* conn, struct tds_authentication * auth);
	TDSRET (*handle_next)(TDSSOCKET * tds, struct tds_authentication * auth, size_t len);
} TDSAUTHENTICATION;

typedef struct tds_packet
{
	struct tds_packet *next;
	short sid;
	unsigned len, capacity;
	unsigned char buf[1];
} TDSPACKET;

typedef struct tds_poll_wakeup
{
	TDS_SYS_SOCKET s_signal, s_signaled;
} TDSPOLLWAKEUP;


/* bulk.c */

/** bcp direction */
enum tds_bcp_directions
{
	TDS_BCP_IN = 1,
	TDS_BCP_OUT = 2,
	TDS_BCP_QUERYOUT = 3
};

struct tds_bcpinfo
{
	const char *hint;
	void *parent;
	DSTR tablename;
	TDS_CHAR *insert_stmt;
	TDS_INT direction;
	TDS_INT identity_insert_on;
	TDS_INT xfer_init;
	TDS_INT bind_count;
	TDSRESULTINFO *bindinfo;
};

#endif