#include <iostream>
#include <iterator>
#include "commons/utils/vector_stream.hxx"
#include "emitter.hh"

namespace compile {

    UnfinishedBytecode::UnfinishedBytecode(Bytecode b)
        : b_(b)
    {}

    UnfinishedBytecode::UnfinishedBytecode(Bytecode b, int64_t arg)
        : b_(b)
    {
        args_.push_back(arg);
    }

    std::ostream& operator<<(std::ostream& os, const Emitter& e) {
        std::vector<char> buffer;
        for (auto& Ub : e.buf_) {
            const char bytecode = Ub.b_;
            buffer.push_back(bytecode);
            for (auto args : Ub.args_) {
                vector_stream::write(buffer, args);
            }
        }

        auto dst = std::ostream_iterator<char>(os, "");
        std::copy(buffer.begin(), buffer.end(), dst);

        return os;
    }

}
