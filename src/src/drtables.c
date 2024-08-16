/*************************************************
*     Exim - an Internet mail transport agent    *
*************************************************/

/* Copyright (c) The Exim Maintainers 2020 - 2024 */
/* Copyright (c) University of Cambridge 1995 - 2018 */
/* See the file NOTICE for conditions of use and distribution. */
/* SPDX-License-Identifier: GPL-2.0-or-later */


#include "exim.h"

#include <string.h>

/* This module contains tables that define the lookup methods and drivers
that are actually included in the binary. Its contents are controlled by
various macros in config.h that ultimately come from Local/Makefile. They are
all described in src/EDITME. */


lookup_info **lookup_list;
int lookup_list_count = 0;

/* Lists of information about which drivers are included in the exim binary. */

auth_info * auths_available= NULL;
router_info * routers_available = NULL;
transport_info * transports_available = NULL;



#ifndef MACRO_PREDEF

gstring *
auth_show_supported(gstring * g)
{
uschar * b = US""               /* static-build authenticatornames */
#if defined(AUTH_CRAM_MD5) && AUTH_CRAM_MD5!=2
  " cram_md5"
#endif
#if defined(AUTH_CYRUS_SASL) && AUTH_CYRUS_SASL!=2
  " cyrus_sasl"
#endif
#if defined(AUTH_DOVECOT) && AUTH_DOVECOT!=2
  " dovecot"
#endif
#if defined(AUTH_EXTERNAL) && AUTH_EXTERNAL!=2
  " external"
#endif
#if defined(AUTH_GSASL) && AUTH_GSASL!=2
  " gsasl"
#endif
#if defined(AUTH_HEIMDAL_GSSAPI) && AUTH_HEIMDAL_GSSAPI!=2
  " heimdal_gssapi"
#endif
#if defined(AUTH_PLAINTEXT) && AUTH_PLAINTEXT!=2
  " plaintext"
#endif
#if defined(AUTH_SPA) && AUTH_SPA!=2
  " spa"
#endif
#if defined(AUTH_TLS) && AUTH_TLS!=2
  " tls"
#endif
  ;

uschar * d = US""		/* dynamic-module authenticator names */
#if defined(AUTH_CRAM_MD5) && AUTH_CRAM_MD5==2
  " cram_md5"
#endif
#if defined(AUTH_CYRUS_SASL) && AUTH_CYRUS_SASL==2
  " cyrus_sasl"
#endif
#if defined(AUTH_DOVECOT) && AUTH_DOVECOT==2
  " dovecot"
#endif
#if defined(AUTH_EXTERNAL) && AUTH_EXTERNAL==2
  " external"
#endif
#if defined(AUTH_GSASL) && AUTH_GSASL==2
  " gsasl"
#endif
#if defined(AUTH_HEIMDAL_GSSAPI) && AUTH_HEIMDAL_GSSAPI==2
  " heimdal_gssapi"
#endif
#if defined(AUTH_PLAINTEXT) && AUTH_PLAINTEXT==2
  " plaintext"
#endif
#if defined(AUTH_SPA) && AUTH_SPA==2
  " spa"
#endif
#if defined(AUTH_TLS) && AUTH_TLS==2
  " tls"
#endif
  ;

if (*b) g = string_fmt_append(g, "Authenticators (built-in):%s\n", b);
if (*d) g = string_fmt_append(g, "Authenticators (dynamic): %s\n", d);
return g;
}

gstring *
route_show_supported(gstring * g)
{
uschar * b = US""		/* static-build router names */
#if defined(ROUTER_ACCEPT) && ROUTER_ACCEPT!=2
  " accept"
#endif
#if defined(ROUTER_DNSLOOKUP) && ROUTER_DNSLOOKUP!=2
  " dnslookup"
#endif
# if defined(ROUTER_IPLITERAL) && ROUTER_IPLITERAL!=2
  " ipliteral"
#endif
#if defined(ROUTER_IPLOOKUP) && ROUTER_IPLOOKUP!=2
  " iplookup"
#endif
#if defined(ROUTER_MANUALROUTE) && ROUTER_MANUALROUTE!=2
  " manualroute"
#endif
#if defined(ROUTER_REDIRECT) && ROUTER_REDIRECT!=2
  " redirect"
#endif
#if defined(ROUTER_QUERYPROGRAM) && ROUTER_QUERYPROGRAM!=2
  " queryprogram"
#endif
  ;

uschar * d = US""		/* dynamic-module router names */
#if defined(ROUTER_ACCEPT) && ROUTER_ACCEPT==2
  " accept"
#endif
#if defined(ROUTER_DNSLOOKUP) && ROUTER_DNSLOOKUP==2
  " dnslookup"
#endif
# if defined(ROUTER_IPLITERAL) && ROUTER_IPLITERAL==2
  " ipliteral"
#endif
#if defined(ROUTER_IPLOOKUP) && ROUTER_IPLOOKUP==2
  " iplookup"
#endif
#if defined(ROUTER_MANUALROUTE) && ROUTER_MANUALROUTE==2
  " manualroute"
#endif
#if defined(ROUTER_REDIRECT) && ROUTER_REDIRECT==2
  " redirect"
#endif
#if defined(ROUTER_QUERYPROGRAM) && ROUTER_QUERYPROGRAM==2
  " queryprogram"
#endif
  ;

if (*b) g = string_fmt_append(g, "Routers (built-in):%s\n", b);
if (*d) g = string_fmt_append(g, "Routers (dynamic): %s\n", d);
return g;
}

gstring *
transport_show_supported(gstring * g)
{
uschar * b = US""		/* static-build transportnames */
#if defined(TRANSPORT_APPENDFILE) && TRANSPORT_APPENDFILE!=2
  " appendfile"
# ifdef SUPPORT_MAILDIR
    "/maildir"
# endif
# ifdef SUPPORT_MAILSTORE
    "/mailstore"
# endif
# ifdef SUPPORT_MBX
    "/mbx"
# endif
#endif
#if defined(TRANSPORT_AUTOREPLY) && TRANSPORT_AUTOREPLY!=2
  " autoreply"
#endif
#if defined(TRANSPORT_LMTP) && TRANSPORT_LMTP!=2
  " lmtp"
#endif
#if defined(TRANSPORT_PIPE) && TRANSPORT_PIPE!=2
  " pipe"
#endif
#if defined(EXPERIMENTAL_QUEUEFILE) && EXPERIMENTAL_QUEUEFILE!=2
  " queuefile"
#endif
#if defined(TRANSPORT_SMTP) && TRANSPORT_SMTP!=2
  " smtp"
#endif
  ;

uschar * d = US""		/* dynamic-module transportnames */
#if defined(TRANSPORT_APPENDFILE) && TRANSPORT_APPENDFILE==2
  " appendfile"
# ifdef SUPPORT_MAILDIR
    "/maildir"
# endif
# ifdef SUPPORT_MAILSTORE
    "/mailstore"
# endif
# ifdef SUPPORT_MBX
    "/mbx"
# endif
#endif
#if defined(TRANSPORT_AUTOREPLY) && TRANSPORT_AUTOREPLY==2
  " autoreply"
#endif
#if defined(TRANSPORT_LMTP) && TRANSPORT_LMTP==2
  " lmtp"
#endif
#if defined(TRANSPORT_PIPE) && TRANSPORT_PIPE==2
  " pipe"
#endif
#if defined(EXPERIMENTAL_QUEUEFILE) && EXPERIMENTAL_QUEUEFILE==2
  " queuefile"
#endif
#if defined(TRANSPORT_SMTP) && TRANSPORT_SMTP==2
  " smtp"
#endif
  ;

if (*b) g = string_fmt_append(g, "Transports (built-in):%s\n", b);
if (*d) g = string_fmt_append(g, "Transports (dynamic): %s\n", d);
return g;
}



struct lookupmodulestr
{
  void *dl;
  struct lookup_module_info *info;
  struct lookupmodulestr *next;
};

static struct lookupmodulestr *lookupmodules = NULL;

static void
addlookupmodule(void *dl, struct lookup_module_info *info)
{
struct lookupmodulestr * p =
  store_get(sizeof(struct lookupmodulestr), GET_UNTAINTED);

p->dl = dl;
p->info = info;
p->next = lookupmodules;
lookupmodules = p;
lookup_list_count += info->lookupcount;
}

/* only valid after lookup_list and lookup_list_count are assigned */
static void
add_lookup_to_list(lookup_info *info)
{
/* need to add the lookup to lookup_list, sorted */
int pos = 0;

/* strategy is to go through the list until we find
either an empty spot or a name that is higher.
this can't fail because we have enough space. */

while (lookup_list[pos] && (Ustrcmp(lookup_list[pos]->name, info->name) <= 0))
  pos++;

if (lookup_list[pos])
  {
  /* need to insert it, so move all the other items up
  (last slot is still empty, of course) */

  memmove(&lookup_list[pos+1], &lookup_list[pos],
	  sizeof(lookup_info *) * (lookup_list_count-pos-1));
  }
lookup_list[pos] = info;
}


/* These need to be at file level for old versions of gcc (2.95.2 reported),
which give parse errors on an extern in function scope.  Each entry needs
to also be invoked in init_lookup_list() below  */

#if defined(LOOKUP_CDB) && LOOKUP_CDB!=2
extern lookup_module_info cdb_lookup_module_info;
#endif
#if defined(LOOKUP_DBM) && LOOKUP_DBM!=2
extern lookup_module_info dbmdb_lookup_module_info;
#endif
#if defined(LOOKUP_DNSDB) && LOOKUP_DNSDB!=2
extern lookup_module_info dnsdb_lookup_module_info;
#endif
#if defined(LOOKUP_DSEARCH) && LOOKUP_DSEARCH!=2
extern lookup_module_info dsearch_lookup_module_info;
#endif
#if defined(LOOKUP_IBASE) && LOOKUP_IBASE!=2
extern lookup_module_info ibase_lookup_module_info;
#endif
#if defined(LOOKUP_JSON) && LOOKUP_JSON!=2
extern lookup_module_info json_lookup_module_info;
#endif
#if defined(LOOKUP_LDAP)
extern lookup_module_info ldap_lookup_module_info;
#endif
#if defined(LOOKUP_LSEARCH) && LOOKUP_LSEARCH!=2
extern lookup_module_info lsearch_lookup_module_info;
#endif
#if defined(LOOKUP_MYSQL) && LOOKUP_MYSQL!=2
extern lookup_module_info mysql_lookup_module_info;
#endif
#if defined(LOOKUP_NIS) && LOOKUP_NIS!=2
extern lookup_module_info nis_lookup_module_info;
#endif
#if defined(LOOKUP_NISPLUS) && LOOKUP_NISPLUS!=2
extern lookup_module_info nisplus_lookup_module_info;
#endif
#if defined(LOOKUP_ORACLE) && LOOKUP_ORACLE!=2
extern lookup_module_info oracle_lookup_module_info;
#endif
#if defined(LOOKUP_PASSWD) && LOOKUP_PASSWD!=2
extern lookup_module_info passwd_lookup_module_info;
#endif
#if defined(LOOKUP_PGSQL) && LOOKUP_PGSQL!=2
extern lookup_module_info pgsql_lookup_module_info;
#endif
#if defined(LOOKUP_REDIS) && LOOKUP_REDIS!=2
extern lookup_module_info redis_lookup_module_info;
#endif
#if defined(LOOKUP_LMDB)
extern lookup_module_info lmdb_lookup_module_info;
#endif
#if defined(SUPPORT_SPF)
extern lookup_module_info spf_lookup_module_info;
#endif
#if defined(LOOKUP_SQLITE) && LOOKUP_SQLITE!=2
extern lookup_module_info sqlite_lookup_module_info;
#endif
#if defined(LOOKUP_TESTDB) && LOOKUP_TESTDB!=2
extern lookup_module_info testdb_lookup_module_info;
#endif
#if defined(LOOKUP_WHOSON) && LOOKUP_WHOSON!=2
extern lookup_module_info whoson_lookup_module_info;
#endif

extern lookup_module_info readsock_lookup_module_info;


void
init_lookup_list(void)
{
#ifdef LOOKUP_MODULE_DIR
DIR * dd;
struct dirent * ent;
int countmodules = 0;
int moduleerrors = 0;
#endif
static BOOL lookup_list_init_done = FALSE;
rmark reset_point;

if (lookup_list_init_done)
  return;
reset_point = store_mark();
lookup_list_init_done = TRUE;

#if defined(LOOKUP_CDB) && LOOKUP_CDB!=2
addlookupmodule(NULL, &cdb_lookup_module_info);
#endif

#if defined(LOOKUP_DBM) && LOOKUP_DBM!=2
addlookupmodule(NULL, &dbmdb_lookup_module_info);
#endif

#if defined(LOOKUP_DNSDB) && LOOKUP_DNSDB!=2
addlookupmodule(NULL, &dnsdb_lookup_module_info);
#endif

#if defined(LOOKUP_DSEARCH) && LOOKUP_DSEARCH!=2
addlookupmodule(NULL, &dsearch_lookup_module_info);
#endif

#if defined(LOOKUP_IBASE) && LOOKUP_IBASE!=2
addlookupmodule(NULL, &ibase_lookup_module_info);
#endif

#ifdef LOOKUP_LDAP
addlookupmodule(NULL, &ldap_lookup_module_info);
#endif

#if defined(LOOKUP_JSON) && LOOKUP_JSON!=2
addlookupmodule(NULL, &json_lookup_module_info);
#endif

#if defined(LOOKUP_LSEARCH) && LOOKUP_LSEARCH!=2
addlookupmodule(NULL, &lsearch_lookup_module_info);
#endif

#if defined(LOOKUP_MYSQL) && LOOKUP_MYSQL!=2
addlookupmodule(NULL, &mysql_lookup_module_info);
#endif

#if defined(LOOKUP_NIS) && LOOKUP_NIS!=2
addlookupmodule(NULL, &nis_lookup_module_info);
#endif

#if defined(LOOKUP_NISPLUS) && LOOKUP_NISPLUS!=2
addlookupmodule(NULL, &nisplus_lookup_module_info);
#endif

#if defined(LOOKUP_ORACLE) && LOOKUP_ORACLE!=2
addlookupmodule(NULL, &oracle_lookup_module_info);
#endif

#if defined(LOOKUP_PASSWD) && LOOKUP_PASSWD!=2
addlookupmodule(NULL, &passwd_lookup_module_info);
#endif

#if defined(LOOKUP_PGSQL) && LOOKUP_PGSQL!=2
addlookupmodule(NULL, &pgsql_lookup_module_info);
#endif

#if defined(LOOKUP_REDIS) && LOOKUP_REDIS!=2
addlookupmodule(NULL, &redis_lookup_module_info);
#endif

#ifdef LOOKUP_LMDB
addlookupmodule(NULL, &lmdb_lookup_module_info);
#endif

#ifdef SUPPORT_SPF
addlookupmodule(NULL, &spf_lookup_module_info);
#endif

#if defined(LOOKUP_SQLITE) && LOOKUP_SQLITE!=2
addlookupmodule(NULL, &sqlite_lookup_module_info);
#endif

#if defined(LOOKUP_TESTDB) && LOOKUP_TESTDB!=2
addlookupmodule(NULL, &testdb_lookup_module_info);
#endif

#if defined(LOOKUP_WHOSON) && LOOKUP_WHOSON!=2
addlookupmodule(NULL, &whoson_lookup_module_info);
#endif

/* This is a custom expansion, and not available as either
a list-syntax lookup or a lookup expansion. However, it is
implemented by a lookup module. */

addlookupmodule(NULL, &readsock_lookup_module_info);

#ifdef LOOKUP_MODULE_DIR
if (!(dd = exim_opendir(CUS LOOKUP_MODULE_DIR)))
  {
  DEBUG(D_lookup) debug_printf("Couldn't open %s: not loading lookup modules\n", LOOKUP_MODULE_DIR);
  log_write(0, LOG_MAIN|LOG_PANIC,
	  "Couldn't open %s: not loading lookup modules\n", LOOKUP_MODULE_DIR);
  }
else
  {
  const pcre2_code * regex_islookupmod = regex_must_compile(
    US"_lookup\\." DYNLIB_FN_EXT "$", MCS_NOFLAGS, TRUE);

  DEBUG(D_lookup) debug_printf("Loading lookup modules from %s\n", LOOKUP_MODULE_DIR);
  while ((ent = readdir(dd)))
    {
    char * name = ent->d_name;
    int len = (int)strlen(name);
    if (regex_match(regex_islookupmod, US name, len, NULL))
      {
      int pathnamelen = len + (int)strlen(LOOKUP_MODULE_DIR) + 2;
      void *dl;
      struct lookup_module_info *info;
      const char *errormsg;

      /* SRH: am I being paranoid here or what? */
      if (pathnamelen > big_buffer_size)
	{
	fprintf(stderr, "Loading lookup modules: %s/%s: name too long\n", LOOKUP_MODULE_DIR, name);
	log_write(0, LOG_MAIN|LOG_PANIC, "%s/%s: name too long\n", LOOKUP_MODULE_DIR, name);
	continue;
	}

      /* SRH: snprintf here? */
      sprintf(CS big_buffer, "%s/%s", LOOKUP_MODULE_DIR, name);

      if (!(dl = dlopen(CS big_buffer, RTLD_NOW)))
	{
	errormsg = dlerror();
	fprintf(stderr, "Error loading %s: %s\n", name, errormsg);
	log_write(0, LOG_MAIN|LOG_PANIC, "Error loading lookup module %s: %s\n", name, errormsg);
	moduleerrors++;
	continue;
	}

      /* FreeBSD nsdispatch() can trigger dlerror() errors about
      _nss_cache_cycle_prevention_function; we need to clear the dlerror()
      state before calling dlsym(), so that any error afterwards only comes
      from dlsym().  */

      errormsg = dlerror();

      info = (struct lookup_module_info*) dlsym(dl, "_lookup_module_info");
      if ((errormsg = dlerror()))
	{
	fprintf(stderr, "%s does not appear to be a lookup module (%s)\n", name, errormsg);
	log_write(0, LOG_MAIN|LOG_PANIC, "%s does not appear to be a lookup module (%s)\n", name, errormsg);
	dlclose(dl);
	moduleerrors++;
	continue;
	}
      if (info->magic != LOOKUP_MODULE_INFO_MAGIC)
	{
	fprintf(stderr, "Lookup module %s is not compatible with this version of Exim\n", name);
	log_write(0, LOG_MAIN|LOG_PANIC, "Lookup module %s is not compatible with this version of Exim\n", name);
	dlclose(dl);
	moduleerrors++;
	continue;
	}

      addlookupmodule(dl, info);
      DEBUG(D_lookup) debug_printf("Loaded \"%s\" (%d lookup types)\n", name, info->lookupcount);
      countmodules++;
      }
    }
  store_free((void*)regex_islookupmod);
  closedir(dd);
  }

DEBUG(D_lookup) debug_printf("Loaded %d lookup modules\n", countmodules);
#endif

DEBUG(D_lookup) debug_printf("Total %d lookups\n", lookup_list_count);

lookup_list = store_malloc(sizeof(lookup_info *) * lookup_list_count);
memset(lookup_list, 0, sizeof(lookup_info *) * lookup_list_count);

/* now add all lookups to the real list */
for (struct lookupmodulestr * p = lookupmodules; p; p = p->next)
  for (int j = 0; j < p->info->lookupcount; j++)
    add_lookup_to_list(p->info->lookups[j]);
store_reset(reset_point);
/* just to be sure */
lookupmodules = NULL;
}

#endif	/*!MACRO_PREDEF*/
/* End of drtables.c */
