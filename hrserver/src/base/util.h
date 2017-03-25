#ifndef __UTIL_H__
#define __UTIL_H__

#define _CRT_SECURE_NO_DEPRECATE	// remove warning C4996, 
#include <cxxabi.h>
#include <execinfo.h>
#include <signal.h>
#include "ostype.h"
#include "UtilPdu.h"
#include "Lock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "slog/slog_api.h"
#ifndef _WIN32
#include <strings.h>
#endif

#include <sys/stat.h>
#include <assert.h>


#ifdef _WIN32
#define	snprintf	sprintf_s
#else
#include <stdarg.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#endif

#include "ImLog.h"

#define NOTUSED_ARG(v) ((void)v)		// used this to remove warning C4100, unreferenced parameter

/// yunfan modify end 
class CRefObject
{
public:
	CRefObject();
	virtual ~CRefObject();

	void SetLock(CLock* lock) { m_lock = lock; }
	void AddRef();
	void ReleaseRef();
	
	virtual void SetObjName(std::string name) { m_name = name; }
	virtual std::string& GetObjName() { return m_name; }
	virtual int GetRefCount() { return m_refCount; }
	
	
private:
	int		m_refCount;
	CLock*	m_lock;
	std::string m_name;
};

#include <exception>

class NetException : public std::exception
{
	std::string _why;
public:
	NetException(const char* why, ...);
	virtual const char* what() const throw() { return _why.c_str();	}
};
// #define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define netex(fmt, args...)  NetException(" %s:%d |<%s>," fmt, __FILE__, __LINE__, __FUNCTION__, ##args)

void str_split(string s, vector<string>& ret);
void str_split(string s, vector<string>& ret, char sep);

uint64_t get_tick_count();
void util_sleep(uint32_t millisecond);

class CStrExplode
{
public:
	CStrExplode(char* str, char seperator);
	virtual ~CStrExplode();

	uint32_t GetItemCnt() { return m_item_cnt; }
	char* GetItem(uint32_t idx) { return m_item_list[idx]; }
private:
	uint32_t	m_item_cnt;
	char** 		m_item_list;
};

char* replaceStr(char* pSrc, char oldChar, char newChar);
string int2string(uint32_t user_id);
uint32_t string2int(const string& value);
void replace_mark(string& str, string& new_value, uint32_t& begin_pos);
void replace_mark(string& str, uint32_t new_value, uint32_t& begin_pos);

void writePid();
inline unsigned char toHex(const unsigned char &x);
inline unsigned char fromHex(const unsigned char &x);
string URLEncode(const string &sIn);
string URLDecode(const string &sIn);


int64_t get_file_size(const char *path);
const char*  memfind(const char *src_str,size_t src_len, const char *sub_str, size_t sub_len, bool flag = true);
void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63);

void backup_core_file();
void daemon();
int daemon(int nochdir, int noclose, int asroot);
void will_be_daemon(int argc, char* argv[]);
void will_have_stacktrace();

#endif