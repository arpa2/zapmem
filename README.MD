# Zapping Memory Securely

> *Clearing memory is difficult.  This is a solution.*

Reference:

  * [KIP issue #32](https://gitlab.com/arpa2/kip/issues/32)
  * [CCC presentation "Memsad"](https://media.ccc.de/v/35c3-9788-memsad)

The solution presented here intends to not only work under present
compilers, but to avoid problems in the future.  This can be assured
by presenting compiler optimisation routines with an abstraction
boundary.


## Problem Explanation

The C specifications introduced `memset_s()` as a variant of `memset()`
that cannot be removed by optimisers.  This can be used to construct
something to replace the pattern

```
memset (mem, 0, memsize);
free (mem);
```

which compiles as intended, clearing memory whose contents may be
sensitive before returning it to the memory pool from which programs
could see it after `malloc()` which does not clear the new memory.

The problem with the literal pattern above is that the `memset()` may
be optimised out by the compiler, who sees no use in it.  The same
may happen across modules when link-time optimisation is enabled.


## Optional Solution in C11

The `memset_s()` operation is an optional extension to the C11
standard.  The symbol `__STDC_LIB_EXT1__` is defined if `memset_s()`
is available.  (TODO: Formal Reference Needed)

If the flag is not defined, what to do?

Some platforms have a special function for being sure to clear
memory, such as Windows, and such platforms tend to define it as
their `memset_s()` so solutions that explicitly call this function
may not add much.  We therefore focussed on creating `memset_s()` on
the remaining platforms, but not through these existing functions.

As it turns out however, there is a lot more to do when this is
to be done faithfully.  The `memset_s()` function adds constraint
checks and may invoke a separately set constraint handler function,
and it requires even more paramaters.

You knew about the error that could be returned, right?  And, you
had a plan of handling it, either by reporting it explicitly or
crashing your program while being mindful of the possibility that
other secure memory did not get wiped?  All this gets in the way of
the simple functionality that we need.


## Simpler Fun

Our ARPA2 remake of this intended function handles any problems in a
graceful manner.  It does not crash.  When faced with a NULL pointer
it simply does nothing, and otherwise it relies on the memory size to
be set properly.

```
#include <stddef.h>
void arpa2_zapmem (void *mem, size_t memsz);
```

Also, the ARPA2 version can be called with a pointed-at variable
to be wiped based on its size.

```
#define arpa2_zapvar(v) arpa2_zapmem ((v), sizeof (v))
```

Finally, a variant that works on arrays of a given size.

```
#define arpa2_zaparray(a,n) arpa2_zapmem ((a), sizeof ((a)) * (n))
```

## Sigh

This is a separate library so compilers can perform link-time optimisation,
which is not the default.  One might argue that such optimisation is not a
good idea for security software anyway.

To still enable it in software using these functions, the output made here
is a shared library, also known as a dynamic object.  Since it is designed
to be pluggable code, it is not to be expected that a compiler would ever
silently introduce optimisations for this kind of library linking.
