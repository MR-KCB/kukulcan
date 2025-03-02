/**
 * @brief append new strings to old string.
 * 
 * @param[out] oldString      The old strind where the new string will be append, the terminator char will me removed
 * @param[in]  string2Append  The new string to be added into old string with null terminator
 * @param[in]  maxLength      The max length is used to abort the search in case null terminator is missing.
 *                            Strongly suggest to fit with the size of the first string + size of second string (with terminator)
 * @return     uint8          String size without terminator if null pointer is received 0 will be returned
 * 
 * NOTE: The maxLength argument is used as guard protection, both string must contain the NULL Terminator character ('\0') 
 *       for a correct use of this function
 */
uint8 custom_appendStr(uint8 *oldString, uint8 const * string2Append, uint8 maxLength);
uint8 custom_appendStr(uint8 *oldString, uint8 const * string2Append, uint8 maxLength)
{
    uint8 oldString_offset = 0U;
    uint8 string2Append_offset = 0U;
    uint8 isNullTerminatorFound = 0U;
    if ((NULL_PTR != oldString) && (NULL_PTR != string2Append))
    {
      for (oldString_offset = 0U ; ((oldString_offset < maxLength) && ('\0' != string2Append[string2Append_offset])); oldString_offset++)
      {
         if (('\0' == oldString[oldString_offset]) || (isNullTerminatorFound == 1U))
         {
            isNullTerminatorFound = 1U;
            oldString[oldString_offset] = string2Append[string2Append_offset++];
         }
      }
    }
    return oldString_offset;
}

/**
 * @brief concatenate two string into new strings.
 * 
 * @param[out] outputString   The result of concatenate two strings 
 * @param[in]  maxLength      The max length is used to limit the buffer size for the new string, if the size of two strings is bigger 
 *                            than maxLength the output string will be truncated.
 * @param[in]  inputString1   First string part,  null terminator character is required
 * @param[in]  inputString2   Second string part, null terminator character is required
 * @return     uint8          String size without terminator if null pointer is received 0 will be returned
 * 
 * NOTE: The maxLength argument is used as guard protection, both string must contain the NULL Terminator character ('\0') 
 *       for a correct use of this function
 */
uint8 custom_concatenateStr(uint8 *outputString, uint8 maxLength, uint8 const * inputString1, uint8 const * inputString2);
uint8 custom_concatenateStr(uint8 *outputString, uint8 maxLength, uint8 const * inputString1, uint8 const * inputString2)
{
    uint8 inputString1_offset = 0U;
    uint8 inputString2_offset = 0U;

    if ((NULL_PTR != inputString1) && (NULL_PTR != inputString2) && ((NULL_PTR != outputString)))
    {
      for (inputString1_offset = 0U ; '\0' != inputString1[inputString1_offset]; inputString1_offset++)
      {
         outputString[inputString1_offset] = inputString1[inputString1_offset];
      }

      for (inputString2_offset = 0U ; ((inputString1_offset + inputString2_offset) < maxLength) && ('\0' != inputString2[inputString2_offset]) ; inputString2_offset++)
      {
         outputString[inputString1_offset+inputString2_offset] = inputString2[inputString2_offset];
      }
    }
    return (inputString1_offset+inputString2_offset);
}

/**
 * @brief Convert integer value to ASCII 
 * 
 * @param[out] outStr buffer where the ASCII Value will be save
 * @param[in]  intVal value to conver to ASCII (max 65535)
 * @return     uint16 quantity of bytes used of the current buffer, if null pointer is received
 *                    0 will be returned
 * 
 * NOTE: The NULL terminator character was added in the end of the buffer and 
 *       was included as part of the size to report
 */
uint16 custom_itoaU16(uint8 *outStr, uint16 intVal);
uint16 custom_itoaU16(uint8 *outStr, uint16 intVal)
{
    uint8 slot = 0u;
    uint8 remain = 0u;
    if (NULL_PTR != outStr)
    {
        if (0U == intVal)
        {
            outStr[slot++] = '0';
        }
        else
        {
            /* Convert values to ASCII endianed inverted */
            while ( intVal != 0u)
            {
                remain = intVal % 10U;
                outStr[slot++] = remain + '0';
                intVal /= 10U;
            }

            /* Swap endianes */
            for (int i = 0U ; i < (slot>>1U) ; i++)
            {
                outStr[i] ^= outStr[slot-1U-i];
                outStr[slot-1U-i] ^= outStr[i];
                outStr[i] ^= outStr[slot-1U-i];
            }
        }
      
      /* Append NULL character */
      outStr[slot++] = '\0';
    }
    
    /* length size of the string include terminator \0 */
    return slot;
}