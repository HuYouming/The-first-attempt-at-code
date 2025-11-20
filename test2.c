#include <stdio.h>
#include <stdlib.h>
#include <string.h>


    struct Key
    {
        char name[12];
        char value[12];
    };            //定义一个结构体，然后就可以把键名和对应的内容联系在一起

    struct Key key[100];//不知道究竟有多少个键，干脆先定义一个100
    char temp[100];//定义一个临时字符数组装获取到的字符
    char c ;//临时变量存储fgetc获取到的字符
    char choose[12];//用户选择
    int key_count = 0;//键数目  记录键的顺序（个数）  记录键值个数
    int i = 0;//已经存储进temp中的的字符数(name模式)
    int j = 0;//已经存储进temp中的的字符数(value模式)
    int flag = 0;//表示获取状态
    int command;//记录用户输入的指令

/*
定义一个查找函数来查找用户输入的键名是否存在并返回索引
*/

int search(char choose[12], struct Key key[100], int key_count)
{
    for(int i = 0; i < key_count; i++)
    {
        if(strcmp(choose, key[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}


int main()
{
    system("chcp 65001 > nul");//设置终端编码为UTF-8
    FILE* data = fopen("data.txt","r"); //打开文件，只读模式

    if(data == NULL)
    {
        printf("Failed to open the file\n");
        return 1;
    }

    while((c = fgetc(data)) != EOF)
    {
        if(c == ':')
        {
            temp[i] = '\0';//获取到英文冒号后在字符数组最后加上结束符，相当于拼了一个字符串
            
            strcpy(key[key_count].name, temp);//将临时字符数组内容copy到key的name里面

            i = 0;//从0开始，将之前的temp里面的内容覆盖

            flag = 1;//进入获取键内容的模式
        }
        if(flag == 1)//对模式进行判断,进入获取键值模式
        {
            while((c = fgetc(data)) != '\n')//在碰到换行之前都要一直获取键值
            {
                if(c == EOF)//如果是最后一行，就碰不到换行而是结束符
                {
                    break;//全部结束，跳出内循环
                }
                temp[j] = c;
                j ++;
            }

            //其实这里处理的是最后一行的键值
            if(c == EOF)//判断是否为结束符，然后将获取到的字符键值赋值到字符串
            {
                temp[j] = '\0';
                strcpy(key[key_count].value, temp);

                key_count ++;
                j = 0;
 
                break;
            }
            //这里是对非最后行的键值进行赋值
            temp[j] = '\0';
            strcpy(key[key_count].value, temp);

            key_count ++; //移动索引
            j = 0;
 
            flag = 0;
        }
        if(c == '\n')
        {
            i = 0;//神之一手，解决错行问题。原理：如果没有碰到':',却碰到了换行，直接初始化临时字符c
            continue;//在获取完键值后可能会碰到连续空行
        }
    
        temp[i] = c;
        i ++;
    }

    printf("There are %d pairs of key-value pairs.\n",key_count);//查看究竟有多少对键值对

    while(1)
    {
       printf("Please input the key:");
       scanf("%s",choose);

       if(strcmp(choose, "Quit") == 0) //退出
       {
           break;
       }

       command = search(choose, key, key_count); //调用查找函数
 
       if(command != -1)
       {
           printf("%s\n",key[command].value);
       }
       else
       {
           printf("Error!Key name does't exist!\n");
       }
    }



    fclose(data); //别忘了关闭文件

    return 0;
}

