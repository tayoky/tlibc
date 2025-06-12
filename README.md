# tlibc
tlibc is a portbale standard c library orginaly written for the [stanix operating system](https://github.com/tayoky/stanix) with the goal of being complete to compile program such as gcc binutils or git

# software
a list of some software that can be compiled using tlibc
- all stanix userspace init program
- [tutils](https://github.com/tayoky/tutils)
- [tsh](https://github.com/tayoky/tsh)
- [tcc](https://github.com/tinycc/tinycc)

# completion
list of header and estimation of their completion

- `string.h` : 95%
- `strings.h` : 60%
- `stdio.h` : 70%
- `stdlib.h` : 20% to 30%
- `stddef.h` : 100%
- `stdint.h` : 100% (but need rewrite to use compiler's one)
- `time.h` : 70%
- `ctype.h` : 100%
- `setjmp.h` : 100%
