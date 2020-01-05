#include "list.h"

List createList()
{
    List list;
    list.Head = NULL;
    list.Tail = NULL;
    list.count = 0;
    return list;
}

void pushBackNode(List *list, void *data)
{
    if (list->Head == NULL)
    {
        Node *head = (Node *)malloc(sizeof(Node));
        head->data = data;
        head->next = NULL;
        head->prev = NULL;

        list->Head = head;
        list->Tail = head;
        list->count = 1;
    }
    else
    {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->next = NULL;
        node->prev = list->Tail;

        list->Tail->next = node;
        list->Tail = node;
        list->count++;
    }
}

void *getNodeByIndex(List *list, int index)
{
    if (index > list->count - 1)
    {
        return NULL;
    }
    else
    {
        Node *buf = list->Head;
        for (int i = 0; i < index; i++)
        {
            buf = buf->next;
        }
        return buf->data;
    }
}

void deleteNode(List *list, int index)
{
    if (index > list->count - 1)
    {
        return;
    }
    else
    {
        Node *buf = list->Head;
        for (int i = 0; i < index; i++)
        {
            buf = buf->next;
        }
        free(buf->data);
        if (buf == list->Head)
        {
            list->Head = list->Head->next;
            list->Head->prev = NULL;
        }
        else if (buf == list->Tail)
        {
            list->Tail = list->Tail->prev;
            list->Tail->next = NULL;
        }
        else
        {
            buf->prev->next = buf->next;
            buf->next->prev = buf->prev;
        }
        list->count--;
        free(buf);
        return;
    }
}