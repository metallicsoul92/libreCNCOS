#include "../../../include/kernel/tty.h"
#include "../include/string.h"
#include "../include/stdarg.h"
#include "../include/stdio.h"
#include "../include/stdbool.h"
#include "../include/limits.h"

static bool print_to_buffer(char* buffer, size_t* written, const char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[*written] = data[i];
        (*written)++;
    }
    return true;
}

int vsprintf(char* buffer, const char* fmt, va_list parameters) {
    size_t written = 0;

    while (*fmt != '\0') {
        size_t maxrem = INT_MAX - written;

        if (fmt[0] != '%' || fmt[1] == '%') {
            if (fmt[0] == '%')
                fmt++;
            size_t amount = 1;
            while (fmt[amount] && fmt[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print_to_buffer(buffer, &written, fmt, amount))
                return -1;
            fmt += amount;
            continue;
        }

        const char* format_begun_at = fmt++;

        static char temp_buffer[64];
        memset(&temp_buffer, 0, sizeof(temp_buffer));

        switch (*fmt) {
        case 'c':
            fmt++;
            {
                char c = (char) va_arg(parameters, int /* char promotes to int */);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, &c, sizeof(c)))
                    return -1;
                written++;
            }
            break;
        case 's':
            fmt++;
            {
                const char* str = va_arg(parameters, const char*);
                size_t len = strlen(str);
                if (maxrem < len) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, str, len))
                    return -1;
                written += len;
            }
            break;
        case 'd':
            fmt++;
            {
                int i = (int) va_arg(parameters, int);
                char* c = kitoa(i, temp_buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        case 'u':
            fmt++;
            {
                unsigned int i = (unsigned int) va_arg(parameters, unsigned int);
                char* c = kuitoa(i, temp_buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        case 'U':
            fmt++;
            {
                unsigned long long i = (unsigned long long) va_arg(parameters, unsigned long long);
                char* c = kulltoa(i, temp_buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        case 'l':
            fmt++;
            {
                long long i = (long long) va_arg(parameters, long long);
                char* c = klltoa(i, temp_buffer);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        case 'x':
            fmt++;
            {
                unsigned int i = (unsigned int) va_arg(parameters, unsigned int);
                char* c = kuitoab(i, temp_buffer, 16);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        case 'X':
            fmt++;
            {
                unsigned long long i = (unsigned long long) va_arg(parameters, unsigned long long);
                char* c = kulltoab(i, temp_buffer, 16);
                size_t len = strlen(c);
                if (!maxrem) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                if (!print_to_buffer(buffer, &written, c, len))
                    return -1;
                written += len;
            }
            break;
        default:
            fmt = format_begun_at;
            size_t len = strlen(fmt);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print_to_buffer(buffer, &written, fmt, len))
                return -1;
            written += len;
            fmt += len;
            break;
        }
    }

    buffer[written] = '\0'; // Null-terminate the string
    return written;
}
