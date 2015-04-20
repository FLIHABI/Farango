#ifndef EMITTER_HXX_
# define EMITTER_HXX_

# include <commons/utils/vector_stream.hxx>
# include "emitter.hh"

namespace compile {
    template<Bytecode b>
    void Emitter::emit() {
        static_assert(!bytecode::has_parameter(b),
                "Bytecode has a parameter.");

        const char bytecode = b;
        buf_.push_back(bytecode);
    }

    template<Bytecode b, typename T>
    void Emitter::emit(T arg) {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has no parameter.");

        const char bytecode = b;
        buf_.push_back(bytecode);
        vector_stream::write(buf_, arg);
    }
}

#endif /* !EMITTER_HXX_ */
