#pragma once
 
 
#include "stdint.h"
#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <memory.h>
 
class MyCharSet
{
public:
    MyCharSet();
    ~MyCharSet();
    static MyCharSet * getinstence();
    static void destoryinstence();
    int utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize);
    int unicode_to_utf8(uint16_t *in, int insize, uint8_t **out);
};