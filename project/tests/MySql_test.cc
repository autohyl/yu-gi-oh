#include <stdio.h>
#include <mysql.h>
#include "../../database/cmysql.h"
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "6537127"
#define DATABASE "ScanPort"
 
void insert_sql(char * sql);
void query_sql(char* sql);
int main(int argc,char *argv[])
{
    //insert_sql("insert into test values('user','123456')");
    //query_sql("select * from IPAddress");
    CMysql mysql(HOST, USERNAME, PASSWORD, DATABASE);
    try {
        mysql.Query("select * from IPAddress");
        char** row = mysql.FetchRow();
        printf("row0 %s, row1 %s\n", row[0], row[1]);
    } catch (CMysqlException &e) {
        printf("error %s\n", e.GetErrMsg());
    }
    return 0;
}

void insert_sql(char * sql)
{
    MYSQL conn;
    int res;
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","","test",0,NULL,CLIENT_FOUND_ROWS))
    {
        printf("connect success!\n");
        res=mysql_query(&conn,sql);
        if(res)
        {
            printf("error\n");
        }
        else
        {
            printf("OK\n");
        }
        mysql_close(&conn);
    }

}

void query_sql(char* sql) 
{
    MYSQL my_connection; /*����һ�����ݿ�����*/
    int res; /*ִ��sql�Z���ķ��ر�־*/
    MYSQL_RES *res_ptr; /*ָ���ѯ�����ָ��*/
    MYSQL_FIELD *field; /*�ֶνṹָ��*/
    MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/

    int row, column; /*��ѯ���ص�����������*/
    int i, j; /*ֻ�ǿ���ѭ������������*/

    /*��ʼ��mysql����my_connection*/
    mysql_init(&my_connection);

    /*�����������mysql.h���һ��������������֮ǰ�������Щ�꽨��mysql���ӣ���
    *     ����һ��ֵ�����ز�Ϊ��֤�������ǳɹ���*/
    if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) 
    {
        /*���ӳɹ�*/
        printf("���ݿ��ѯquery_sql���ӳɹ���\n");
        /*��仰�����ò�ѯ����Ϊutf8������֧������*/
        mysql_query(&my_connection, "set names utf8");

        /*������仰������mysql_query������ִ�����Ǹոմ����sql�Z�䣬
        *         ��᷵��һ��intֵ�����Ϊ0��֤���Z��ִ�гɹ�*/
        res = mysql_query(&my_connection, sql);

        if (res) 
        { /*���ھʹ���ִ��ʧ����*/
            printf("Error�� mysql_query !\n");
            /*��Ҫ���˹ر�����*/
            mysql_close(&my_connection);
        }
        else 
        { 
            /*���ھʹ���ִ�гɹ���*/
            /*����ѯ�ĽY����res_ptr*/
            res_ptr = mysql_store_result(&my_connection);

            /*��������Ϊ�գ��Ͱѽ��print*/
            if (res_ptr) 
            {
                /*ȡ�ýY����������*/
                column = mysql_num_fields(res_ptr);
                row = mysql_num_rows(res_ptr) + 1;
                printf("��ѯ�� %lu �� \n", row);

                /*����Y�����ֶ���*/
                for (i = 0; field = mysql_fetch_field(res_ptr); i++)
                    printf("%s\t", field->name);
                printf("\n");

                /*��������Y��*/
                for (i = 1; i < row; i++)
                {
                    result_row = mysql_fetch_row(res_ptr);
                    for (j = 0; j < column; j++)
                    printf("%s\t", result_row[j]);
                    printf("\n");  
                }  

            }  

            /*��Ҫ���˹ر�����*/  
            mysql_close(&my_connection);  
        }  
    }  
} 
