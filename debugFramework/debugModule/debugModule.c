/*
*  Small compress module to allocate all debug utils
*
*
*
*/

/******************************************************************/
/* Includes */
/******************************************************************/
#include "debugModule.h"
/******************************************************************/
/* Defines  */
/******************************************************************/


/******************************************************************/
/* Typedefs and enums  */
/******************************************************************/
#pragma pack(1)
typedef struct
{
   tdebugModule debugModule;
   uint8 debugValue;
   uint32 lineNumber;
   uint32 timeStamp;
   uint8 terminator;
} tdebugInfo;

/******************************************************************/
/* Prototypes */
/******************************************************************/

/******************************************************************/
/* Variable section */
/******************************************************************/
tdebugInfo debugInformation[120];
uint16 printNo = 0U;
uint16 debugSlot = 0U;
uint64 startTime = 0U;
uint64 elapsedTime = 0U;

uint8 moduleNameStr[][25] =
{
   "module_1",
   "module_2",
   "module_3",
};


/******************************************************************/
/* Public Functions */
/******************************************************************/
void debugModule_init(void)
{
   elapsedTime = 0U;
   //GetCounterValue(SYSTEM_TIMER, &startTime);
}

void debugModule_increaseElapsedTime(void)
{
   elapsedTime++;
   //GetCounterValue(SYSTEM_TIMER, &startTime);
}

void debugModule_SaveValue(uint8 value, tdebugModule module, uint32 lineNo)
{
   if (debugSlot < 120U)
   {
      debugInformation[debugSlot].debugModule = module;
      debugInformation[debugSlot].debugValue = value;
      debugInformation[debugSlot].lineNumber = lineNo;
      debugInformation[debugSlot].timeStamp = elapsedTime;
      debugInformation[debugSlot].terminator = 0xFFU;
      debugSlot++;
   }
}

void debugModule_printData(uint8 value, tdebugModule module, uint32 lineNo)
{
   printf("[Debug Data Rqst][value] 0x%X\n", value);
   printf("[Debug Data Rqst][debugModule] %d\n",  module);
   printf("[Debug Data Rqst][lineNumber] %d\n",   lineNo);
}



/******************************************************************/
/* Private Functions */
/******************************************************************/

