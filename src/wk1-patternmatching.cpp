// The Pattern Matching Problem
//
// Input: Two strings, Pattern and Genome
// Output: All starting positions where Pattern appears as a substring of Genome
//
// https://stepik.org/lesson/3/step/5?unit=8232
// http://bioinformaticsalgorithms.com/data/debugdatasets/replication/PatternMatchingProblem.pdf

#include "util/assert.h"
#include "util/io.h"
#include "util/int.h"
#include "util/string.h"
#include "util/string-view.h"
#include "util/string2.h"

#include "basename.cpp"
#include "join.cpp"

#define KMP_NO_MATCH SIZE_MAX

// Knuth-Morris-Pratt pattern matching
//
// See
//   Knuth, D. E., Morris, Jr, J. H., & Pratt, V. R. (1977). Fast pattern
//   matching in strings. SIAM Journal on Computing, 6(2), 323-350.
class KMP {
 public:
    KMP(StringView pattern) : pattern(pattern) {
        assert_(pattern.size > 0);
        next.resize(pattern.size);

        // pattern = "aabaabaaa"
        // next    =  010123451

        // pattern = "abcabcadab
        // next    =  0110110501
        //
        // indices off by one, probably

        for (size_t i = 1; i < pattern.size; i++) {
            ;
        }
    }

    size_t
    match(StringView text, size_t k = 0) noexcept {
        size_t m = pattern.size;
        size_t n = text.size;

        size_t j = 0;
        while (j < pattern.size && k < text.size) {
            while (j > 0 && pattern[j] != text[k]) {
                j = next[j];
            }
            j++;
            k++;
        }

        if (j == pattern.size) {
            return k - pattern.size;
        }
        else {
            return KMP_NO_MATCH;
        }
    }

 public:
    StringView pattern;
    String next;  // Partial match table.
};

static Vector<size_t>
patternMatchKMP(StringView pattern, StringView text) noexcept {
    Vector<size_t> matches;
    KMP kmp(pattern);

    size_t i = 0;
    while (true) {
        size_t position = kmp.match(text, i);
        if (position == KMP_NO_MATCH) {
            return matches;
        }
        matches.push_back(position);
        i = position + 1;
    }
}

static Vector<size_t>
patternMatchNaive(StringView pattern, StringView text) noexcept {
    Vector<size_t> matches;

    #pragma unroll
    for (size_t i = 0; i <= text.size - pattern.size; i++) {
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

#define patternMatch patternMatchNaive

static void
test(StringView pattern, StringView text) noexcept {
    sout << join(patternMatch(pattern, text), " ") << '\n';
}

int
main(int argc, char **argv) noexcept {
    ReadLines lines(basename(argv[0]));
    for (StringView line = lines.next(); line.data; line = lines.next()) {
        Splits<' '> splits(line);
        StringView pattern = splits.next();
        StringView text = splits.next();
        test(pattern, text);
    }
    return 0;
}
