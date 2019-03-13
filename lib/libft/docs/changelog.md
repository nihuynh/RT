# Libft
TODO : 
printf & printf_toa
fix * ft\_ft_tabdel.c
___
### Uncommit
#### added
ft\_swap
ft_dtoa.c
#### fixed
Optimise strcmp
#### removed
ft\_strnchr.c (duplicat with ft_memchr.c)
___
### [V1.0.2] 2018-04-25
#### added
* ft\_get_next_line.c >> ft_gnl.c
* ft\_get_next_line.h >> ftgnl.h
* ft\_ft_atoi_base.c
* ft\_wordcount.c
* ft\_ft_strnchr.c
* ft\_ft_tabdel.c
* ft\_ft_tablen.c
* ft\_ft_error.c
* ft\_ft_fopen_read.c
#### fixed
#### removed
___
### [V1.0.1] 2018-04-22
#### added
.gitignore
* specific folder for the sources files.
* ft\_strjoinfree.c
* ft\_strsubfree.c
* ft\_strpbrk.c
* ft\_puttab.c
* ft\_print_value.c
* ft\_lstget.

#### fixed
cont order in the functions (const char instead of char const )
#### removed

___
### [V1.0.0] 2018-04-07
#### added
* .travis.yml
* Headers 42
* categorie for the headers (IO, String, memory, math, ctype, list, convert, test)
* srcs, and includes folders
#### fixed
* categorie into the makefile
* .travis.yml
* Norme
#### removed
* License MIT
restrict keyword
___
### [V0.0.2] 2018-03-30
#### added
* License MIT
* logo on the readme.md + pdf in docs folder
* ft\_lstlen
* ft\_min
* ft\_max
* ft\_abs
* ft\_btw
* ft\_strlstsplit
* ft\_lstrev
* security in memalloc
#### fixed
* now on github
* change from define to function for math functions
__
### [V0.0.2] 2018-03-29
#### added
* readme.md
* ft_memrcpy.c
* ft_strclen.c
* struct t_byte
#### fixed
* make ft_atoi.c work in negative because of INT MIN case. 
* protect some fonctions
#### removed
* malloc call in ft_memmove.c (forward or bwd cpy)
---
### [V0.0.2] 2018-03-27
#### added
* folder for objects on compilation
* banner on compiling the lib
* include <stdlib.h> into sources files that require it
* ft_lstlast.c
* ft_lstat.c
* security on ft_lstdelone.c
#### removed
* std lib include in the header
* roadmap.txt
___
### [V0.0.1] 2018-03-26
#### added
* changelog.md
* ft_strcasestr.c
* security to strncmp.c
#### removed
* headers
* preprocessor WSTRIM(c)
* sizeof in ft_strnew.c
* write call in ft_putendl.c
#### fixed
* Makefile change (upgrade linker, add status when building the lib)
* ft_putnbr now call ft_putnbr\_fd
* ft_strcasecmp now call ft_strncasecmp
___
### [V0.0.1] 2018-03-24
#### added
* ft_strcasecmp.c
* ft_strncasecmp.c
* ft_strndup.c
* ft_strupcase.c
* roadmap.txt
#### fixed
* libft.h prototypes
___
### [V0.0.1] 2018-03-23
#### added
* Initial commit
