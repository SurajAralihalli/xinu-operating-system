/* helperfunctions.c - helperfunctions */

#include <xinu.h>

int copyBuffer(char* toBuffer, char* fromBuffer, uint16 len)
{
    // int fromSize = strlen(fromBuffer);
    if(len < IPCX_MAXLEN)
    {
        strncpy(toBuffer, fromBuffer, len);
        // to be safe
        toBuffer[IPCX_MAXLEN - 1] = '\0';
        return len;
    }
    return -1;
    
}
