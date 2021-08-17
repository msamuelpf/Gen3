/*!
 * @file
 * @brief Statically allocated linked list.  Nodes are allocated by clients.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stddef.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "uassert.h"

void LinkedList_Init(LinkedList_t *list)
{
   uassert(list);

   list->head = NULL;
}

size_t LinkedList_Count(const LinkedList_t *list)
{
   size_t count = 0;
   LinkedListNode_t *current;

   uassert(list);

   current = list->head;

   while(current)
   {
      current = current->next;
      count++;
   }

   return count;
}

LinkedListNode_t * LinkedList_At(const LinkedList_t *list, const size_t index)
{
   size_t i;
   LinkedListNode_t *current;

   uassert(list);

   current = list->head;
   uassert(current);

   for(i = 0; i < index; i++)
   {
      current = current->next;
      uassert(current);
   }

   return current;
}

size_t LinkedList_IndexOf(const LinkedList_t *list, const LinkedListNode_t *node)
{
   LinkedListNode_t *current;
   size_t index = 0;

   uassert(list);
   uassert(node);

   current = list->head;

   while(current)
   {
      if(current == node)
      {
         return index;
      }

      current = current->next;
      index++;
   }

   uassert(!"node not in the list!");
   return 0;
}

bool LinkedList_Contains(const LinkedList_t *list, const LinkedListNode_t *node)
{
   LinkedListNode_t *current;

   uassert(list);
   uassert(node);

   current = list->head;

   if(current == node)
   {
      return true;
   }

   while(current)
   {
      current = (current->next);

      if(current == node)
      {
         return true;
      }
   }

   return false;
}

void LinkedList_PushFront(LinkedList_t *list, LinkedListNode_t *node)
{
   uassert(list);
   uassert(node);
   uassert(!LinkedList_Contains(list, node));

   node->next = list->head;
   list->head = node;
}

void LinkedList_PushBack(LinkedList_t *list, LinkedListNode_t *node)
{
   LinkedListNode_t *current;

   uassert(list);
   uassert(node);
   uassert(!LinkedList_Contains(list, node));

   current = list->head;

   node->next = NULL;

   if(current)
   {
      while(current->next)
      {
         current = current->next;
      }

      current->next = node;
   }
   else
   {
      list->head = node;
   }
}

void LinkedList_Insert(LinkedList_t *list, LinkedListNode_t *node, size_t index)
{
   uassert(list);
   uassert(node);
   uassert(!LinkedList_Contains(list, node));

   if(index > 0)
   {
      LinkedListNode_t *before = LinkedList_At(list, index - 1);
      node->next = before->next;
      before->next = node;
   }
   else
   {
      LinkedList_PushFront(list, node);
   }
}

LinkedListNode_t * LinkedList_PopFront(LinkedList_t *list)
{
   LinkedListNode_t *popped;

   uassert(list);
   uassert(list->head);

   popped = list->head;
   list->head = list->head->next;

   return popped;
}

LinkedListNode_t * LinkedList_PopBack(LinkedList_t *list)
{
   LinkedListNode_t *popped;
   LinkedListNode_t *current;

   uassert(list);
   uassert(list->head);

   current = list->head;

   if(current->next)
   {
      while(current->next->next)
      {
         current = current->next;
      }

      popped = current->next;
      current->next = NULL;
   }
   else
   {
      popped = list->head;
      list->head = NULL;
   }

   return popped;
}

void LinkedList_RemoveAt(LinkedList_t *list, const size_t index)
{
   size_t i;
   LinkedListNode_t *previous = NULL;
   LinkedListNode_t *current;

   uassert(list);

   current = list->head;

   for(i = 0; i < index; i++)
   {
      uassert(current);
      previous = current;
      current = current->next;
   }

   uassert(current);

   if(previous)
   {
      previous->next = current->next;
   }
   else
   {
      list->head = current->next;
   }
}

void LinkedList_Remove(LinkedList_t *list, LinkedListNode_t *node)
{
   uassert(list);
   uassert(node);

   if(list->head == node)
   {
      list->head = node->next;
   }
   else
   {
      LinkedListNode_t *current = list->head;

      while(current)
      {
         if(current->next == node)
         {
            current->next = node->next;
            break;
         }

         current = current->next;
      }
   }
}

void LinkedList_ForEach(const LinkedList_t *list, LinkedList_ForEachCall_t each, void *context)
{
   LinkedListNode_t *current;
   size_t index = 0;

   uassert(list);
   uassert(each);

   current = list->head;

   while(current)
   {
      LinkedListNode_t *next = current->next;

      if(!each(current, context, index))
      {
         break;
      }

      current = next;
      index++;
   }
}
