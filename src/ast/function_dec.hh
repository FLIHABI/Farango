#ifndef FUNCTION_DEC_HH
# define FUNCTION_DEC_HH


# include <memory>

# include "exp.hh"
# include "vardec.hh"
# include "function_prototype.hh"
# include "visitor.hh"

namespace ast
{
    class FunctionDec : public FunctionPrototype
    {
        public:
            FunctionDec(std::shared_ptr<FunctionPrototype> f, std::shared_ptr<Exp> body)
                : FunctionPrototype(*f)
                , body_(body)
            {};

            virtual ~FunctionDec()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> body_get()
            {
                return body_;
            }

            uint16_t reg_size_get()
            {
                return reg_size_;
            }

            void reg_size_set(uint16_t reg_)
            {
                reg_size_ = reg_;
            }

            uint16_t reg_offset_get()
            {
                return reg_offset_;
            }

            void reg_offset_set(uint16_t reg_)
            {
                reg_offset_ = reg_;
            }

            uint16_t function_offset_get()
            {
                return function_offset_;
            }

            void function_offset_set(uint16_t function_)
            {
                function_offset_ = function_;
            }

        private:
            std::shared_ptr<Exp> body_;
            uint16_t reg_size_;
            uint16_t reg_offset_;
            uint16_t function_offset_;

    };
}

#endif /* FUNCTION_DEC_HH */
