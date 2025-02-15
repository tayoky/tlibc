# build
## required sofware
you need all of this software to be installed:
- git
- make
- gcc
- ld
- nasm
- coreutil(for cp and find)
## header install
you can install the headers to the sysroot by using
```sh
make header SYSROOT=/path/to/sysroot TARGET=stanix
```
if you want to install the header to the current running system do 
```sh
make header SYSROOT= TARGET=stanix
```
## build the tlibc
to build the tlibc just do
```sh
make TARGET=stanix
```
## install
you can install the tlibc to your sysroot same as headers
```sh
make TARGET=stanix SYSROOT=path/to/your/sysroot
```
or to install to the current running system
```sh
make TARGET=stanix SYSROOT=
```
NOTE : that might required super user permison

