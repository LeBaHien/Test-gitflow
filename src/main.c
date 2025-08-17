#include "cbuffer.h"
cbuffer_t cb;
uint8_t cb_buff[6];
uint8_t a;
void main(void)
{
    cb_init(&cb, cb_buff, 100);
    cb_clear(&cb);
    char a[] = {0, 1, 2, 3, 4}; 
    cb_write(&cb, a, 5);
    char b[5] = {0, 0, 0, 0, 0};
    cb_read(&cb, b, 4);
    for(int i=0;i<5;i++){
        printf("%d ",b[i]);
    }
    printf("\n");
    int c[6] = {0, 0, 0, 0, 0, 0};
    cb_read(&cb, c, 6);
    for(int j=0;j<6;j++){
        printf("%d ",c[j]);
    }
}