#include <iostream>
#include <iterator>
#include "commons/utils/vector_stream.hxx"
#include "emitter.hh"

namespace compile {

    UnfinishedBytecode::UnfinishedBytecode(Bytecode b) {
        vector_stream::write<char>(args_, b);
    }

    std::ostream& operator<<(std::ostream& os, const Emitter& e) {
        for (auto& Ub : e.buf_) {
            auto dst = std::ostream_iterator<char>(os, "");
            std::copy(Ub.args_.begin(), Ub.args_.end(), dst);
        }
        return os;
    }

}
