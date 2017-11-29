// showstats.c
// Original copied from: http://codewiki.wikidot.com/c:system-calls:stat
// Modified by TK, added the comments, refactored and added new features and output

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/*

   struct stat {
       dev_t     st_dev;         // ID of device containing file 
       ino_t     st_ino;         // Inode number 
       mode_t    st_mode;        // File type and mode 
       nlink_t   st_nlink;       // Number of hard links 
       uid_t     st_uid;         // User ID of owner 
       gid_t     st_gid;         // Group ID of owner 
       dev_t     st_rdev;        // Device ID (if special file) 
       off_t     st_size;        // Total size, in bytes
       blksize_t st_blksize;     // Block size for filesystem I/O 
       blkcnt_t  st_blocks;      // Number of 512B blocks allocated 

       struct timespec st_atim;  // Time of last access 
       struct timespec st_mtim;  // Time of last modification 
       struct timespec st_ctim;  // Time of last status change
   };

    Macros used to evealuate the st_mode flags
       S_ISREG(m)  is it a regular file?
       S_ISDIR(m)  directory?
       S_ISCHR(m)  character device?
       S_ISBLK(m)  block device?
       S_ISFIFO(m) FIFO (named pipe)?
       S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
       S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
*/


int main(int argc, char **argv){
    struct stat fileStat;
    mode_t modes; 
    char fname[255];
    int useStat = 0;  // use lstat() instead of stat() by default
    
    if(argc < 2) {    
        printf("Provide a file, directory, or device name\n");
        printf("such as /dev/sda1 or /dev/tty0\n");
        printf("add a -s after the filename if you want to use stat() instead of lstat()\n");
        return 1;
    }

    // return if null
    if (!argv[1]) 
        return 1;

    strcpy(fname, argv[1]);

    if (argc == 3) {
        if (strcmp(argv[2], "-s") == 0) 
            useStat = 1; // use the stat() function, instead of fstat()
    }
    printf("---------------------------\n");
    if (useStat) {
        stat(fname, &fileStat);
        printf("Using the stat() function, which will follow symbolic\n");
        printf("links, and thus report them as regular files (the -s option)\n");
    }
    else { // default is lstat()
        lstat(fname, &fileStat);
        printf("Using the lstat() function, which will not follow symbolic\n");
        printf("links, and will thus report them as symbolic files (default)\n");
    }
 
    modes = fileStat.st_mode;
 
    printf("---------------------------\n");
    printf("Information for %s\n",fname);
    printf("---------------------------\n");
    printf("File Size: \t\t%lu bytes\n",fileStat.st_size);
    printf("Number of Links: \t%lu\n",fileStat.st_nlink);
    printf("File inode: \t\t%lu\n",fileStat.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(modes)) ? "d" : "-");
    printf( (modes & S_IRUSR) ? "r" : "-");
    printf( (modes & S_IWUSR) ? "w" : "-");
    printf( (modes & S_IXUSR) ? "x" : "-");
    printf( (modes & S_IRGRP) ? "r" : "-");
    printf( (modes & S_IWGRP) ? "w" : "-");
    printf( (modes & S_IXGRP) ? "x" : "-");
    printf( (modes & S_IROTH) ? "r" : "-");
    printf( (modes & S_IWOTH) ? "w" : "-");
    printf( (modes & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("---------------------------\n");

    printf( (S_ISREG(modes)) ? "%s is a regular file\n" : "", fname);        
    printf( (S_ISDIR(modes)) ? "%s is directory\n" : "", fname);        
    printf( (S_ISLNK(modes)) ? "%s is a symbolic link\n" : "", fname);        
    printf( (S_ISBLK(modes)) ? "%s is a block device\n" : "", fname);        
    printf( (S_ISCHR(modes)) ? "%s is a character device\n" : "", fname);        
 
    return 0;
}
