#include <libmemcached/memcached.h>
#include <iostream>
using namespace std;

int main() {
    memcached_st *memc = NULL;   
    memcached_return rc;   
    memcached_server_st *servers = NULL;   
    
    //connect multi server   
    memc = memcached_create(NULL);   

    //servers = memcached_server_list_append(NULL, (char*)"localhost", 11211, &rc);   
    servers = memcached_server_list_append(servers, (char*)"localhost", 12000, &rc);
    
    rc = memcached_server_push(memc, servers);  

    if (MEMCACHED_SUCCESS != rc) {  
        cout <<"memcached_server_push failed! rc: " << rc << endl;  
    }  

    memcached_server_list_free(servers);    
    
    /**
    memcached_behavior_set(memc,MEMCACHED_BEHAVIOR_DISTRIBUTION,MEMCACHED_DISTRIBUTION_CONSISTENT);  
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_RETRY_TIMEOUT, 20) ;  
    //  memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_REMOVE_FAILED_SERVERS, 1) ;  // 同时设置MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT 和 MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS  
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT, 5) ;  
    memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS, true) ;  */
    
    //cout << "-------------------" << endl;
    //save data   
    const char  *keys[]= {"key1", "key2", "key3","key4"};   
    const  size_t key_length[]= {4, 4, 4, 4};   
    char *values[] = {"This is 1 first value", "This is 2 second value", "This is 3 third value"," this is 4 forth value"};   
    size_t val_length[]= {21, 22, 21, 22};  
      
    for (int i = 0; i < 4; i++)        
    {  
        rc = memcached_set(memc, keys[i], key_length[i], values[i], val_length[i], (time_t)180,(uint32_t)0);     
        printf("key: %s  rc:%s\n", keys[i], memcached_strerror(memc, rc));   // 输出状态        
    }

    uint32_t flags = 0;
    const char* key = "key1";
    size_t value_length;  
    char* value = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);  

    // get ok  
    if(rc == MEMCACHED_SUCCESS)  
    {    
        cout << value << endl;  
    }  

    //free   
    memcached_free(memc);   
    return 0;
}