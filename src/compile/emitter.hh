#ifndef COMPILE_EMITTER_HH_
# define COMPILE_EMITTER_HH_

# include <commons/asm/bytecodes.hh>
# include <vector>
# include <ostream>

namespace compile {
    class Emitter final {
    public:
        template<Bytecode b, typename T>
        void emit(T arg);

        template<Bytecode b>
        void emit();

    private:
        std::vector<char> buf_;

    friend std::ostream& operator<<(std::ostream& os, const Emitter& e);
    };

}

# include "emitter.hxx"

#endif /* !COMPILE_EMITTER_HH_ */
