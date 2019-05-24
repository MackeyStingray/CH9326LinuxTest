#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/ch9326.h"

int main()
{
    char buf[128];
    int i;

    memset(buf, 0, sizeof(buf));

    int r = ch9326_find();

    if(r == 0) {
        printf("can not find 9326 device.\n");
        return -1;
    } else {
        printf("found %d 9326\n", r);
    }

    r = ch9326_open(0);
    printf("open : %d\n", r);
    if(r == 0) {
        printf("ch9326_open failed.\n");
        return -1;
    }

    r = ch9326_set(0, B115200, P_NONE, STOP_1, BIT_8, 30);
    printf("set : %d\n", r);
    if(r == 0) {
        printf("ch9326_set failed.\n");
        return -1;
    }

    r = ch9326_set_gpiodir(0, 0x0F);
    printf("set gpio dir: %d\n", r);
    if(r == 0) {
        printf("ch9326_set failed.\n");
        return -1;
    }

//    r = ch9326_set_gpio(0, 0, 0);
//    printf("set gpio: %d\n", r);
//    if(r == 0) {
//        printf("ch9326_set failed.\n");
//        return -1;
//    }
//
//    r = ch9326_get_gpio(0, &data);
//    printf("get gpio: %d\n", r);
//    if(r == 0) {
//        printf("ch9326_set failed.\n");
//        return -1;
//    }

    r = ch9326_connected(0);
    printf("connected : %d\n", r);
    if(r == 0) {
        printf("ch9326_set failed.\n");
        return -1;
    }

    r = ch9326_get_manufacturer_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get ch9326_get_manufacturer_string error.\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }

    r = ch9326_get_product_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get prod error\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }

    r = ch9326_get_serial_number_string(0, (unsigned char *)buf, 128);
    if (r == 0)
        printf("get serial error\n");
    else if (r == 1) {
        for (i = 0; i < 128; i++)
            printf("%x ", buf[i]);
        printf("\n");
    }

    for (i = 0; i < 100000; i++) {
        snprintf(buf,sizeof(buf),"Hello, %d.\n",i);
        r = ch9326_send(0, (unsigned char *)buf, strlen(buf));
        printf("send : %d\n", r);

        sleep(1);

        memset(buf,0,sizeof(buf));
        r = ch9326_recv(0, buf, sizeof(buf));
        printf("receive : %d \n", r);
        if(r > 0) {
            printf("%s\n",buf);
        }
        ch9326_set_gpiodata(0,0x04);
        sleep(1);
        ch9326_set_gpiodata(0,0x08);
    }

    r = ch9326_close(0);
    printf("close : %d\n", r);
    return 0;
}

