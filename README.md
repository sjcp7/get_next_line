*This project has been created as part of the 42 curriculum by samupedr*.

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor one line at a time:

```c
char	*get_next_line(int fd);
```

Each call returns the next line from `fd` (including the terminating `\n`, if
there is one), or `NULL` once there is nothing left to read or an error occurs.
The caller owns the returned string and must `free()` it.

The goal of the project is to learn how to keep state between function calls
with static variables, how to work with file descriptors and `read(2)`
when the size of each read is fixed at compile time (`BUFFER_SIZE`), and how to
manage heap memory without leaks.

The repository contains two versions:

| Part      | Files                                                                          | Behaviour                                                         |
|-----------|--------------------------------------------------------------------------------|-------------------------------------------------------------------|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`                  | Reads one file descriptor at a time.                              |
| Bonus     | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` | Keeps separate state for each fd, so several can be read in turn. |

## Instructions

### Compilation

Compile the files together with a `main` of your own, and use
`-D BUFFER_SIZE=n` to choose how many bytes each `read()` call asks for (the
default is 4096, which is the default page size on most x86\_64 systems; run
`getconf PAGESIZE` to check it out):

```sh
# mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

To read standard input, pass `0` as the fd. With the bonus version you can call
`get_next_line(fd_a)` and `get_next_line(fd_b)` in turn, and each fd continues
from where it stopped.

## Algorithm

### Data structures

Two small structures (declared in the headers) hold all the state:

```c
typedef struct s_buffer
{
	char	*buf;      // read() data
	size_t	len;       // bytes in buf
	size_t	i;         // next unread
}	t_buffer;

typedef struct s_string
{
	char	*s;        // the line being built
	size_t	capacity;  // usable bytes in s
	size_t	len;       // bytes used in s
}	t_string;
```

- `t_buffer` is the only thing kept between calls. It holds the last chunk
  returned by `read()` and a cursor `i` that points to the first byte not yet
  given to the caller. The mandatory version keeps one `static t_buffer`. The
  bonus version keeps `static t_buffer buf[MAX_NUM_FD]` and uses the fd as the
  index, so each fd has its own buffer and cursor.
- `t_string` is a dynamic string that exists only during one call. It
  collects the bytes of the line being returned.

### Steps of one call

1. **Validation.** Return `NULL` if `fd < 0`, if `BUFFER_SIZE <= 0`, or (bonus)
   if `fd >= MAX_NUM_FD`.
2. **First use.** If this fd has no buffer yet (`buf == NULL`), allocate
   `BUFFER_SIZE` bytes and set `len = i = 0`. Allocating only on first use
   means an fd that is never read costs no heap memory.
3. **Main loop.**
   - If every byte in the buffer has been used (`i >= len`), call
     `read(fd, buf, BUFFER_SIZE)`:
     - `> 0`: store the number of bytes in `len` and set `i = 0`.
     - `== 0` (end of file): free the buffer, set the pointer to `NULL`, and
       return what has been collected so far: the last line, or `NULL` if
       nothing was collected.
     - `< 0` (error): free the buffer and the partial line, and return `NULL`.
   - Otherwise, append `buf[i]` to the line and advance `i`. If that byte was
     `\n`, return the line. The bytes after it stay in the buffer, and `i`
     already points to them for the next call.
4. **Appending.** The first append allocates 64 bytes (`INIT_STRING_SIZE`).
   When the line is full, the capacity doubles: `gnl_string_resize` allocates
   the new block, copies the old contents and frees the old block. After each
   append a `\0` is written, so the line is always a valid C string. If a
   `malloc` fails, the error is passed back up, the line and the buffer are
   freed, and `NULL` is returned.

## Resources

### References

- [`read(2)`](https://man7.org/linux/man-pages/man2/read.2.html): return
  values, end of file and errors.
- [`malloc(3)` / `free(3)`](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [`open(2)`](https://man7.org/linux/man-pages/man2/open.2.html): file
  descriptors.
- [Storage duration (cppreference)](https://en.cppreference.com/w/c/language/storage_duration):
  how `static` local variables keep their value between calls.
- [Dynamic array (Wikipedia)](https://en.wikipedia.org/wiki/Dynamic_array):
  growing by doubling and why it costs amortised O(1) per append.
- [Valgrind Memcheck manual](https://valgrind.org/docs/manual/mc-manual.html):
  what "definitely lost", "still reachable", "invalid read" and
  "conditional jump depends on uninitialised value" mean.
- [gnlTester](https://github.com/Tripouille/gnlTester): the tester used for
  this project.

### Use of AI

Claude was used as a reviewer and testing assistant. Claude was used to:

- Audit for memory problems. 
- Find performance issues. 
- Draft this README, which I then reviewed and tweaked.
