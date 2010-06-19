#include "string.h"

#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <string.h>

/* A safer `strcpy()`, using `strncpy()` and `sizeof()` */
#define STRCPY(TO, FROM, BYTES) \
  strncpy(TO, FROM, BYTES); TO[BYTES - 1] = '\0'//;


/* ========================
= `infrastructure string` =
======================== */

/* ### Method Declarations ### */

string  String__allocate    (char native[]);

thing   string__thing       (string this);
char*   string__native      (string this);

                            struct String // »
                                  *String   = NULL;
void Paws__register_String(void) { String   = malloc(sizeof(struct String));
                             Paws->String   = String;
  
  struct String // »
  data = {
    .allocate   = String__allocate,
    
    .thing      = string__thing,
    .native     = string__native
  };
  
  memcpy(String, &data, sizeof(struct String));
}


/* ### Method Implementations ### */

/* This method allocates a new `infrastructure string`, and returns a C `string` (a pointer to a
 * `struct string`.)
 *--
 * TODO: Global-uniqueness. We need to cache already-created `string`s somewhere, and retreive them when
 *       necessary.
 */
string String__allocate(char native[]) {
  string this = malloc(sizeof(struct string));
  
  this->content = LL->allocate();
  
  this->bytes = strlen(native) + 1;
  if (this->bytes <= sizeof(this->native.short_array)) {
    STRCPY(this->native.short_array, native, this->bytes);
  } else {
    this->native.long_array = malloc(this->bytes);
    STRCPY(this->native.long_array, native, this->bytes);
  }
  
  return this;
}

/* This method wraps a pointer to a `struct list` into a new `thing` union, and returns that union. */
thing string__thing(string this) {
  struct thing something = {
    .isa = STRING,
    .pointer = { .string = this }
  };
  
  return something;
}

/* This method returns a pointer to a C string of UTF-8 characters for a given `list`.
 * 
 * It is important to note that strings are assumed-unmodifiable, so you shouldn’t modify the returned C string
 * in any way. */
char* string__native(string this) {
  if (this->bytes <= sizeof(this->native.short_array))
    return this->native.short_array;
  else
    return this->native.long_array;
}
