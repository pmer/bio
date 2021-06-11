#include "util/string-view.h"
#include "util/string.h"

static char
complement(char c) {
    switch (c) {
        case 'A':
            return 'T';
        case 'T':
            return 'A';
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        default:
            __builtin_unreachable();
    }
}

static String
reverseComplement(StringView pattern) noexcept {
    String s;
    s.resize(pattern.size);
    for (size_t i = 0; i < pattern.size; i++) {
        s[pattern.size - i - 1] = complement(pattern[i]);
    }
    return s;
}
