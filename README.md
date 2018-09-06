# ft_ls
Recreation of system ls.

Uses my hand written lib C in place of standard libc, my functions are prefixed with `ft_` to
differentiate.
Implemented using a vector as the primary data structure.
I use several tricks to avoid allocating extra memory such as
using the same string for path and filename, with differance pointer offsets.
As a result it is 2x faster than the default on OSX High sierra.
