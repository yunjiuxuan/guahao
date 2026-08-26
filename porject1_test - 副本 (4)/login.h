#ifndef _MYWIN_H
#define _MYWIN_H


#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "lvgl/examples/lv_examples.h" 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ui/ui.h"

#define DISP_BUF_SIZE (600 * 1024)
LV_FONT_DECLARE(chinese) // 确定字库对象


#ifndef __DEBUG_H__
#define __DEBUG_H__
 

// ====== 调试开关 ======
#define DEBUG_ENABLE    1   // ← 改为 0 则完全禁用打印
static debugconst =0;  
#if DEBUG_ENABLE
    #define DBG_PRINT() \
        do { \
            printf("%d\n",debugconst ); \
            debugconst++;\
        } while(0)
#else
    #define DBG_PRINT(fmt, ...) do { } while(0)  // 空操作，编译后无代码
#endif

#endif // __DEBUG_H__



static char *username;
static char *password;
typedef struct userinfo
{
    int id;
    char username[20];
    char password[10];
} user, *USER;

typedef struct userlist
{
    int len;
    USER data;
    struct userlist *NEXT;
} userlist, *USERLIST;


// 实例化全局变量界面对象
static lv_obj_t *main_win = NULL;  // 主界面
static lv_obj_t *user1_win = NULL; // 功能子界面1
static lv_obj_t *user2_win = NULL; // 功能子界面2

static int i = 4, j = 2;
static char bg_url[100] = "S:/userdata/bmp/1.bmp";
static char tb1_url[100] = "S:/userdata/bmp/sz1.bmp";
static char tb2_url[100] = "S:/userdata/bmp/sz2.bmp";
static char tb0_url[100] = "S:/userdata/bmp/fanhui.bmp";
static char loginurl[100] = "S:/userdata/bmp/login.bmp";
static char registeurl[100] = "S:/userdata/bmp/registe.bmp";

// 前向声明事件回调函数，用于处理文本框的各种事件（如点击、聚焦、完成等）
static void ta_event_cb(lv_event_t *e);

// 全局变量，用于保存键盘对象的指针，以便在多个文本框之间切换焦点
static lv_obj_t *kb;

// 样式设置
static lv_style_t mystyle; // 静态全局样式

// 显示页面
void show_main_win(void);
void show_user1_win(char *username, char *password );
void show_user2_win(void);

// 事件
void user1_event(lv_event_t *e);
void user2_event(lv_event_t *e);
void main_event1(lv_event_t *e);
void main_event2(lv_event_t *e);

void show_button();
void show_btn();
static void funb(lv_event_t *e);
void show_Image(int i);
void style_show();
void lvgl_init(void); 


//注册or登录
extern USERLIST head;

void head_add_user(USERLIST head, USER user);
int find_UsernameAndPwd(  char *username,  char *password);
 int adduserinfo(  char *username,  char *password);

static  lv_obj_t *username_ta  ;

static  lv_obj_t * pwd_ta;

static  lv_obj_t * pwd2_ta;


static int zhuce = 0 ;

#endif