#include <iterator>
#include "emitter.hh"

namespace compile {

    std::ostream& operator<<(std::ostream& os, const Emitter& e) {
        auto dst = std::ostream_iterator<char>(os, "");
        std::copy(e.buf_.begin(), e.buf_.end(), dst);
        return os;
    }

}
