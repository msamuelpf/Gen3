/*!
 * @file
 * @brief Interface for extracting bi-directional mapping data that has mappings that contain a "one to many" or "many to one" relationship.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_CONSTMULTIMAP_H
#define I_CONSTMULTIMAP_H

#include "I_Iterator.h"

struct I_ConstMultiMap_Api_t;

typedef struct
{
   const struct I_ConstMultiMap_Api_t *api;
} I_ConstMultiMap_t;

typedef void (*ConstMultiMapCallback_t)(void *context, I_Iterator_t *iterator);

typedef struct I_ConstMultiMap_Api_t
{
   /*!
    * Find all the left values that are mapped to the right value.
    * @param instance The const multi-map.
    * @param key Key for which values will be found.
    * @param callback Callback that will be invoked with an iterator that can be used to visit values (if any exist).
    * @param context The context to be provided via the callback.
    */
   void (*Find)(I_ConstMultiMap_t *instance, const void *key, ConstMultiMapCallback_t callback, void *context);
} I_ConstMultiMap_Api_t;

#define ConstMultiMap_Find(instance, key, callback, context) \
   (instance)->api->Find((instance), (key), (callback), (context))

#endif
