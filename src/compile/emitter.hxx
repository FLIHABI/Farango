#ifndef EMITTER_HXX_
# define EMITTER_HXX_

# include <commons/utils/vector_stream.hxx>
# include "emitter.hh"

namespace compile {
    template<Bytecode b>
    unsigned Emitter::emit() {
        static_assert(!bytecode::has_parameter(b),
                "Bytecode has a parameter.");

        buf_.push_back(UnfinishedBytecode(b));
        current_length += 1;
        return buf_.size() - 1;
    }

    template<Bytecode b>
    unsigned Emitter::emit(int64_t arg) {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has no parameter.");

        buf_.push_back(UnfinishedBytecode(b, arg));
        current_length += 1 + sizeof(arg);
        return buf_.size() - 1;
    }
}

#endif /* !EMITTER_HXX_ */
