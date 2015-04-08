/**
 ** \file misc/indent.hh
 ** \brief Indentation relative functions.
 **/

#ifndef MISC_INDENT_HH
# define MISC_INDENT_HH

# include <iosfwd>

namespace misc
{
  /// Increment the indentation.
  std::ostream& incindent(std::ostream& o);

  /// Decrement the indentation.
  std::ostream& decindent(std::ostream& o);

  /// Reset the indentation.
  std::ostream& resetindent(std::ostream& o);

  /// Print an end of line, then set the indentation.
  std::ostream& iendl(std::ostream& o);

  /// Increment the indentation, print an end of line, and set the indentation.
  std::ostream& incendl(std::ostream& o);

  /// Decrement the indentation, print an end of line, and set the indentation.
  std::ostream& decendl(std::ostream& o);
}

#endif // !MISC_INDENT_HH
