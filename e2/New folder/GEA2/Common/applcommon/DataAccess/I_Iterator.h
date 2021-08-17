/*!
 * @file
 * @brief Interface for an iterator
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_ITERATOR_H
#define I_ITERATOR_H

#include <stdbool.h>

struct I_Iterator_Api_t;

typedef struct
{
   const struct I_Iterator_Api_t *api;
} I_Iterator_t;

typedef struct I_Iterator_Api_t
{
   /*!
    * Move the iterator to the next entry and return the value if one exists
    * @param instance The instance
    * @param entryBuffer Buffer to read the entry into.
    * @return Indication if a next value was returned.
    */
   bool (*GetNext)(I_Iterator_t *instance, void *entryBuffer);
} I_Iterator_Api_t;

#define Iterator_GetNext(instance, entryBuffer) \
   (instance)->api->GetNext((instance), (entryBuffer))

/*!
 * Used to iterate through all of the entries provided by an iterator.  Similar syntax as a loop.
 *
 * Example given an I_Iterator reference:
 *
 * SomeEntryType_t entry;
 *
 * foreach(iterator, &entry)
 * {
 *    // Do something with the entry
 * }
 *
 * @note The extra parentheses are present to keep Eclipse's formatter from formatting improperly
 */
#define foreach(iterator, entry) while((Iterator_GetNext((iterator), (entry))))

#endif
