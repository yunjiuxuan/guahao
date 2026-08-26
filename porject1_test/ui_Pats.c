#include "ui_LoginAndRegiste.h"
void clearHouZhenList(PatsList head)
{
    DBG_MSG("clearHouZhenList\n");
    if (head == NULL)
    {
        DBG_MSG("链表为空\n");
        return;
    }

    PatsNode *cur = head->next;
    int count = 0;
    while (cur != head)
    {
        DBG_MSG("删除节点：%s\n", cur->patsInfo);
        PatsNode *next = cur->next;
        free(cur);
        cur = next;
        count++;
    }

    head->next = head;
    head->pre = head;
    DBG_MSG("已清空 %d 个节点", count);
}
void dispaly(PatsList head)
{
    DBG_MSG("==========开始dispaly==============\n");
    if (head == NULL)
    {
        DBG_MSG("链表为空\n");
        return;
    }

    PatsList cur = head->next;

    if (cur == head)
    {
        DBG_MSG("候诊列表为空。\n");
        return;
    }

    int index = 1;
    DBG_MSG("===== 候诊病人列表 =====\n");
    while (cur != head)
    {
        DBG_MSG("%d. %s\n", index++, cur->patsInfo);
        cur = cur->next;
    }
    DBG_MSG("==========dispaly结束==============\n");
}
PatsList initHouZhenList(void)
{
    DBG_MSG("initHouZhenList\n");
    PatsList head = (PatsList)malloc(sizeof(PatsNode));
    if (head == NULL)
    {
        return NULL;
    }

    head->next = head;
    head->pre = head;
    strcpy(head->patsInfo, "");
    DBG_MSG("初始化成功");
    return head;
}

// 尾差法
bool insertPatsAtTail(PatsList head, const char *patsInfo)
{
    DBG_MSG("\n==========================insertPatsAtTail=======================\n");
    if (head == NULL || patsInfo == NULL)
    {
        return false;
    }

    PatsList newnode = (PatsList)malloc(sizeof(PatsNode));
    if (newnode == NULL)
    {
        return false;
    }

    strncpy(newnode->patsInfo, patsInfo, STR_MAX - 1);
    newnode->patsInfo[STR_MAX - 1] = '\0';

    PatsList headpre = head->pre;

    newnode->next = head;
    newnode->pre = headpre;
    headpre->next = newnode;
    head->pre = newnode;
    DBG_MSG("\n------------------------------%s   插入成功", newnode->patsInfo);
    return true;
}
// 头插法
bool insertPatsAtHead(PatsList head, const char *patsInfo)
{
    DBG_MSG("\n==========================insertPatsAtHead=======================\n");
    if (head == NULL || patsInfo == NULL)
    {
        return false;
    }

    PatsList newnode = (PatsList)malloc(sizeof(PatsNode));
    if (newnode == NULL)
    {
        return false;
    }

    strncpy(newnode->patsInfo, patsInfo, STR_MAX - 1);
    newnode->patsInfo[STR_MAX - 1] = '\0';

    PatsList first = head->next;

    newnode->next = first;
    newnode->pre = head;
    head->next = newnode;
    first->pre = newnode;

    DBG_MSG("\n------------------------------%s   头部插入成功", newnode->patsInfo);
    return true;
}
bool deletePatsNode(PatsList head, const char *patsInfo)
{
    DBG_MSG("deletePatsNode\n");

    PatsList cur = head->next;
    while (cur != head)
    {
        if (strcmp(cur->patsInfo, patsInfo) == 0)
        {
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
            free(cur);
            DBG_MSG("删除成功");
            return true; // 删除成功
        }
        cur = cur->next;
    }

    return false;
}
