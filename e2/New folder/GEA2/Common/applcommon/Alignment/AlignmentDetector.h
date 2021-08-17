/*!
 * @file
 * @brief Utility for detecting the strictest alignment requirement of an environment.
 *
 * @warning This has been tested in only a few environments.  It would be prudent to double-check that
 * this works for your environment and file a bug report if it does not.  At the very least it will not
 * determine an alignment that is _more_ strict than necessary.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef ALIGNMENTDETECTOR_H
#define ALIGNMENTDETECTOR_H

#include <stdint.h>

/*!
 * Detect the strictest alignment requirements of the current execution environment.
 * @return The byte alignment of the current execution environment.
 */
uint8_t AlignmentDetector_GetAlignment(void);

#endif
