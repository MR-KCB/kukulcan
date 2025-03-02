/*
* File: memcpy.h
*
* Description: memcpy utilities 
*
*/

#ifndef MEMCPY_H
#define MEMCPY_H

/******************************************************************************
 * Include definitions   
 *****************************************************************************/
#include "platformtypes.h"


/*****************************************************************************
 * Prototype definitions for external access
 *****************************************************************************/
void * custom_memcpy(void *dest, void *src, size_t numbytes);
void * memcpy_8bit (void *dest, const void *src, size_t len);
void * memcpy_16bit(void *dest, const void *src, size_t len);
void * memcpy_32bit(void *dest, const void *src, size_t len);

#endif /*MEMCPY_H*/