#define INTERNALIZE
# include "Paws.h"
#undef INTERNALIZE

#include <stdlib.h>


thing   Paws__nothing   (void);

struct Paws Paws = {
  .Threading    = NULL,
  
  .List         = NULL,
  .Routine      = NULL,
  .Numeric      = NULL,
  .String       = NULL,
  
  .nothing    = Paws__nothing
};

thing Paws__nothing(void) {
  struct thing nothing = {
    .isa = NOTHING,
    .pointer = { .nothing = NULL }
  };
  
  return nothing;
}
