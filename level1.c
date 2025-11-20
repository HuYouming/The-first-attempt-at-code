#include <stdio.h>
#include <string.h>
#include <ctype.h>

    char User_name[10];//用户名
    char Login[10];//登录判断
    char Date[12];//字符串星期
    int menu_select;//菜单选择
    int Floor;//楼层
    int d;//数字星期
    int count = 0;//记录成功预约次数，同时也可以作为座位初始化函数是否进行的判断依据
    int flag0 = 0;
    int flag1 = 1;
    int flag2 = 1;

    char seat[7][5][4][4]; //全部座位   //注意！！！这里是字符类型不是字符串，占位符不要用错
    

int convert(char Date [12],char* Date_English[7]);
char* Date_English [7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
void Check();
int Reserve();
void Initializa();
char* Date_Translate(int d,char* Date_English[7]);
void checkmyself();
void SaveData();
int LoadData();
void Clear();
void User_menu();
void Admin_menu();
void Loginf();

int main()
{
   //进行座位初始化
    Initializa();

   //加载原来保存的数据
    LoadData();

   //登录系统，可以用用户名来记录预约状态
   while(1)
   {
    if (flag1 == 1)
    {
    Loginf();
    if(flag2 == 0)
    {
        return 0;
    }
 //登录成功后进入菜单系统
    flag1 = 0;
    
    if(strcmp(User_name,"Admin") == 0)
    {
        Admin_menu();
    }
    else
    {
        User_menu();
    }
    }
    break;
   }
    return 0;
}
//座位初始化函数
void Initializa()
{
    if(count == 0)
    {
        memset(seat, '0', sizeof(seat));
    }
}


 //查询系统函数
void Check()
{
    int r,c;
    printf("Please enter the date and the floor you want to check:");
    while(getchar() != '\n'); 
    scanf("%s Floor %d",Date,&Floor); //Floor是整型，需要加 &
    d = convert(Date,Date_English); 

    char seat_1[4][4] = {0};

    for(r = 0; r < 4; r++)
    {
        for(c = 0; c < 4; c++)
        {
            seat_1[r][c] = seat[d][Floor - 1][r][c];
        }
    }

    for(r = 0; r < 4; r++)
    {
        for(c = 0; c < 4; c++)
        {
            if(User_name != "Admin")
            {
            if(seat_1[r][c] == User_name[0])
            {
                printf("2 "); //Floor记得要 - 1，因为用户输入的是真实楼层
            }
            else if(seat_1[r][c] >= 'A' && seat_1[r][c] <= 'Z')
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
            }
        }

        printf("\n");
    }
}
    
//预约函数
int Reserve()
{
    int r,c;

    printf("Please type your reservation as the example\n'Reserve Monday Floor 1 Seat 1 2'\n");
    while(getchar() != '\n'); 
    scanf("Reserve %s Floor %d Seat %d %d",Date,&Floor,&r,&c);
    d = convert(Date,Date_English); 

    if(seat[d][Floor - 1][r - 1][c - 1] != '0')//判断位置是否还空余
    {
        return 1;
    }

    seat[d][Floor - 1][r - 1][c - 1] = User_name[0];
    count++;
    return 0;
}
//查看自己的预约
void checkmyself()
{
    for(int d = 0; d < 7; d++)
        {
            for(int f = 0; f < 5; f++)
            {
                for(int r = 0; r < 4; r++)
                {
                    for(int c = 0; c < 4; c++)
                    {
                        if(seat[d][f][r][c] == User_name[0])
                        {
                            printf("%s Floor %d Seat %d %d\n",Date_Translate(d,Date_English), f + 1, r + 1, c + 1);
                            flag0  = 1;
                        }
                    }
                }
            }
        }

        if(flag0 == 0)
        {
            printf("You haven't made a reservation yet.\n");
        }
}


//日期映射函数 1（将字符串映射成数字，方便检索）
int convert(char Date [12],char* Date_English[7])
{
    for(d = 0; d < 7; d++)
    {
        if(strcmp(Date,Date_English[d]) == 0)
        {
            return d;
        }
    }
    return -1;
}
//日期映射函数 2（将数字映射成字符串）
char* Date_Translate(int d,char* Date_English[7])
{
    return Date_English[d];
}

//保存进度函数，实质是保存座位
void SaveData()
{
    FILE* file = fopen("seat_data","wb");

    size_t num = fwrite(seat, sizeof(seat), 1, file);

    fclose(file);

    if(num == 1)
    {
        printf("Success!\n");
    }
    else
    {
        printf("Error!Please check yuor error.\n");
    }
}

//读取进度函数
int LoadData()
{
    FILE* file = fopen("seat_data","rb");

    if(file == NULL)
    {
        printf("欢迎使用图书馆预约系统！\n");

        return 0;
    }

    else
    {
    size_t num = fread(seat, sizeof(seat), 1, file);
    }

    fclose(file);

    return 0;

}

//清除用户数据
void Clear()
{

    printf("已清除所有数据\n");
    FILE* file = fopen("seat_data","wb");

    Initializa();

    size_t num = fwrite(seat, sizeof(seat), 1, file);

    fclose(file);

}

//管理员菜单
void Admin_menu()
{
    printf("已进入管理员模式\n");
    while(1)
    {
    printf("Please select a command from the menu\n1. Check for available seats\n2. Reserve seat\n3. Check your reservation\n4. Exit logining\n5. Quit\n6. Clear all data\n");
    while(getchar() != '\n'); 
    scanf("%d",&menu_select);
    
    switch(menu_select)
      {
        case 1://Check for available seats
        Check();
        break;

        case 2://Reserve seat
        while(1)
        {
           int flag = Reserve();
           if(flag == 1)
           {
               printf("This seat is not available!\n");
               continue;
           }
           printf("OK!\n");

           break;
        }
        break;

        case 3://Check your reservation
        checkmyself();
        break;

        case 4:
        flag1 = 1;
        break;

        case 5:
        SaveData();
        return ;

        case 6:
        Clear();
        break;
        return ;

     }
    }
}

//用户菜单

void User_menu()
{
    while(1)
    {
    printf("Please select a command from the menu\n1. Check for available seats\n2. Reserve seat\n3. Check your reservation\n4. Exit logining\n5. Quit\n");
    while(getchar() != '\n'); 
    scanf("%d",&menu_select);
    
    switch(menu_select)
      {
        case 1://Check for available seats
        Check();
        break;

        case 2://Reserve seat
        while(1)
        {
           int flag = Reserve();
           if(flag == 1)
           {
               printf("This seat is not available!\n");
               continue;
           }
           printf("OK!\n");

           break;
        }
        break;

        case 3://Check your reservation
        checkmyself();
        break;

        case 4:
        flag1 = 1;
        break;

        case 5:
        SaveData();
        return ;

     }
    }
}


//登录函数
void Loginf()
{
    while(1)
    {
        printf("Please enter command:");
        scanf("%s",Login);

        if(strcmp(Login,"Login") == 0)
        {
            printf("Please enter the User_name:");
            scanf("%s",User_name);

            if(strcmp(User_name,"Admin") == 0)
            {
                printf("Welcome!%s\n",User_name);
                break;
            }
            else if(strlen(User_name) == 1 && isalpha(User_name[0]))
            {
                User_name[0] = toupper(User_name[0]);
                printf("Welcome!%s\n",User_name);
                break;
            }
            else
            {
                printf("Invalid User_name! A-Z(a-z) or Admin\n");
            }
        }
        else if(strcmp(Login,"Quit") == 0)
        {
            flag2 = 0;
            break;
        }
        else
        {
            printf("Invalid command!\n");
        }
    }
}