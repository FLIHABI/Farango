/**
 ** \file misc/unique.hh
 ** \brief Definition of misc::unique.
 */

#ifndef MISC_UNIQUE_HH
# define MISC_UNIQUE_HH

# include <set>
# include <iosfwd>

namespace misc
{

  /** \brief Define \c unique class.
   **
   ** Implementation of the flyweight pattern.
   ** Map identical objects to a unique reference.
   */
  template <typename T,
            class C = std::less<T>>
  class unique
  {
  protected:
    /// The unique's object type.
    using object_set_type = std::set<T, C>;
    /// The type for the size of the unique set.
    using object_size_type = typename object_set_type::size_type;

  public:
    using value_type = unique<T, C>;
    using data_type = T;

    /** \name Ctor & Dtor.
     ** \{ */
    /** \brief Construct a \c unique.
     ** \param s referenced object */
    unique(const data_type& s);
    virtual ~unique();
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the object referenced by \c this.
    virtual const data_type& object_get() const;
    virtual operator const data_type&() const;

    /// Return the number of referenced objects.
    static object_size_type object_map_size();
    /** \} */

    /** \name Operators.
     ** \{ */
    /** \brief Assign a \c unique to this \c unique.
     ** \param rhs \c unique to copy. */
    virtual value_type& operator=(const value_type& rhs);

    /** \brief Compare two \c unique for equality.
     ** \param rhs \c unique to compare with. */
    virtual bool operator==(const value_type& rhs) const;
    /** \brief Compare two \c unique for inequality.
     ** \param rhs \c unique to compare with. */
    virtual bool operator!=(const value_type& rhs) const;
    /** \brief Compare two \c sunique for order.
     ** \param rhs \c unique to compare with. */
    virtual bool operator<(const value_type& rhs) const;
    /** \} */

  protected:
    /// Return the set of uniques.
    static object_set_type& object_set_instance();

    /// Pointer to the unique referenced object.
    const data_type* obj_;
  };

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param the a reference to the unique to redirect
   */
  template <typename T, class C>
  std::ostream& operator<<(std::ostream& ostr, const unique<T, C>& u);
}

# include "unique.hxx"

#endif // !MISC_UNIQUE_HH
