/*!
 * @file
 * @brief Defines a XMacro table of Default values to be written toi the ERDs in the DataModel
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef ERDDEFAULTWRITERCONFIGURATION_H
#define ERDDEFAULTWRITERCONFIGURATION_H

#include <WasherErds.h>

// ENTRY(Enumeration, DataType, DefaultValue)
#define ERD_DEFAULTS_TABLE(ENTRY)  \
	ENTRY(Erd_ApplianceType,            	ApplianceType_t,                 ApplianceType_TranslatorBoard)
#endif
