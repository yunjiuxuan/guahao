
#include "login.h"

// 定义结构体保存数据
struct user
{
    int id;
    char username[10];
    char password[10];
} userinfo[10]; // 结构体数组
static int i;

// 打开文件
FILE *openfile(const char *path, char *mode)
{
    // 打开文件 获取文件流指针
    FILE *fp = fopen(path, mode);
    if (fp == NULL)
    {
        perror("fopen failed\n");
        return NULL;
    }
    else
    {
        printf("打开文件成功\n");
        printf("文件流指针：%p\n", fp);
        return fp;
    }
}
// 关闭文件
int closefile(FILE *fp)
{
    // 关闭文件 文件流指针负责关闭
    int ret = fclose(fp);
    if (ret == EOF)
    {
        perror("fclose failed\n");
        return -1;
    }
    else
    {
        printf("关闭文件流成功\n");
    }
}
// 解析账户和密码
int userfile(FILE *fp, char *username, char *password)
{
    // 定义字符串保存数据
    char buf[50];
    // 循环读取文件内容
    int i = 0;
    while (1)
    {
        // 清空数组
        memset(buf, 0, sizeof(buf));
        // 逐行读取内容
        fgets(buf, sizeof(buf), fp);
        // 若读取到末尾结束
        if (feof(fp) != 0)
            break;
        // 解读读取的内容
        fputs(buf, stdout);
        // 拆分内容保存到结构体数组
        sscanf(buf, "userid:%d username:%s password:%s",
               &userinfo[i].id, userinfo[i].username, userinfo[i].password);

        printf("获取用户表信息  用户名：%s 密码：%s\n", userinfo[i].username, userinfo[i].password);
        if (strcmp(username, userinfo[i].username) == 0)
        {
            if (strcmp(password, userinfo[i].password) == 0 && zhuce == 0)
            {
                printf("登录成功！,返回账号id:   %d\n", userinfo[i].id);

                printf("账号信息:   %s  %s\n", userinfo[i].username, userinfo[i].password);
 
                return userinfo[i].id;
            }
            else
            {
                printf("账号存在\n");
                return -1;
            }
        }
        i++;
    }
    printf("用户不存在！\n");
    return -2;
    closefile(fp);
}

int find_UsernameAndPwd(char *username, char *password)
{

    FILE *fp = openfile("/userdata/userinfo.txt", "r");
    zhuce = 0;
    printf("\n开始遍历用户表...");
    printf("\n传入username为：%s", username);
    printf("\n传入password为：%s\n", password);
    int res = userfile(fp, username, password);
    return res;
}

int adduserinfo(char *username, char *password)
{

    FILE *fp = openfile("/userdata/userinfo.txt", "a+");

    printf("\n传入username为：%s", username);
    printf("\n传入password为：%s\n", password);
    zhuce = 1;
    int res = userfile(fp, username, password);
    if (res == -1)
    {
        printf("\n账号存在,添加用户失败！\n");
        return 0;
    }
    else
    {
        printf("\n开始添加用户...");

        int id = rand() % 100 + 4;
        fprintf(fp, "userid:%d username:%s password:%s\n",
                id, username, password);
        printf("\n成功添加用户: ID=%d, 用户名=%s \n",id, username);

        return 1;
    }
}