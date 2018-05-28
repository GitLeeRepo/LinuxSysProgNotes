// copysimple.c
//
// Very simple demo of copy the contents of one file to another.  This program is not
// very robust and only demonstrates the minimal code needed.  It only copies a single
// byte at a time, and relies on hardcoded demo files, rather than command line arguments.
// For a better solution refer to copybetter.c

#include <unistd.h>
#include <fcntl.h>


int main() {
	char c;
	int in, out;

	in = open("file.in", O_RDONLY);
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while (read(in, &c, 1) == 1)
		write(out, &c, 1);
}
