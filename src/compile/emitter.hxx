#ifndef EMITTER_HXX_
# define EMITTER_HXX_

# include <commons/utils/vector_stream.hxx>
# include "emitter.hh"

namespace compile {
    template<Bytecode b>
    void Emitter::emit() {
        static_assert(!bytecode::has_parameter(b),
                "Bytecode has a parameter.");

        buf_ << b;
    }

    template<Bytecode b, typename T>
    void Emitter::emit(T arg) {
        static_assert(bytecode::has_parameter(b),
                "Bytecode has no parameter.");

        buf_ << b << arg;
    }
}

#endif /* !EMITTER_HXX_ */
