/**
 ** \file symbol/symbol.cc
 ** \brief Implementation of misc::symbol.
 */

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "symbol.hh"

namespace misc
{
  symbol::symbol(const std::string& s)
    : unique<std::string>(s)
  {}

  symbol::symbol(const char* s)
    : unique<std::string>(std::string(s))
  {}

  symbol::~symbol()
  {}

  symbol::string_size_type
  symbol::string_map_size()
  {
    return object_map_size();
  }

  symbol
  symbol::fresh()
  {
    return fresh("a");
  }

  symbol
  symbol::fresh(const symbol& s)
  {
    /// Counter of unique symbols.
    static unsigned counter_ = 0;
    std::string str =
      s.object_get() + "_" + boost::lexical_cast<std::string>(counter_);
    ++counter_;
    return symbol(str);
  }

} // namespace symbol
