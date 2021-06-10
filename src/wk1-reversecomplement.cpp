// http://bioinformaticsalgorithms.com/data/debugdatasets/replication/ReverseComplementProblem.pdf
// http://bioinformaticsalgorithms.com/data/extradatasets/replication/reverse_complement.txt

#include "util/io.h"
#include "util/string.h"
#include "util/string-view.h"
#include "util/string2.h"

#include "basename.cpp"

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

static void
test(StringView pattern) noexcept {
    sout << reverseComplement(pattern) << '\n';
}

int
main(int argc, char **argv) noexcept {
    ReadLines lines(basename(argv[0]));
    for (StringView line = lines.next(); line.data; line = lines.next()) {
        test(line);
    }
    return 0;
}
