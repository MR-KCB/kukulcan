import argparse
import os
import os.path
from struct import unpack, calcsize


#=============================================
# Config section and variables
#=============================================

OUT_FILE_NAME = 'dumpParser.txt'

log_elements = list()
print_text = list()
FORMAT = '<BBLLB'
size = calcsize(FORMAT)
##############################################




#=============================================
# functions/methods
#=============================================
MODULE_DEFINITIONS = {
'eMODULE_1'                          :   0x00,
'eMODULE_2'                          :   0x01,
'eMODULE_3'                          :   0x02,
'eMODULE_3'                          :   0x03,
'eNOF_DEBUG_MODULE'                  :   0x04,
}

#=============================================
# functions/methods
#=============================================
def parseModule(inValue):
   retVal = ''
   for key,value in MODULE_DEFINITIONS.items():
      if (inValue == value):
         retVal = key
         break
   return retVal


## @brief   Swap endianned for uint16 from MSB to LSB and viceversa
#  @param   inString: input string hex value.
#  @return  Return int value with new endianess.
def swapByteEndianessU16(inValue):
   retVal = ((int(inValue,16) >> 8) & 0x00FF) | \
            ((int(inValue,16) & 0x00FF) << 8) 
   return retVal

## @brief   Swap endianned for uint16 from MSB to LSB and viceversa
#  @param   inString: input string hex value.
#  @return  Return int value with new endianess.
def swapByteEndianessU32(inValue):
   print(inValue)
   temp1 = ((int(inValue,16) >> 24) & 0x000000FF) | \
           ((int(inValue,16) & 0x000000FF) << 24)
   temp2 = ((int(inValue,16) >> 16) & 0x0000FF00) | \
           ((int(inValue,16) & 0x0000FF00) << 16)
   retVal = temp1 | temp2
   return retVal

#=============================================
# get line number
#=============================================
def getLineNumber(inValue):
    print(inValue)
    strInValue = str(inValue)
    return str((strInValue))


#=============================================
# convert dec and hex values
#=============================================
def printDecAndHex(value):
    value_int = int(value)
    return ( str(value_int) + "("+hex(value) +")")


#=============================================
# read bin dump
#=============================================
def readBin(arg1):
   with open(arg1, 'rb') as file:
      binary_data = file.read(size)
      log_elements.append(binary_data)
      while binary_data:
         binary_data = file.read(size)
         log_elements.append(binary_data)


def printRawData(inData, slots):
   outStrData = "[ "
   for x in range(slots):
      outStrData += hex(inData[x]) 
      if x != slots-1:
         outStrData += ' ,'
      else:
         outStrData += ' ]'
   
   return outStrData

#=============================================
# Split and print the dump results
#=============================================
def splitFrame(arg1):
    i = 0
    for dump in log_elements:
        i += 1
        if len(dump) == size:
            elements = unpack(FORMAT, dump)
            print_text.append(("="*30+">> "+str(i)+" <<"+"="*30)+ '\n')
            print_text.append("RAW Data                        ->\t" + printRawData(elements, 5) + '\n')
            print_text.append("uint8  Debug Module             ->\t" + parseModule(elements[0])+ '\n')
            print_text.append("uint8  Debug Value              ->\t" + printDecAndHex(elements[1])+ '\n')
            print_text.append("uint32 line Number              ->\t" + getLineNumber(elements[2])+ '\n')
            print_text.append("uint32 time Stamp               ->\t" + printDecAndHex(elements[3])+ '\n')
            print_text.append("uint8 teminator                 ->\t" + printDecAndHex(elements[4])+ '\n')
        else:
            print_text.append(("="*30+">> "+str(i)+" <<"+"="*30)+ '\n')
            print_text.append("No enough data to be interpreted -> Remaining: "+str(len(dump))+'\n')
            print_text.append(str(dump)+ '\n')

def saveTxt():
    if os.path.exists(OUT_FILE_NAME):
        os.remove(OUT_FILE_NAME)
    with open(OUT_FILE_NAME, 'w') as f:
        f.writelines(print_text)

def printData():
    i = 0
    for element in print_text:
        i += 1
        print(element)
        #if (i == 10):
        #    input("Press Enter to continue...")


#=============================================
# main function
#=============================================
def main(arg1):
  readBin(arg1)
  splitFrame(arg1)
  printData()
  saveTxt()

#=============================================
# Entry point
#=============================================
if __name__ == '__main__':
  parser = argparse.ArgumentParser(
                  prog='binParser',
                  description='read binary and interpreted the values',
                  epilog='=.=')
  parser.add_argument("-f", help='Bin file with directory')
  args = parser.parse_args()
  main(args.f)