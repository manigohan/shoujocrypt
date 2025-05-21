#ifndef WEB_H
#define WEB_H

int get(const char *url, long *status_code);
int post(const char *url, const char *data);

#endif
