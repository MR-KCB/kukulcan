/*
* File: memcpy.c
*
* Description: memcpy utilities 
*
*/

/**
 * @brief memcpy to copy from 8-Bits, 16-Bits, 32-Bits (1-Byte, 2-Byte, 4-Bytes), starting
 *        copy with the largest data supported until the small package
 * 
 * @param[out] dest  Destination output of data to copy
 * @param[in]  src   Source input of data to copy
 * @param[in]  len   Length of data to be copy
 * 
 * @return     void* Destination pointer where data was copy
 * 
 */
void * custom_memcpy(void *dest, void *src, size_t numbytes)
{
   void * destination = dest; 
   size_t offset = 0; 

   if(((uint8*)src == (uint8*)dest) || (NULL_PTR == src) || (NULL_PTR == dest))
   {
      // Same address nothing to be done
      // NULL PTR received as src or dest
      return destination;
   }

  while(numbytes)
  {
      if(numbytes < 2) // 1 byte
      {
        memcpy_8bit(dest, src, numbytes);
        offset = numbytes & -1;
        dest = (uint8 *)dest + offset;
        src = (uint8 *)src + offset;
        numbytes = 0;
      }
      else if(numbytes < 4) // 2 bytes
      {
        memcpy_16bit(dest, src, numbytes >> 1);
        offset = numbytes & -2;
        dest = (uint8 *)dest + offset;
        src = (uint8 *)src + offset;
        numbytes &= 1;
      }
      else //if(numbytes < 8) // 4 bytes
      {
        memcpy_32bit(dest, src, numbytes >> 2);
        offset = numbytes & -4;
        dest = (uint8 *)dest + offset;
        src = (uint8 *)src + offset;
        numbytes &= 3;
      }
  }
  return destination;
}


/**
 * @brief memcpy 8 bit/1 byte
 * 
 * @param[out] dest  Destination output of data to copy
 * @param[in]  src   Source input of data to copy
 * @param[in]  len   Length of data to be copy
 * 
 * @return     void* Destination pointer where data was copy
 * 
 */
void * memcpy_8bit (void *dest, const void *src, size_t len)
{
  const uint8 *source = (uint8*)src;
  uint8 *destination = (uint8*)dest;

  while (len--)
  {
    *destination++ = *source++;
  }

  return dest;
}

/**
 * @brief memcpy 16 bit/2 Bytes
 * 
 * @param[out] dest  Destination output of data to copy
 * @param[in]  src   Source input of data to copy
 * @param[in]  len   Length of data to be copy
 * 
 * @return     void* Destination pointer where data was copy
 * 
 */
void * memcpy_16bit(void *dest, const void *src, size_t len)
{
  const uint16* source = (uint16*)src;
  uint16* destination = (uint16*)dest;

  while (len--)
  {
    *destination++ = *source++;
  }

  return dest;
}


/**
 * @brief memcpy 32 bit/4 Bytes
 * 
 * @param[out] dest  Destination output of data to copy
 * @param[in]  src   Source input of data to copy
 * @param[in]  len   Length of data to be copy
 * 
 * @return     void* Destination pointer where data was copy
 * 
 */
void * memcpy_32bit(void *dest, const void *src, size_t len)
{
  const uint32* source = (uint32*)src;
  uint32* destination = (uint32*)dest;

  while (len--)
  {
    *destination++ = *source++;
  }

  return dest;
}



#if 0 // backup test
/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include "stdint.h"

uint32 dataSrc[] = {0x11111111,0x22222222,0x33333333,0x44444444,0x55555555,0x66666666,0x77777777,0x88888888,0x99999999,0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD,0xEEEEEEEE,0xFFFFFFFF};
uint32 dataDst[256] = {0};
#define ARRAY_SIZE(x)           (sizeof(x)/sizeof(x[0]))
#define NULL_PTR                ((void*)0)
int dataSrc_Test2[] = {3122916715, 1850201260, 3554221071, 2192062590, 1720979567, 2081812272, 894805599, 572999894, 2955457358, 993917778, 716966723, 968573008, 2886054782, 3205820501, 3786903525, 2223610804, 1320460375, 2599386273, 2709078762, 4170790790, 2786113535, 120293043, 3300680395, 614056910, 596765575, 2274859777, 4239864497, 3494270294, 1658437788, 1937187715, 1378952327, 4215160756, 1772375425, 2811019370, 4291739235, 2356359080, 3689195856, 2471478665, 3219764206, 2231812947, 2602260291, 987439670, 1058654987, 3628666811, 3254765133, 3705843594, 1869084388, 3765971111, 2709887069, 2188558727, 403013751, 3136738881, 810489637, 329097522, 1007327295, 2223986006, 144489824, 3694872, 3945102791, 2207184593, 4240409384, 1256132203, 2055067544, 4062990725, 1561058218, 1842775429, 3545088455, 2502865495, 3437021461, 1931697237, 1937234841, 1928419557, 939642483, 968712422, 4089220580, 2392286857, 524649156, 1459457422, 747310282, 912197272, 2399237931, 3365390051, 4209327482, 915727881, 733846479, 48002111, 982303783, 3185656587, 1612534222, 2156635322, 941358001, 11143536, 2633170248, 3576836242, 2449929655, 674400478, 1177918968, 3421081419, 3489722043, 667331192};
//int dataSrc_Test2[100u] = {0xba23ed6b, 0x6e47d4ac, 0xd3d91c0f, 0x82a8387e, 0x6694106f, 0x7c15ef30, 0x3555a65f, 0x222748d6, 0xb028b34e, 0x3b3dfb52, 0x2abc0b43, 0x39bb4050, 0xac05b37e, 0xbf14f055, 0xe1b78fe5, 0x84899bb4, 0x4eb4a057, 0x9aef7ca1, 0xa17942ea, 0xf8993786, 0xa610b7ff, 0x72b86b3, 0xc4bc62cb, 0x2499c3ce, 0x2391eb87, 0x87979b01, 0xfcb732b1, 0xd0465556, 0x62d9c09c, 0x73772383, 0x52312487, 0xfb3e3fb4, 0x69a44d81, 0xa78cc06a, 0xffcebe63, 0x8c732fa8, 0xdbe4a950, 0x934fc589, 0xbfe9b3ee, 0x8506c353, 0x9b1b5743, 0x3adb2236, 0x3f19cb0b, 0xd8490fbb, 0xc1ffc64d, 0xdce2af8a, 0x6f67f6e4, 0xe07828a7, 0xa185985d, 0x8272c187, 0x18058077, 0xbaf6d641, 0x304f1725, 0x139da132, 0x3c0a983f, 0x848f5556, 0x89cbd60, 0x386118, 0xeb257dc7, 0x838ef6d1, 0xfcbf8328, 0x4adf0e6b, 0x7a7dd798, 0xf22c5185, 0x5d0bdbaa, 0x6dd68585, 0xd34dc1c7, 0x952eb257, 0xccdcc915, 0x73235c55, 0x7377db99, 0x72f158e5, 0x3801ce73, 0x39bd60e6, 0xf3bc8de4, 0x8e976689, 0x1f4582c4, 0x56fd8d8e, 0x2c8b0cca, 0x365f0698, 0x8f01772b, 0xc897c6e3, 0xfae53d7a, 0x3694e609, 0x2bbd9bcf, 0x2dc743f, 0x3a8cc427, 0xbde1430b, 0x601d51ce, 0x808ba4ba, 0x381bfbb1, 0xaa0970, 0x9cf2fd48, 0xd5323092, 0x9206f5b7, 0x283288de, 0x46359df8, 0xcbe98f4b, 0xd000eebb, 0x27c6aa78};
//int length_of_array = 100u;

int dataSrc_Test3[57u] = {2881625272, 3301600401, 217551559, 584971221, 2153461596, 1238819651, 3608618772, 3168104004, 3232399702, 133455607, 3528476202, 964690392, 2592751330, 2785652746, 1368741082, 469757400, 3759364948, 2126365962, 19752255, 1446639187, 4171540319, 1999797171, 3482630272, 3722920650, 231601215, 4016030334, 3284084802, 3840882064, 2119835314, 694838631, 558538476, 2522662204, 177337211, 309348125, 991737927, 2951953165, 697252730, 2785252928, 2410744320, 2052354727, 3928065087, 2837124210, 4279009656, 3205692370, 1591448125, 1995677998, 3207750958, 343451067, 1746275206, 1062456966, 1199406112, 4121167131, 512615256, 1758532359, 1610641452, 282346544, 1287078008};
//int dataSrc_Test3[57u] = {0xabc21cb8, 0xc4ca6c91, 0xcf792c7, 0x22ddf3d5, 0x805b375c, 0x49d6e343, 0xd7172714, 0xbcd56e44, 0xc0aa8156, 0x7f45ef7, 0xd250462a, 0x398001d8, 0x9a8a3ee2, 0xa609b00a, 0x519554da, 0x1bffedd8, 0xe0135b54, 0x7ebdc50a, 0x12d653f, 0x5639f653, 0xf8a4a75f, 0x77327bb3, 0xcf94b880, 0xdde742ca, 0xdcdf43f, 0xef5fc27e, 0xc3bf2842, 0xe4ef3590, 0x7e5a1eb2, 0x296a6567, 0x214a9eec, 0x965cc53c, 0xa91f37b, 0x1270471d, 0x3b1cb847, 0xaff33b0d, 0x298f3b7a, 0xa6039640, 0x8fb10a00, 0x7a5472a7, 0xea21843f, 0xa91b1472, 0xff0c8178, 0xbf12fbd2, 0x5edb923d, 0x76f3a12e, 0xbf32652e, 0x1478a5bb, 0x68160b86, 0x3f53ce86, 0x477d7c20, 0xf5a4051b, 0x1e8de358, 0x68d11307, 0x6000702c, 0x10d44430, 0x4cb74078};
//int length_of_array  = 57u;


uint8_t dataSrc_Test4[111u] = {102, 5, 200, 55, 233, 88, 73, 219, 108, 157, 117, 203, 105, 143, 209, 86, 129, 89, 34, 71, 66, 21, 91, 209, 63, 254, 12, 201, 147, 47, 158, 79, 80, 5, 222, 229, 215, 69, 255, 77, 91, 235, 228, 162, 155, 187, 193, 210, 200, 30, 24, 26, 205, 251, 15, 152, 178, 53, 219, 131, 88, 194, 11, 103, 231, 88, 31, 120, 84, 234, 7, 233, 6, 184, 151, 58, 122, 143, 28, 208, 93, 10, 174, 67, 234, 180, 209, 100, 178, 99, 182, 175, 225, 126, 161, 3, 165, 34, 159, 206, 86, 224, 119, 44, 58, 78, 185, 87, 137, 203, 57};
//int dataSrc_Test4[111u] = {0x66, 0x5, 0xc8, 0x37, 0xe9, 0x58, 0x49, 0xdb, 0x6c, 0x9d, 0x75, 0xcb, 0x69, 0x8f, 0xd1, 0x56, 0x81, 0x59, 0x22, 0x47, 0x42, 0x15, 0x5b, 0xd1, 0x3f, 0xfe, 0xc, 0xc9, 0x93, 0x2f, 0x9e, 0x4f, 0x50, 0x5, 0xde, 0xe5, 0xd7, 0x45, 0xff, 0x4d, 0x5b, 0xeb, 0xe4, 0xa2, 0x9b, 0xbb, 0xc1, 0xd2, 0xc8, 0x1e, 0x18, 0x1a, 0xcd, 0xfb, 0xf, 0x98, 0xb2, 0x35, 0xdb, 0x83, 0x58, 0xc2, 0xb, 0x67, 0xe7, 0x58, 0x1f, 0x78, 0x54, 0xea, 0x7, 0xe9, 0x6, 0xb8, 0x97, 0x3a, 0x7a, 0x8f, 0x1c, 0xd0, 0x5d, 0xa, 0xae, 0x43, 0xea, 0xb4, 0xd1, 0x64, 0xb2, 0x63, 0xb6, 0xaf, 0xe1, 0x7e, 0xa1, 0x3, 0xa5, 0x22, 0x9f, 0xce, 0x56, 0xe0, 0x77, 0x2c, 0x3a, 0x4e, 0xb9, 0x57, 0x89, 0xcb, 0x39};
//int length_of_array = 111u;
uint8_t dataDstU8[256] = {0};


void * custom_memcpy(void *dest, void *src, size_t numbytes);
void * memcpy_8bit (void *dest, const void *src, size_t len);
void * memcpy_16bit(void *dest, const void *src, size_t len);
void * memcpy_32bit(void *dest, const void *src, size_t len);

void test1();
void test2();
void test3();
void test4();

int main()
{
    printf("========================================================\n");
    test1();
    printf("========================================================\n");
    test2();
    printf("========================================================\n");
    test3();
    printf("========================================================\n");
    test4();
    printf("========================================================\n");
    return 0;
}



void test1()
{
    uint32 i,j;
    
    void * retVal;
    retVal = custom_memcpy(dataDst, dataSrc, sizeof(dataSrc));
    printf("MemCpy: %X\n", retVal  );
    
    
    for (int i = 0 ; i < ARRAY_SIZE(dataSrc); i++)
    {
        printf("dataSrc[%i] : 0x%X\n", i, dataSrc[i]);
        printf("dataDst[%i] : 0x%X\n", i, dataDst[i]);
    }
 
}

void test2()
{
    uint32 i,j;
    
    void * retVal;
    retVal = custom_memcpy(dataDst, dataSrc_Test2, sizeof(dataSrc_Test2));
    printf("MemCpy: %X\n", retVal  );
    
    
    for (int i = 0 ; i < ARRAY_SIZE(dataSrc_Test2); i++)
    {
        printf("dataSrc[%i] : 0x%X\n", i, dataSrc_Test2[i]);
        printf("dataDst[%i] : 0x%X\n", i, dataDst[i]);
    }

}

void test3()
{
    uint32 i,j;
    
    void * retVal;
    retVal = custom_memcpy(dataDst, dataSrc_Test3, sizeof(dataSrc_Test3));
    printf("MemCpy: %X\n", retVal  );
    
    
    for (int i = 0 ; i < ARRAY_SIZE(dataSrc_Test3); i++)
    {
        printf("dataSrc[%i] : 0x%X\n", i, dataSrc_Test3[i]);
        printf("dataDst[%i] : 0x%X\n", i, dataDst[i]);
    }

}

void test4()
{
    uint32 i,j;
    
    void * retVal;
    retVal = custom_memcpy(dataDstU8, dataSrc_Test4, sizeof(dataSrc_Test4));
    printf("MemCpy: %X\n", retVal  );
    
    
    for (int i = 0 ; i < ARRAY_SIZE(dataSrc_Test4); i++)
    {
        printf("dataSrc[%i] : 0x%X\n", i, dataSrc_Test4[i]);
        printf("dataDst[%i] : 0x%X\n", i, dataDstU8[i]);
    }

}

void *  custom_memcpy(void *dest, void *src, size_t numbytes)
{
   void * returnval = dest; 
   size_t offset = 0; 
   
   if(((uint8*)src == (uint8*)dest) || (NULL_PTR == src) || (NULL_PTR == dest))
   {
      // Lol.
      return returnval;
   }
     printf("[START] numbytes: %d offset: %d\n", numbytes , offset);
   while(numbytes)
  // The biggest sizes will go first for alignment. There's no benefit to using
  // aligned loads over unaligned loads here, so all are unaligned.
  // NOTE: Each memcpy has its own loop so that any one can be used individually.
  {
      if(numbytes < 2) // 1 byte
      {
         memcpy_8bit(dest, src, numbytes);
         offset = numbytes & -1;
         dest = (uint8 *)dest + offset;
         src = (uint8 *)src + offset;
         numbytes = 0;
      }
      else if(numbytes < 4) // 2 bytes
      {
         memcpy_16bit(dest, src, numbytes >> 1);
         offset = numbytes & -2;
         dest = (uint8 *)dest + offset;
         src = (uint8 *)src + offset;
         numbytes &= 1;
      }
      else //if(numbytes < 8) // 4 bytes
      {
         memcpy_32bit(dest, src, numbytes >> 2);
         offset = numbytes & -4;
         dest = (uint8 *)dest + offset;
         src = (uint8 *)src + offset;
         numbytes &= 3;
      }
  }
  printf("[END] numbytes: %d offset: %d\n", numbytes , offset);
}


// Default (8-bit, 1 byte at a time)
void * memcpy_8bit (void *dest, const void *src, size_t len)
{
  const uint8 *s = (uint8*)src;
  uint8 *d = (uint8*)dest;

  while (len--)
  {
    *d++ = *s++;
  }

  return dest;
}

void * memcpy_16bit(void *dest, const void *src, size_t len)
{
  const uint16* s = (uint16*)src;
  uint16* d = (uint16*)dest;

  while (len--)
  {
    *d++ = *s++;
  }

  return dest;
}

// 32-bit (4 bytes at a time - 1 pixel in a 32-bit linear frame buffer)
// Len is (# of total bytes/4), so it's "# of 32-bits"

void * memcpy_32bit(void *dest, const void *src, size_t len)
{
  const uint32* s = (uint32*)src;
  uint32* d = (uint32*)dest;

  while (len--)
  {
    *d++ = *s++;
  }

  return dest;
}
#endif