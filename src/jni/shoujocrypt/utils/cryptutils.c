#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

#include <errr.h>
#include <cryptutils.h>

void generate_key(const char *key_file_path) {
    unsigned char key[16];  // AES-128

    if (!RAND_bytes(key, sizeof(key))) {
        fprintf(stderr, "Error generating random key\n");
        return;
    }

    FILE *key_file = fopen(key_file_path, "wb");
    if (!key_file) {
        fprintf(stderr, "Error opening key file for writing\n");
        return;
    }
    
    fwrite(key, 1, sizeof(key), key_file);
    fclose(key_file);
}

int load_key(const char *key_file_path, unsigned char *key) {
    FILE *key_file = fopen(key_file_path, "rb");
    if (!key_file) {
        fprintf(stderr, "Error opening key file for reading\n");
        return 0;
    }

    fread(key, 1, 16, key_file);  // AES-128 key
    fclose(key_file);
    return 1;
}

void encrypt_file(const char *input_path, const char *output_path, const unsigned char *key) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char input_block[AES_BLOCK_SIZE];
    unsigned char encrypted_block[AES_BLOCK_SIZE];

    FILE *in = fopen(input_path, "rb");
    FILE *out = fopen(output_path, "wb");

    if (!in || !out) handle_err();

    // Generate and write random IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) handle_err();
    fwrite(iv, 1, AES_BLOCK_SIZE, out);

    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) handle_err();

    size_t bytes_read;
    while ((bytes_read = fread(input_block, 1, AES_BLOCK_SIZE, in)) > 0) {
        if (bytes_read < AES_BLOCK_SIZE) {
            // Simple zero-padding (not PKCS#7)
            memset(input_block + bytes_read, 0, AES_BLOCK_SIZE - bytes_read);
        }

        AES_cbc_encrypt(input_block, encrypted_block, AES_BLOCK_SIZE, &aes_key, iv, AES_ENCRYPT);
        fwrite(encrypted_block, 1, AES_BLOCK_SIZE, out);
    }

    fclose(in);
    fclose(out);
}

void decrypt_file(const char *input_path, const char *output_path, const unsigned char *key) {
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE];
    unsigned char input_block[AES_BLOCK_SIZE];
    unsigned char decrypted_block[AES_BLOCK_SIZE];

    FILE *in = fopen(input_path, "rb");
    FILE *out = fopen(output_path, "wb");

    if (!in || !out) handle_err();

    // Read IV from file
    if (fread(iv, 1, AES_BLOCK_SIZE, in) != AES_BLOCK_SIZE) handle_err();

    if (AES_set_decrypt_key(key, 128, &aes_key) < 0) handle_err();

    size_t bytes_read;
    while ((bytes_read = fread(input_block, 1, AES_BLOCK_SIZE, in)) > 0) {
        AES_cbc_encrypt(input_block, decrypted_block, AES_BLOCK_SIZE, &aes_key, iv, AES_DECRYPT);
        fwrite(decrypted_block, 1, AES_BLOCK_SIZE, out); // No padding check here
    }

    fclose(in);
    fclose(out);
}