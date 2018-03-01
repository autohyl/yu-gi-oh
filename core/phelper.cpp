#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stropts.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <string>
#include <sstream>
#include "phelper.h"

using namespace std;
#define DICLEN 97
#include <iconv.h> 
#define OUTLEN 255 

int phelper::code_convert(char *from_charset,char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen) 
{ 
	iconv_t cd; 
	int rc; 
	char **pin = &inbuf; 
	char **pout = &outbuf; 

	cd = iconv_open(to_charset,from_charset); 
	if (cd==0) return -1; 
	memset(outbuf,0,outlen); 
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1) return -1; 
	iconv_close(cd); 
	return 0; 
} 
//UNICODE???GB2312? 
int phelper::u2g(char *inbuf,int inlen,char *outbuf,int outlen) 
{ 
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen); 
} 
//GB2312???UNICODE? 
int phelper::g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) 
{ 
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen); 
} 


string phelper::mem2hex(const char *pData, const unsigned uiDataLen, bool bCap)
{
	char pBuf[3] = {0};

	static char pUpperHex[20]="0123456789ABCDEF";
	static char pLowerHex[20]="0123456789abcdef";
	const char *pHex = NULL;
	if(bCap) {
		pHex = pUpperHex;
	}
	else {
		pHex = pLowerHex;
	}

	std::string strResult("");

	for(unsigned i=0; i<uiDataLen; i++) {
		unsigned char ucChar = pData[i];
		pBuf[0] = pHex[ucChar / 16];
		pBuf[1] = pHex[ucChar % 16];
		strResult += pBuf;
	}
	return strResult;
}

string phelper::mem2hex(const string &strData, bool bCap)
{
	return mem2hex(strData.data(), strData.size(), bCap);
}

string phelper::hex2mem(const char *pData, const unsigned uiDataLen)
{
	string strResult("");
	if (uiDataLen%2 != 0) {
		return strResult;
	}

	char szOneStr[3] = {0};
	for (unsigned i=0; i<(uiDataLen/2); i++) {
		memcpy(szOneStr, pData+2*i, 2);
		szOneStr[2] = '\0';
		strResult.push_back((char)strtol(szOneStr, NULL, 16));
	}

	return strResult;
}

string phelper::hex2mem(const string &strData)
{
	return hex2mem(strData.data(), strData.size());
}

char* phelper::get_local_ip_p()
{
      static char ip[20] = {0};
      int i;
      int s = socket(PF_INET, SOCK_STREAM, 0);

      for (i=1;;i++) {
          struct ifreq ifr;
          struct sockaddr_in *sin = (struct sockaddr_in *) &ifr.ifr_addr;

          ifr.ifr_ifindex = i;
          if (ioctl(s, SIOCGIFNAME, &ifr) < 0)
            break;

          /* now ifr.ifr_name is set */
          if (ioctl(s, SIOCGIFADDR, &ifr) < 0)
            continue;

         memset(ip, 0, sizeof(ip));
         strcpy(ip, inet_ntoa (sin->sin_addr));
         if(0==strncmp(ip, "172", 3) || 0==strncmp(ip, "192", 3) || 0==strncmp(ip, "10.", 3)) {
           close (s);
           return ip;
         }
         else
            continue;
      }

      close (s);
      return NULL;
}

int phelper::get_local_ip_p_by_eth(string main_eth,string& ip)
{
	char cmd_buf[1024] = { 0 };
	snprintf(cmd_buf, sizeof(cmd_buf), "/sbin/ifconfig %s | grep \"inet addr\"| awk '{print $2}' | awk -F: '{print $2}'",main_eth.c_str());
	
	FILE *sar_fp = popen(cmd_buf, "r");
	ip="";
	
	if (sar_fp != NULL)
	{
		char fps_buf[20];
		int nread = fread(fps_buf, 1, 20, sar_fp);
		if (nread > 0)
		{
		 	ip=fps_buf;
			ip=ip.substr(0,ip.length()-1);
		}
		pclose(sar_fp);
	}
	
	return 0;

}


unsigned phelper::get_local_ip_n()
{
	return inet_p2n(get_local_ip_p());
}

string phelper::inet_n2p(unsigned ipv4, string* p)
{
    char buf[INET_ADDRSTRLEN] = {0};
    struct in_addr in;
    in.s_addr = ipv4;

    inet_ntop(AF_INET, &in ,buf, sizeof(buf));

	if(p) {
		return p->assign(buf);
	}
	else {
		return string(buf);
	}
}


unsigned phelper::inet_p2n(const char* pAddr)
{
	in_addr in = {0};
	if(inet_pton(AF_INET, pAddr, &in) > 0) {
		return in.s_addr;
	}
	else
	{
		return 0;
	}

}

unsigned phelper::inet_p2n(const string& strAddr)
{
	return inet_p2n(strAddr.c_str());
}

void phelper::split_string(const string &str, vector<string>& vStrs, const char cDel)
{
    vStrs.clear();

    if(str.empty()) {
        return;
    }
    string tempStr = str;

	if(str[0] != cDel) {
		tempStr = cDel + tempStr;
	}

	if(str[str.size()-1] != cDel) {
		tempStr = tempStr + cDel;
	}

    vector<string>::size_type idxA=0, idxB=0;
    while(idxA != tempStr.size()-1) {
        idxB = idxA;
        idxA = tempStr.find(string(&cDel, 1), idxA+1);
        vStrs.push_back(tempStr.substr(idxB+1, idxA-idxB-1));
    }
}

void phelper::trim_string(string &target)
{
	if(target.empty()) {
		return;
	}

	while(target.at(0) == ' ') {
		target.erase(0, 1);
	}

	if(target.empty()) {
		return;
	}

	while(target.at(target.size() - 1) == ' ') {
		target.erase(target.size()-1, 1);
	}
}

string phelper::get_host_name()
 {
	char hname[128];
	gethostname(hname,sizeof(hname));
	
	 return string(hname);
 }

 int phelper::get_url_args(map<string, string> & url_args, string & url)
 {
	 size_t start_pos = 0;
	 size_t colon_pos = 0;
	 size_t equal_symbol = 0;
 
	 string name;
	 string value;
 
	 while((equal_symbol = url.find('=', start_pos)) != string::npos)
	 {
		 colon_pos = url.find('&', start_pos);
		 if(colon_pos == string::npos)
		 {
			 colon_pos = url.length();
 // 		 cookie_value = cookie_string.substr(equal_symbol + 1, cookie_string.length() - (equal_symbol + 1));
		 }
			 
		 value = url.substr(equal_symbol + 1, colon_pos - (equal_symbol + 1));
		 name = url.substr(start_pos, equal_symbol - start_pos);/*escape space*/
		 std::size_t and_pos = name.find("amp;");
		 if (and_pos != string::npos) {
				 name = name.substr(and_pos + 4);
		 }

		 and_pos = value.find(" ");
		  if (and_pos != string::npos) {
				 value = value.substr(0,and_pos);
		 }
 
		 //printf("name %s , value %s \n", name.c_str(),value.c_str());
		 
		 url_args.insert(std::map<string, string>::value_type(name, value));
		 start_pos = colon_pos + 1; 	 /*search start after the ';' symbol*/
		 if(start_pos >= url.length())
		 {
			 break;
		 }
	 }
 
	 return (0);
 
 }

unsigned int phelper::Dirhash(const char * key)
{//BKDRhash??
      unsigned int seed = 131;
      unsigned int hash = 0;

      while(*key != '\n' && *key != 0)      //?????,?????*key != 0??,???*key != '\n'????????
          hash = hash * seed + (*key++);

      return hash % DICLEN;
}

int phelper::is_file_exist(const char *path)
{
    errno = 0;
    int ret = access(path, R_OK);
    if (ret < 0 &&
            (errno == ENAMETOOLONG
             || errno == ENOTDIR
             || errno == ENOENT))
        return 0;
    else
        return 1;
}

int phelper::get_file_size(const char *path) 
{
	struct stat statbuf;
	if (stat(path, &statbuf) < 0)
		return 0;
	else
		return statbuf.st_size; 
}

int phelper::get_file_count(const char *path)
{
	DIR *dir;
	struct dirent *ptr;
	int total = 0;
	dir = opendir(path); /* 打开目录*/
	if(dir == NULL)
	{
		//perror("fail to open dir");
		//exit(1);
		return -1;
	}
	errno = 0;
	while((ptr = readdir(dir)) != NULL)
	{
		//顺序读取每一个目录项；
		//跳过“..”和“.”两个目录
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
		{
			continue;
		}
		//printf("%s%s/n",root,ptr->d_name);
		//如果是目录，则递归调用 get_file_count函数
		
		if(ptr->d_type == DT_DIR)
		{
			//sprintf(path,"%s%s/",root,ptr->d_name);
			//printf("%s/n",path);
			total += get_file_count(path);
		}
		
		if(ptr->d_type == DT_REG)
		{
			total++;
			//printf("%s%s/n",root,ptr->d_name);
		}
	}
	if(errno != 0)
	{
		//printf("fail to read dir");  //失败则输出提示信息
		//exit(1);
		return -1;
	}
	closedir(dir);
	return total;
}

