#ifndef COMPILE_EMITTER_HH_
# define COMPILE_EMITTER_HH_

# include <commons/asm/bytecodes.hh>
# include <vector>
# include <ostream>

namespace compile {

    class UnfinishedBytecode
    {
        public:
            UnfinishedBytecode(Bytecode b);
            UnfinishedBytecode(Bytecode b, int64_t arg);

            Bytecode b_;
            std::vector<int64_t> args_;
            unsigned jump_flag; //Where it should jump
            unsigned flag; //Instruction flag
    };

    class Emitter final {
    public:
        template<Bytecode b>
        unsigned emit(int64_t arg);

        template<Bytecode b>
        unsigned emit();

        inline unsigned next_instruction_id() {
            return buf_.size();
        }

        inline unsigned get_current_length() {
            return current_length;
        }

        inline std::vector<UnfinishedBytecode>& buf_get() {
            return buf_;
        }

    private:
        std::vector<UnfinishedBytecode> buf_;
        unsigned current_length = 0;

    friend std::ostream& operator<<(std::ostream& os, const Emitter& e);
    };

    std::ostream& operator<<(std::ostream& os, const Emitter& e);
}

# include "emitter.hxx"

#endif /* !COMPILE_EMITTER_HH_ */
