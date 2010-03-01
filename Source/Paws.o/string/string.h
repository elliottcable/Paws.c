#define STRING_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/Core/ll.h"
#endif


/* ========================
= `infrastructure string` =
======================== */

/* ### Data Types & Structures ### */

typedef  unsigned long long int  E(string_size);

/* `infrastructure string`, the immutable character-string data structure of
 * Paws, is herein implemented natively with UTF-8 byte strings.
 */
struct E(string) {
  E(ll)           content; /* The `ll` behind this `string`’s `list` interface */
  
  /* This complex nested structure provides a very efficient storage for very
   * short byte strings (anything less than (usually) sixteen bytes, including
   * the `NULL` terminator). This is because those short-strings are stored
   * inline in the struct, instead of in another memory location; this also
   * allows for a single cache entry. If the string is *longer* than that, it
   * is stored in another memory location, and a pointer is stored in the
   * equivalent space instead. */
  union {
    struct packed {
      char*           long_array;
      E(string_size)  available;
    }     otherwise;
    char  short_array[sizeof(char*) + sizeof(E(string_size))];
  }               native;
  E(string_size)  bytes;
};


/* ### Method Declarations ### */

struct E(String) {
  /* `String` functions */
  E(string) (*create)   ( char native[], E(string_size) bytes );
  
  /* `struct numeric` methods */
  E(thing)  (*to_thing) ( E(string) this );
  char*     (*native)   ( E(string) this );
};
#if !defined(EXTERNALIZE)
  struct E(String) extern const String;
#endif