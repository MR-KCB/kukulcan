/*
*  Small compress module to allocate all debug utils
*
*
*
*/
#ifndef __DEBUGMODULE__
#define __DEBUGMODULE__


/******************************************************************/
/* Includes */
/******************************************************************/
#include "platformTypes.h"
/******************************************************************/
/* Defines */
/******************************************************************/

/******************************************************************/
/* Typedefs and enums  */
/******************************************************************/
typedef enum 
{
   eMODULE_1,
   eMODULE_2,
   eMODULE_3,
   eMODULE_4,
} tdebugModule;

/******************************************************************/
/* Prototypes */
/******************************************************************/


/******************************************************************/
/* Variable section */
/******************************************************************/

/******************************************************************/
/* Public Functions */
/******************************************************************/
extern void debugModule_init(void);
extern void debugModule_increaseElapsedTime(void);
extern void debugModule_SaveValue(uint8 value, tdebugModule module,  uint32 lineNo);
extern void debugModule_printData(uint8 value, tdebugModule module, uint32 lineNo);

#endif /*__DEBUGMODULE__*/