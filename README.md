# CMM HMMM What????

just a fork of c2mir from the [MIR](https://github.com/vnmakarov/mir) project that make the C11 support:

1. Type Reflection and opaque type
2. defer (yes that defer)
3. template system for templating with C
4. Simple macro update with `__fresh__` so no more macro name clash
5. Auto deref so we dont mandate `->` use `.` and it will work just fine
6. auto include guard you dont need to add `ifndef` circus on header


## Build

To build use your C compiler to build `build.cmm` (rename it to `build.c`) so the linker wont get angry...
then after that you can use the created `cmm` to run that build script for update.


## Note

to use make sure you set the env: `HMM_LIBPATH` so you can use the all new include with ":", example:

```c
#include ":yes.hmm"
```

will search at that path.
