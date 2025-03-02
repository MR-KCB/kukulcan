/*
* File: platformtypes.h
*
* Description: Module for all interfaces declared in dio.c
*              required for external access
*
*/


#ifndef PLATFORMTYPES_H
#define PLATFORMTYPES_H
/******************************************************************************
 * Include definitions   
 *****************************************************************************/
#include <stddef.h>
#ifdef PRINTS_ENABLE
#pragma message("Prints enable...")
#include <stdio.h>
#else
#define printf(...) 
#endif

/******************************************************************************
 * typedefs definitions
 *****************************************************************************/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef char sint8;
typedef short sint16;
typedef int sint32;
typedef long sint64;

typedef enum {
  OK = 0,
  NOT_OK = 1,
  BUSY = 2,
  ERROR = 3,
} stdReturn;

typedef enum {
  TRUE = 1,
  FALSE = 0,
  HIGH = 1,
  LOW = 0,
  ON = 1,
  OFF = 0,
} boolean;



/******************************************************************************
 * External macro definitions
 *****************************************************************************/

/******************************************************************************
 * External constant definitions
 *****************************************************************************/

/*****************************************************************************
 * Prototype definitions for external access
 *****************************************************************************/


#endif /* PLATFORMTYPES_H */
