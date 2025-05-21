#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cryptutils.h>
#include <walk.h>

void walk_and_encrypt(const char *path, const unsigned char *key) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir failed");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) {
            perror("stat failed");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            walk_and_encrypt(full_path, key);
        } else if (S_ISREG(st.st_mode)) {
            // Create output path: append ".enc" to filename
            char output_path[1024];
            snprintf(output_path, sizeof(output_path), "%s.enc", full_path);

            printf("Encrypting: %s -> %s\n", full_path, output_path);
            encrypt_file(full_path, output_path, key);
        }
    }

    closedir(dir);
}

void walk_and_decrypt(const char *path, const unsigned char *key) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir failed");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) {
            perror("stat failed");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            walk_and_encrypt(full_path, key);
        } else if (S_ISREG(st.st_mode)) {
            decrypt_file(full_path, full_path, key);
        }
    }

    closedir(dir);
}