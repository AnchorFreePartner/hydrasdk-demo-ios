#ifndef HYDRA_LOGLEVELS_H__
#define HYDRA_LOGLEVELS_H__

/*
 * Maximum supported log message size in bytes
 */
#define HYDRA_LOGMSG_MAXSIZE  8192

/*
 * Log levels and numbers are matched with syslog.h, except HLOG_NONE
 */
#define HYDRA_LOGLEVEL_NONE    -1   /* no log */
#define HYDRA_LOGLEVEL_EMERG    0   /* system is unusable */
#define HYDRA_LOGLEVEL_ALERT    1   /* action must be taken immediately */
#define HYDRA_LOGLEVEL_CRIT     2   /* critical conditions */
#define HYDRA_LOGLEVEL_ERR      3   /* error conditions */
#define HYDRA_LOGLEVEL_WARNING  4   /* warning conditions */
#define HYDRA_LOGLEVEL_NOTICE   5   /* normal but significant condition */
#define HYDRA_LOGLEVEL_INFO     6   /* informational */
#define HYDRA_LOGLEVEL_DBG      7   /* debug-level messages */

#endif /* HYDRA_LOGLEVELS_H__ */
