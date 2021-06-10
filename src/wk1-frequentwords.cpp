// http://bioinformaticsalgorithms.com/data/debugdatasets/replication/FrequentWordsProblem.pdf
// http://bioinformaticsalgorithms.com/data/extradatasets/replication/frequent_words.txt

#include "os/os.h"
#include "util/hashtable.h"
#include "util/io.h"
#include "util/move.h"
#include "util/sort.h"
#include "util/string.h"
#include "util/string-view.h"
#include "util/string2.h"
#include "util/vector.h"

#include "basename.cpp"
#include "join.cpp"

static Vector<String>
frequentWords(StringView text, size_t k) noexcept {
    Hashmap<String, size_t> counts;
    size_t highest = 0;

    for (size_t i = 0; i <= text.size - k; i++) {
        size_t count = ++counts[text.substr(i, k)];
        highest = highest > count ? highest : count;
    }

    Vector<String> words;
    for (auto& entry : counts) {
        if (entry.value == highest) {
            words.push_back(entry.key);
        }
    }
    return words;
}

static void
test(StringView text, size_t k) noexcept {
    Vector<String> words = frequentWords(text, k);
    sortA(words);
    sout << join(words, " ") << '\n';
}

int
main(int argc, char **argv) noexcept {
    ReadLines lines(basename(argv[0]));
    for (StringView line = lines.next(); line.data; line = lines.next()) {
        Splits<' '> tokens(line);

        StringView text = tokens.next();
        String kstr = tokens.next();
        int k;
        parseInt(k, kstr);

        test(text, k);
    }
    return 0;
}
