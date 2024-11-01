rm a.out
cc -Wall -Wextra -Werror main.c /usr/local/lib/libmlx_Linux.a -lXext -lX11
./a.out