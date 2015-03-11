/**
 ** \file misc/symbol.hh
 ** \brief Definition of misc::symbol.
 */

#ifndef MISC_SYMBOL_HH
# define MISC_SYMBOL_HH

# include <set>
# include <string>
# include <iosfwd>
# include "unique.hh"

namespace misc
{

  /** \brief Define symbol class.
   **
   ** Map any string to a unique reference.
   ** This allows to avoid an "strcmp()" style comparison of strings:
   ** reference comparison is much faster.
   */
  class symbol : public unique<std::string>
  {
    using super_type = unique<std::string>;
    /// The type "set of strings".
    using string_set_type = super_type::object_set_type;
    /// The type for the size of string map.
    using string_size_type = string_set_type::size_type;

    /** \name Ctor & Dtor.
     ** \{ */
  public:
    /** \brief Construct a symbol.
     ** \param s referenced string */
    symbol(const std::string& s);
    /** \brief Construct a symbol.
     ** \param s referenced string */
    symbol(const char* s = "");
    /** \brief Destroy a symbol.  */
    virtual ~symbol();
    /** \} */

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the string referenced by this.
    const std::string& name_get() const;

    /// Return the number of referenced strings.
    static string_size_type string_map_size();
    /** \} */

    /** \name Operators.
     ** \{ */
  public:
    /** \brief Assign a symbol to this symbol.
     ** \param rhs symbol to copy. */
    symbol& operator=(const symbol& rhs);

    /** \brief Compare two symbol for equality.
     ** \param rhs string to compare with. */
    bool operator==(const symbol& rhs) const;
    /** \brief Compare two symbol for inequality.
     ** \param rhs string to compare with. */
    bool operator!=(const symbol& rhs) const;
    /** \} */

  public:
    /** \name Factory methods.
     ** \{ */
    /** \brief Create a new unique symbol. */
    static symbol fresh();
    /** \brief Create a new unique symbol, forged from \a s. */
    static symbol fresh(const symbol& s);
    /** \} */
  };

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param the a reference to the symbol to redirect
   */
  std::ostream& operator<<(std::ostream& ostr, const symbol& the);
}

# include "symbol.hxx"

#endif // !MISC_SYMBOL_HH
