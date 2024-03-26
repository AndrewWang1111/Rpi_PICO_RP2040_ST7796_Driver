#include <ctype.h>
#include <stdbool.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "driver.h"
#include <hardware/vreg.h>
#include "receiver.h"
#include "2.h"

#include "f_util.h"
#include "hw_config.h"
#include "my_debug.h"
#include "rtc.h"
#include "sd_card.h"
#include "ff.h"     /* Obtains integer types */
#include "diskio.h" /* Declarations of disk functions */

using namespace std;
sd_card_t *pSD = nullptr;
void sd_card_mount(sd_card_t *sd);
sd_card_t *sd_get_by_name(const char *const name);
FATFS *sd_get_fs_by_name(const char *name);
UartReceiver recever(uart0, 0, 1, 115200);

uint bytesAlreadyRead = 0;
uint fNum = 0;
uint currentIndex = 0;
uint currentFrameIndex = 0;
char fileName[16];
char buffer[512];
char BmpHeader[128];

int main()
{
    set_sys_clock_khz(266 * 1000, true);
    stdio_init_all();
    stdio_uart_init();
    time_init();
    ST7796 disp;
    disp.LcdInit();
    disp.DrawBmp(0, 0, 320, 480, IMG2);

    while (1)
    {
        ;
    }
    return 0;
}

sd_card_t *sd_get_by_name(const char *const name)
{
    for (size_t i = 0; i < sd_get_num(); ++i)
        if (0 == strcmp(sd_get_by_num(i)->pcName, name))
            return sd_get_by_num(i);
    DBG_PRINTF("%s: unknown name %s\n", __func__, name);
    return NULL;
}

FATFS *sd_get_fs_by_name(const char *name)
{
    for (size_t i = 0; i < sd_get_num(); ++i)
        if (0 == strcmp(sd_get_by_num(i)->pcName, name))
            return &sd_get_by_num(i)->fatfs;
    DBG_PRINTF("%s: unknown name %s\n", __func__, name);
    return NULL;
}

void sd_card_mount(sd_card_t *sd)
{
    DWORD fre_clust, fre_sect, tot_sect;
    const char *arg1 = strtok(NULL, " ");
    if (!arg1)
        arg1 = sd_get_by_num(0)->pcName;
    FATFS *p_fs = sd_get_fs_by_name(arg1);
    if (!p_fs)
    {
        printf("Unknown logical drive number: \"%s\"\n", arg1);
    }
    FRESULT fr = f_mount(p_fs, arg1, 1);
    if (FR_OK != fr)
    {
        printf("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    }
    pSD = sd_get_by_name(arg1);
    myASSERT(pSD);
    pSD->mounted = true;
    printf("sdcard mounted ok : %s\n", pSD->pcName);
    fr = f_getfree(arg1, &fre_clust, &p_fs);
    if (FR_OK != fr)
    {
        printf("f_getfree error: %s (%d)\n", FRESULT_str(fr), fr);
    }
    /* Get total sectors and free sectors */
    tot_sect = (p_fs->n_fatent - 2) * p_fs->csize;
    fre_sect = fre_clust * p_fs->csize;
    /* Print the free space (assuming 512 bytes/sector) */
    printf("%10lu KiB total drive space.\n%10lu KiB available.\n", tot_sect / 2,
           fre_sect / 2);
}