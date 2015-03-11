/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#ifndef MISC_SYMBOL_HXX
# define MISC_SYMBOL_HXX

# include "symbol.hh"

namespace misc
{
  inline const std::string&
  symbol::name_get() const
  {
    return *obj_;
  }

  inline symbol&
  symbol::operator=(const symbol& rhs)
  {
    unique<std::string>::operator=(rhs);
    return *this;
  }

  inline bool
  symbol::operator==(const symbol& rhs) const
  {
    return *obj_ == *rhs.obj_;
  }

  inline bool
  symbol::operator!=(const symbol& rhs) const
  {
    return !(*this == rhs);
  }

  inline std::ostream&
  operator<<(std::ostream& ostr, const symbol& the)
  {
    ostr << the.name_get();
    return ostr;
  }
}

#endif // !MISC_SYMBOL_HXX
