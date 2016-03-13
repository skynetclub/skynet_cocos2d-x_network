#include "MyCharSet.h"
 
static MyCharSet *_MyCharSet = NULL;
MyCharSet::MyCharSet()
{
}
 
 
MyCharSet::~MyCharSet()
{
}
 
MyCharSet * MyCharSet::getinstence()
{
    if (_MyCharSet == NULL)
    {
        _MyCharSet = new MyCharSet();
    }
    return _MyCharSet;
}
void MyCharSet::destoryinstence()
{
    if (_MyCharSet != NULL)
    {
        delete _MyCharSet;
    }
}
 
int MyCharSet::utf8_to_unicode(uint8_t *in, uint16_t **out, int *outsize)
{
    uint8_t *p = in;
    uint16_t *result = NULL;
    int resultsize = 0;
    uint8_t *tmp = NULL;
 
    result = (uint16_t *)malloc(strlen((char *)in) * 2 + 2); /* should be enough */
    memset(result, 0, strlen((char*)in) * 2 + 2);
    tmp = (uint8_t *)result;
 
    while (*p)
    {
        if (*p >= 0x00 && *p <= 0x7f)
        {
            *tmp = *p;
            tmp++;
            *tmp = '\0';
            resultsize += 1;
        }
        else if ((*p & (0xff << 5)) == 0xc0)
        {
            uint16_t t = 0;
            uint8_t t1 = 0;
            uint8_t t2 = 0;
 
            t1 = *p & (0xff >> 3);
            p++;
            t2 = *p & (0xff >> 2);
 
            *tmp = t2 | ((t1 & (0xff >> 6)) << 6);//t1 >> 2;
            tmp++;
 
            *tmp = t1 >> 2;//t2 | ((t1 & (0xff >> 6)) << 6);
            tmp++;
 
            resultsize += 1;
        }
        else if ((*p & (0xff << 4)) == 0xe0)
        {
            uint16_t t = 0;
            uint8_t t1 = 0;
            uint8_t t2 = 0;
            uint8_t t3 = 0;
 
            t1 = *p & (0xff >> 3);
            p++;
            t2 = *p & (0xff >> 2);
            p++;
            t3 = *p & (0xff >> 2);
 
            //Little Endian
            *tmp = ((t2 & (0xff >> 6)) << 6) | t3;//(t1 << 4) | (t2 >> 2);
            tmp++;
 
            *tmp = (t1 << 4) | (t2 >> 2);//((t2 & (0xff >> 6)) << 6) | t3;
            tmp++;
            resultsize += 1;
        }
 
        p++;
    }
 
    //*tmp = '\0';
    //tmp++;
    //*tmp = '\0';
    //resultsize += 2;
 
    //*out = result;
    //*outsize = resultsize;
    return resultsize;
}
 
int MyCharSet::unicode_to_utf8(uint16_t *in, int insize, uint8_t **out)
{
    int i = 0;
    int outsize = 0;
    int charscount = 0;
    uint8_t *result = NULL;
    uint8_t *tmp = NULL;
 
    charscount = insize / sizeof(uint16_t);
    result = (uint8_t *)malloc(charscount * 3 + 1);
    memset(result, 0, charscount * 3 + 1);
    tmp = result;
 
    for (i = 0; i < charscount; i++)
    {
        uint16_t unicode = in[i];
 
        if (unicode >= 0x0000 && unicode <= 0x007f)
        {
            *tmp = (uint8_t)unicode;
            tmp += 1;
            outsize += 1;
        }
        else if (unicode >= 0x0080 && unicode <= 0x07ff)
        {
            *tmp = 0xc0 | (unicode >> 6);
            tmp += 1;
            *tmp = 0x80 | (unicode & (0xff >> 2));
            tmp += 1;
            outsize += 2;
        }
        else if (unicode >= 0x0800 && unicode <= 0xffff)
        {
            *tmp = 0xe0 | (unicode >> 12);
            tmp += 1;
            *tmp = 0x80 | (unicode >> 6 & 0x00ff);
            tmp += 1;
            *tmp = 0x80 | (unicode & (0xff >> 2));
            tmp += 1;
            outsize += 3;
        }
 
    }
 
    *tmp = '\0';
    *out = result;
    return outsize;
}