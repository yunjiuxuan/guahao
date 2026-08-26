#include "ui/ui.h"
#include "ui_LoginAndRegiste.h"

 

 bool is_doc_registered(const char *dir_path, const char *docid)
{
    char filepath[256];
    int len = snprintf(filepath, sizeof(filepath), "%s/%s.txt", dir_path, docid);

    if (access(filepath, F_OK) == 0)
    {
        return true; // 存在,已注册
    }
    else
    {
        return false; // 不存在,未注册
    }
}


DL Dinit() {
    DL duilie = (DL)malloc(sizeof(struct duilie));
    if (duilie == NULL) {
        DBG_MSG("duilie malloc failed\n");
        return NULL;
    }
    // 清空所有字符串
    for (int i = 0; i < MAX; i++) {
        memset(duilie->data[i], 0, STR_MAX);
    }
    duilie->front = 0;
    duilie->after = 0;
    duilie->length = 0;
    return duilie;
}

void inD(DL duilie, const char* str) {
    DBG_MSG("入队信息: \"%s\"\n", str);
    if (duilie == NULL || str == NULL) return;

    if (duilie->after >= MAX) { 
        DBG_MSG("队列已满\n");
        return;
    }
DBG_PRINT();
    strncpy(duilie->data[duilie->after], str, STR_MAX - 1);
    duilie->data[duilie->after][STR_MAX - 1] = '\0'; 

    duilie->after++;
    duilie->length++;

    DBG_MSG("入队: \"%s\", 队尾=%d, 长度=%d\n", 
            duilie->data[duilie->after - 1], duilie->after, duilie->length);
}
//  0 表示成功，-1 表示空队
int outD(DL duilie, char* output, int output_size) {
    if (duilie == NULL || output == NULL) return -1;

    if (duilie->front == duilie->after) {
        DBG_MSG("空队\n");
        return -1;
    }
 
    strncpy(output, duilie->data[duilie->front], output_size - 1);
    output[output_size - 1] = '\0';

    duilie->front++;
    duilie->length--;

    DBG_MSG("出队: \"%s\", 队首=%d, 长度=%d\n", 
            output, duilie->front, duilie->length);
    return 0;
}


void clearD(DL duilie) {
    if (duilie == NULL) {
        return;
    }

    // 方法 1：仅重置指针和长度（高效）
    duilie->front = 0;
    duilie->after = 0;
    duilie->length = 0;

    // 方法 2（可选）：清空所有字符串内容（更安全，防残留）
    for (int i = 0; i < MAX; i++) {
        memset(duilie->data[i], 0, STR_MAX);
    }

    DBG_MSG("队列已清空\n");
}