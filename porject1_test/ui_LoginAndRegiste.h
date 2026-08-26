#include "ui/ui.h"
#include "ui/ui_helpers.h"
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
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX 50
#define STR_MAX 100



#define STR_MAX 100  // 假设最大字符串长度

// 双向循环链表节点结构体
typedef struct HouZhenListNode {
    char patsInfo[STR_MAX];           
    struct HouZhenListNode *next;   
    struct HouZhenListNode *pre;     
} PatsNode, *PatsList;  
void remove_extension(char *filename); 
bool deletePatsNode(PatsList pList, const char* patsInfo) ; 
bool insertPatsAtTail(PatsList pList, const char* patsInfo);
bool insertPatsAtHead(PatsList head, const char *patsInfo);
PatsList initHouZhenList(void);
void dispaly(PatsList head);
void clearHouZhenList(PatsList head);
bool is_doc_registered(const char *dir_path, const char *docid);
typedef struct duilie
{
    char data[MAX][STR_MAX];
    int front;  // 队首下标
    int after;  // 队尾下标
    int length; // 当前长度
} *DL;
DL Dinit();
void inD(DL duilie, const char *str);
int outD(DL duilie, char *output, int output_size);
void clearD(DL duilie);
typedef struct userinfo
{
    char username[20];
    char idcard[20];
    int role; // 0 普通用户 1中医科医师 2康复科医师 3内科医师 4外科医师
    char startTime[10];
    char endTime[10];
} user, *USER;
static   char selectedid[50];
static   char patspath[50]; 
extern  DL patslist;
extern user LoginUserinfo;
#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG_ENABLE 1

#if DEBUG_ENABLE
static int debugconst = 0;

#define DBG_PRINT()                                                   \
    do                                                                \
    {                                                                 \
        printf("\n\nDBG_PRINT%d ------      File:    %s,     Line: %d\n", \
               debugconst++, __FILE__, __LINE__);                     \
    } while (0)

#define DBG_MSG(fmt, ...)                                                                     \
    do                                                                                        \
    {                                                                                         \
        printf("\n\nFile:    %s,     Line: %d       ---------------------  \nDBG_MSG%d:   " fmt "\n", \
              __FILE__, __LINE__,  debugconst++, ##__VA_ARGS__);                             \
    } while (0)

#else
#define DBG_PRINT() \
    do              \
    {               \
    } while (0)
#define DBG_MSG(fmt, ...) \
    do                    \
    {                     \
    } while (0)
#endif

#endif // __DEBUG_H__

static bool is_processing = false;

// 显示提示并 2 秒后隐藏
void show_temp_label(lv_obj_t *label, const char *text, uint32_t duration_ms);

void ui_event_denglu_click(lv_event_t *e);
void ui_event_zhuce(lv_event_t *e);
FILE *openfile(const char *path, char *mode);
int closefile(FILE *fp);
