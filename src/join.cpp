#include "util/string.h"
#include "util/string-view.h"
#include "util/vector.h"

template<typename T>
static String
join(Vector<T> ss, StringView separator) noexcept {
    String s;
    for (size_t i = 0; i < ss.size; i++) {
        if (i != 0) {
            s << ' ';
        }
        s << ss[i];
    }
    return s;
}
