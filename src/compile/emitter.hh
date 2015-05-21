#ifndef COMPILE_EMITTER_HH_
# define COMPILE_EMITTER_HH_

# include <commons/asm/bytecodes.hh>
# include <vector>
# include <ostream>

namespace compile {

    class Emitter;
    class Compile;

    class UnfinishedBytecode
    {
        public:
            UnfinishedBytecode(Bytecode b);

            template<typename T>
            void add_operand(T value);
        private:
            std::vector<char> args_;

        friend std::ostream& operator<<(std::ostream& os, const Emitter& e);
        friend Emitter;
        friend Compile;
    };

    class Emitter final {
    public:
        template<Bytecode b, typename T>
        unsigned emit(T arg);

        template<Bytecode b, unsigned size>
        unsigned emit();

        template<Bytecode b, typename T>
        unsigned emit();

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
