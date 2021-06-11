// Exercise Break
//
// Exercise Break: Return a space-separated list of starting positions (in
// increasing order) where CTTGATCAT appears as a substring in the Vibrio
// cholerae genome.
//
// https://stepik.org/lesson/3/step/6?unit=8232
// https://stepik.org/media/attachments/lessons/3/Vibrio_cholerae.txt

#include "util/assert.h"
#include "util/io.h"
#include "util/int.h"
#include "util/string.h"
#include "util/string-view.h"
#include "util/string2.h"

#include "basename.cpp"
#include "join.cpp"

static Vector<size_t>
patternMatch(StringView pattern, StringView text) noexcept {
    Vector<size_t> matches;

    #pragma unroll
    for (size_t i = 0; i <= text.size - pattern.size; i++) {
        if (i == 116556) {
            debugger();
        }

        size_t j;

        #pragma unroll
        for (j = 0; j < pattern.size; j++) {
            if (pattern[j] != text[i + j]) {
                break;
            }
        }

        if (j == pattern.size) {
            matches.push_back(i);
        }
    }
    return matches;
}

static void
test(StringView pattern, StringView text) noexcept {
    sout << join(patternMatch(pattern, text), " ") << '\n';
}

int
main(int argc, char **argv) noexcept {
    String text;

    bool ok = readFile(basename(argv[0]), text);
    assert_(ok);
    (void)ok;

    assert_(text.size == 1108251);

    test("CTTGATCAT", text);
    return 0;
}
