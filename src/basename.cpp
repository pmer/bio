#include "os/os.h"
#include "util/string-view.h"

static StringView
basename(StringView exe) noexcept {
    StringPosition slash = exe.rfind(dirSeparator);
    if (slash == SV_NOT_FOUND) {
        return exe;
    }
    else {
        return exe.substr(slash + 1);
    }
}
