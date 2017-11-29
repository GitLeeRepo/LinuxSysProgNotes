#!/bin/bash
#
# Examples of various file checks

# Provide help if no arguement provided
if [ -z $1 ] || [ $1 = "-h" ] || [ $1 = "-help" ]
then
    echo "Provide a single: file, directory, symobolic, or device name"
    echo "such as /dev/sda1 or /dev/tty0"
    exit
fi

if [ ! -e $1 ]
then
    echo "<$1 does not exist>"
    echo "Provide a single: file, directory, symobolic, or device name"
    echo "such as /dev/sda1 or /dev/tty0"
    exit
fi

# Regular files and directories
if [ -e $1 ]
then
    echo "$1 exists"
fi
if [ -f $1 ] 
then
    echo "$1 is a normal file"
fi
if [ -x $1 ]
then
    echo "$1 is executable by user"
fi
if [ -d $1 ]
then
    echo "$1 is a directory"
fi

# symbolic links
if [ -h $1 ]
then
    echo "$1 is a symbolic link (with -h)"
fi
if [ -L $1 ]
then
    echo "$1 is a symbolic link (with -L)"
fi


# Devices
if [ -b $1 ] 
then 
    echo "$1 is a block device"
fi
if [ -c $1 ] 
then 
    echo "$1 is a character device"
fi

