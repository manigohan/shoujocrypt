#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <device.h>

#define SERIAL_LEN 128

void disable_adb() {
    system("setprop sys.usb.config none");
    system("setprop persist.sys.usb.config none");
    system("stop adbd");
};

const char* get_sn() {
  static char serial[SERIAL_LEN] = {0};
  FILE *fp = popen("getprop ro.serialno", "r");
    if (fp) {
        if (fgets(serial, SERIAL_LEN, fp)) {
            // Remove trailing newline
            serial[strcspn(serial, "\n")] = 0;
            if (strlen(serial) > 0) {
                pclose(fp);
                return serial;
            }
        }
        pclose(fp);
  }
};