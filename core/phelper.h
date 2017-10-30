#ifndef _PHELPER_H_
#define _PHELPER_H_

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include <cstring>
#include <dirent.h>
using namespace std;


#define P_NOR(fmt, args...) fprintf(stdout, fmt, ##args);
#define P_ERR(fmt, args...) fprintf(stderr, fmt, ##args);

#define NTOHS(arg) arg=ntohs(arg)
#define NTOHL(arg) arg=ntohl(arg)
#define HTONS(arg) arg=htons(arg)
#define HTONL(arg) arg=htonl(arg)

namespace phelper
{

	template <typename T>
		inline void safe_del(T* &p)
		{
			if(p)
			{
				delete p;
				p = NULL;
			}
		}

	template <typename T>
		inline void safe_del_a(T* &p)
		{
			if(p)
			{
				delete []p;
				p = NULL;
			}
		}

	template <typename T>
		inline void safe_free(T *&t)
		{
			if(t)
			{
				free(t);
				t = NULL;
			}
			return;
		}

	inline void * safe_malloc(size_t s)
	{
		void *p = malloc(s);
		if(! p)
		{
			return NULL;
		}
		memset(p, 0x0, s);
		return p;
	}


	template <typename T>
		inline T from_str(const std::string &str)
		{
			std::istringstream is(str);
			T t;
			is >> t;
			return t;
		}

	template <typename T>
		inline std::string to_str(const T &t)
		{
			std::ostringstream os;
			os << t;
			return os.str();
		}

	//¼ÓÃÜ
	inline void encry(char* d,int l)
	{
		int k = l%5+1,x= 0,n = l/k+k;
		for(int j=0;j<n;j++)
		{
		for(int i=0;i<l;i++)
		{
			x = (i+k+l)%l;
			d[i] = d[i]^d[x];
		}
		}
	}
	
	//½âÃÜ
	inline void decry(char* d,int l)
	{
		int k = l%5+1,x= 0,n = l/k+k;
		for(int j=0;j<n;j++)
		{
		for(int i=l-1;i>=0;i--)
		{
			x = (i+k+l)%l;
			d[i] = d[i]^d[x];
		}
		}
	}

	//- Memory to hexadecimal string
	std::string mem2hex(const char *pData, const unsigned uiDataLen = 16, bool bCap = true);
	std::string mem2hex(const std::string &strData, bool bCap = true);

	// Hexadecimal  to memory
	std::string hex2mem(const char *pData, const unsigned uiDataLen = 16);
	std::string hex2mem(const std::string &strData);

	// Get local ip
	char *get_local_ip_p();

	// Get local ip
	unsigned get_local_ip_n();

	int get_local_ip_p_by_eth(string main_eth,string& ip);

	// Transform ipv4 to dot-form
	std::string inet_n2p(unsigned ipv4, std::string* p=NULL);

	// Transform ip in dot-form to ipv4
	unsigned inet_p2n(const char *pAddr);
	unsigned inet_p2n(const std::string& strAddr);

	// Split string to vector according to delimeter, vStrs will be cleared
	void split_string(const std::string &str, std::vector<std::string> &vStrs, const char cDel);

	// trim leading and tailing spaces of string
	void trim_string(std::string &target);

	std::string get_host_name();
	
	int get_url_args(map<string, string> & url_args, string & url);
	unsigned int Dirhash(const char * key);

	int u2g(char *inbuf,int inlen,char *outbuf,int outlen);
	int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
	int code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);

	int is_file_exist(const char *path);
	int get_file_size(const char *path);
	int get_file_count(const char *path);
}

#endif
