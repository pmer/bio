// http://bioinformaticsalgorithms.com/data/debugdatasets/replication/ReverseComplementProblem.pdf
// http://bioinformaticsalgorithms.com/data/extradatasets/replication/reverse_complement.txt

#include "util/io.h"
#include "util/string.h"
#include "util/string-view.h"
#include "util/string2.h"

#include "basename.cpp"
#include "complement.cpp"

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
