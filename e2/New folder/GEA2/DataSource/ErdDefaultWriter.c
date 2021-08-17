/*!
 * @file
 * @brief Xmacro code that will write defult values for erds
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "ErdDefaultWriter.h"
#include "ErdDefaultWriterConfiguration.h"
#include "utils.h"

#define EXPAND_AS_ERD_DEFAULT_WRITER_CODE(Enumeration, DataType, DefaultValue) \
{\
   DataType Enumeration##Data = DefaultValue; \
   DataSource_Write(dataSource, Enumeration, &Enumeration##Data); \
}

void ErdDefaultWriter_Write(I_DataSource_t *dataSource)
{
   IGNORE_ARG(dataSource); // Just in case there are no entries in the table
   ERD_DEFAULTS_TABLE(EXPAND_AS_ERD_DEFAULT_WRITER_CODE)
}
