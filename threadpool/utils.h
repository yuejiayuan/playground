#ifndef __UTILS_H__
#define __UTILS_H__
//
// Created by yuejiayuan on 2021/4/4.
//

//#define DEBUG_MODE

// 头插法入链表
#define YLIST_ADD(item, list) do {  \
    item->prev = NULL;  \
    item->next = list;  \
    if (list != NULL) list->prev = item;  \
    list = item;  \
} while (0)

#define YLIST_REMOVE(item, list) do {  \
    if (item->prev != NULL) item->prev->next = item->next;  \
    if (item->next != NULL) item->next->prev = item->prev;  \
    if (item == list)  list = item->next;  \
    item->next = item->prev = NULL;  \
} while (0)

#endif
