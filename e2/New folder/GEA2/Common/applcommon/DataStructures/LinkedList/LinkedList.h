/*!
 * @file
 * @brief Statically allocated linked list.  Nodes are allocated by clients.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

/*!
 * A linked list node.  Struct members should be considered private.
 * @note This will generally be used within another struct to make that struct a linked list node.
 */
typedef struct LinkedListNode_t
{
   struct LinkedListNode_t *next;
} LinkedListNode_t;

/*!
 * Function called at each node when using ForEach()
 * @param node Current node.
 * @param context ForEach context.
 * @param index Node index.
 * @return True if iteration should continue, false otherwise.
 */
typedef bool (*LinkedList_ForEachCall_t)(LinkedListNode_t *node, void *context, const size_t index);

/*!
 * A singly-linked list.  Struct members should be considered private.
 */
typedef struct LinkedList
{
   LinkedListNode_t *head;
} LinkedList_t;

/*!
 * Initialize a linked list to an empty list.
 * @pre list != NULL
 * @param list The list.
 */
void LinkedList_Init(LinkedList_t *list);

/*!
 * Count the nodes in a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @returns The number of nodes in the list.
 */
size_t LinkedList_Count(const LinkedList_t *list);

/*!
 * Get the node at a specific location in a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre index < Count(list)
 * @param list The list.
 * @param index The specified index.
 * @returns The node at the specified location..
 */
LinkedListNode_t * LinkedList_At(const LinkedList_t *list, const size_t index);

/*!
 * Get the index of a node within a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre Contains(list, node)
 * @param list The list..
 * @param node The node..
 * @returns The index of the node within the list.
 */
size_t LinkedList_IndexOf(const LinkedList_t *list, const LinkedListNode_t *node);

/*!
 * Determine whether a node is contained in a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param node The node.
 * @returns True if the node is contained in the list, false otherwise.
 */bool LinkedList_Contains(const LinkedList_t *list, const LinkedListNode_t *node);

/*!
 * Add a node to the front (head) of a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @param list The list.
 * @param node The node.
 */
void LinkedList_PushFront(LinkedList_t *list, LinkedListNode_t *node);

/*!
 * Add a node to the back (tail) of a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @param list The list.
 * @param node The node.
 */
void LinkedList_PushBack(LinkedList_t *list, LinkedListNode_t *node);

/*!
 * Add a node at the specified index in the list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @pre !Contains(list, node)
 * @pre index <= Count(list)
 * @param list The list.
 * @param node The node.
 */
void LinkedList_Insert(LinkedList_t *list, LinkedListNode_t *node, size_t index);

/*!
 * Remove a node from the front (head) of a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre Count(list) > 0
 * @param list The list.
 * @returns The removed node.
 */
LinkedListNode_t * LinkedList_PopFront(LinkedList_t *list);

/*!
 * Remove a node from the back (tail) of a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre Count(list) > 0
 * @param list The list.
 * @returns The removed node.
 */
LinkedListNode_t * LinkedList_PopBack(LinkedList_t *list);

/*!
 * Remove a specific node from a list.
 * @pre list != NULL
 * @pre node != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param node The node.
 */
void LinkedList_Remove(LinkedList_t *list, LinkedListNode_t *node);

/*!
 * Remove the node at a specific index from a list.
 * @pre list != NULL
 * @pre Initialized(list)
 * @pre index < Count(list)
 * @param list The list.
 * @param index The index.
 */
void LinkedList_RemoveAt(LinkedList_t *list, const size_t index);

/*!
 * Iterate through a list (front to back) and call a function for each node in the list.  More efficient than iterating manually.
 * @pre list != NULL
 * @pre each != NULL
 * @pre Initialized(list)
 * @param list The list.
 * @param each The function.
 * @param context Context passed for each function invocation.
 * @note If Each returns true then iteration continues, otherwise iteration terminates.
 */
void LinkedList_ForEach(const LinkedList_t *list, LinkedList_ForEachCall_t each, void *context);

#endif
