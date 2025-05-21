#ifndef CRYPTUTILS_H
#define CRYPTUTILS_H

void generate_key(const char *key_file_path);
int load_key(const char *key_file_path, unsigned char *key);
void encrypt_file(const char *input_path, const char *output_path, const unsigned char *key);
void decrypt_file(const char *input_path, const char *output_path, const unsigned char *key);

#endif
