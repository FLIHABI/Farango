/**
 ** \file misc/indent.cc
 ** \brief Implementation of indentation relative functions.
 **/

#include <iomanip>
#include <ostream>

#include <lib/indent.hh>

namespace misc
{

  namespace
  {
    /// The current indentation level for \a o.
    inline long int& indent(std::ostream& o)
    {
      // The slot to store the current indentation level.
      static const long int indent_index = std::ios::xalloc();
      return o.iword(indent_index);
    }
  }

  std::ostream& incindent(std::ostream& o)
  {
    indent(o) += 2;
    return o;
  }

  std::ostream& decindent(std::ostream& o)
  {
    indent(o) -= 2;
    return o;
  }

  std::ostream& resetindent(std::ostream& o)
  {
    indent(o) = 0;
    return o;
  }

  std::ostream& iendl(std::ostream& o)
  {
    o << std::endl;
    // Be sure to be able to restore the stream flags.
    char fill = o.fill(' ');
    return o << std::setw(indent(o))
             << ""
             << std::setfill(fill);
  }

  std::ostream& incendl(std::ostream& o)
  {
    return o << incindent << iendl;
  }

  std::ostream& decendl(std::ostream& o)
  {
    return o << decindent << iendl;
  }
}
