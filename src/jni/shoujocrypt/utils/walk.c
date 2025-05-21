#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cryptutils.h>
#include <walk.h>

// Helper to remove ".enc" suffix for decryption
static void remove_enc_extension(const char *filename, char *output, size_t size) {
    size_t len = strlen(filename);
    if (len > 4 && strcmp(filename + len - 4, ".enc") == 0) {
        snprintf(output, size, "%.*s", (int)(len - 4), filename);
    } else {
        snprintf(output, size, "%s", filename);
    }
}

// Process each directory and apply encryption or decryption
static void process_directory(const char *path, const unsigned char *key, int encrypt_mode) {
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
            process_directory(full_path, key, encrypt_mode);
        } else if (S_ISREG(st.st_mode)) {
            char output_path[1024];

            if (encrypt_mode) {
                // Encryption: Append ".enc" extension
                snprintf(output_path, sizeof(output_path), "%s.enc", full_path);
                printf("Encrypting: %s -> %s\n", full_path, output_path);
                encrypt_file(full_path, output_path, key);
            } else {
                // Decryption: Remove ".enc" extension
                remove_enc_extension(full_path, output_path, sizeof(output_path));
                printf("Decrypting: %s -> %s\n", full_path, output_path);
                decrypt_file(full_path, output_path, key);
            }
        }
    }

    closedir(dir);
}

// Encrypt all files in the given directory
void walk_and_encrypt(const char *path, const unsigned char *key) {
    process_directory(path, key, 1);
}

// Decrypt all files in the given directory
void walk_and_decrypt(const char *path, const unsigned char *key) {
    process_directory(path, key, 0);
}
