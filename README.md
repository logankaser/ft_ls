# ft_ls
Recreation of system `ls`.

Uses my hand written libc in place of standard libc.  
Implemented using a vector as the primary data structure.  
I use several tricks to avoid allocating extra memory such as
using the same string for path and filename, with differance pointer offsets.
As a result it is 2-3x faster than default `ls` on MacOS High sierra.  
It can't hold a candle to linux `ls` though.
