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

    template<Bytecode b, typename T>
    unsigned Emitter::emit() {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has a parameter.");
        buf_.push_back(UnfinishedBytecode(b));

        current_length += 1 + sizeof(T);
        return buf_.size() - 1;
    }

    template<Bytecode b, unsigned size>
    unsigned Emitter::emit() {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has a parameter.");
        buf_.push_back(UnfinishedBytecode(b));

        current_length += 1 + size;
        return buf_.size() - 1;
    }

    template<Bytecode b, typename T>
    unsigned Emitter::emit(T element) {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has a parameter.");
        buf_.push_back(UnfinishedBytecode(b));
        buf_[buf_.size() - 1].add_operand<T>(element);

        current_length += 1 + sizeof(T);
        return buf_.size() - 1;
    }

    template<typename T>
    void UnfinishedBytecode::add_operand(T value)
    {
        vector_stream::write<T>(args_, value);
    }
}

#endif /* !EMITTER_HXX_ */
