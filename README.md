# tlibc
tlibc is a portbale standard c library orginaly written for the [stanix operating system](https://github.com/tayoky/stanix) with the goal of being complete to compile program such as gcc binutils or git

# software
with more than 200 functions tlibc can be used with program such as 
- all stanix userspace program
- [tutils](https://github.com/tayoky/tutils)
- [tsh](https://github.com/tayoky/tsh)
- [tcc](https://github.com/tinycc/tinycc) (but segfault see [issue #4](https://github.com/tayoky/tlibc/issues/4))
- binutils (but segfault with a NULL pointer)

# completion
list of header and estimation of their completion

- `string.h` : 95%
- `strings.h` : 60%
- `stdio.h` : 70%
- `stdlib.h` : 20% to 30%
- `stddef.h` : 100%
- `stdint.h` : 100% (but need rewrite to use compiler's one)
- `time.h` : 70%
- `ctype.h` : 100% (but need rewrite to use locale)
- `setjmp.h` : 100%
