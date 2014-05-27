#pragma once
#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <mysql.h>
#include <iostream>
#include <assert.h>

typedef __int64_t   db_int64;
typedef __int32_t   db_int32;
typedef __int16_t   db_int16;
typedef __int8_t    db_int8;
typedef __uint64_t  db_uint64;
typedef __uint32_t  db_uint32;
typedef __uint16_t  db_uint16;
typedef __uint8_t   db_uint8;
typedef db_uint16   db_WORD;
typedef db_uint32   db_DWORD;

const db_uint16 MAX_DB_CONNECT_COUNT = 100;       /// 每个连接最大的连接数

const db_uint8 MAX_DB_HOST_NAME_LEN = 255;
const db_uint8 MAX_DB_USE_NAME_LEN = 255;
const db_uint8 MAX_DB_PASSWD_LEN = 255;
const db_uint8 MAX_DB_DB_LEN = 255;

const db_uint16 MAX_PATH_MYSQL = 1024;

const db_uint16 SQL_STR_LEN =  2048;
const db_uint16 W_SQL_STR_LEN =  4096;

typedef db_uint8 DB_THREAD_ID; 

#define MAX_DBTHREAD_WRITE_NUM 1
#define MAX_DBTHREAD_READ_NUM 10

#define MAX_DBTHREAD_NUM (MAX_DBTHREAD_WRITE_NUM+MAX_DBTHREAD_READ_NUM)


#define DB_READ HREAD_ID (DB HREAD_ID)(accountID % SPLIT_ACCOUNT_BIT % MAX_DBTHREAD_READ_NUM)

#define INVAILD_LOAD_DB -1

#define PRINTFERROR() fprintf(stderr,"PRINTFERROR", ("%s(%d)-%s: error.\n"), __FILE__,__LINE__,__FUNCTION__);
#define MYSQLERROR(mysql)  fprintf(stderr, ("MYSQLERROR"), ("%s(%d)-%s: %s error.\n"), __FILE__,__LINE__,__FUNCTION__, mysql_error(mysql));
#define MYSQLERROR_SQL(mysql,sql)  fprintf(stderr, ("MYSQLERROR_SQL"), ("%s(%d)-%s: %s error.sql:%s\n"), __FILE__,__LINE__,__FUNCTION__, mysql_error(mysql), sql);
#define MYSQLSTMTERROR(stmt)  fprintf(stderr, ("MYSQLSTMTERROR"), ("%s(%d)-%s: %s error.\n"), __FILE__,__LINE__,__FUNCTION__, mysql_stmt_error(stmt));
#define MYSQLSTMTERROR_SQL(stmt,sql)  fprintf(stderr, ("MYSQLSTMTERROR_SQL"), ("%s(%d)-%s: %s error.sql:%s\n"), __FILE__,__LINE__,__FUNCTION__, mysql_stmt_error(stmt), sql);
