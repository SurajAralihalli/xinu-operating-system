/* helperfunctions.c - helperfunctions */

#include <xinu.h>

int copyBuffer(char* toBuffer, char* fromBuffer, uint16 len)
{
    // int fromSize = strlen(fromBuffer);
    if(len <= IPCX_MAXLEN)
    {
        memcpy((void *)toBuffer, (void *)fromBuffer, len);
        return len;
    }
    return -1;
}
