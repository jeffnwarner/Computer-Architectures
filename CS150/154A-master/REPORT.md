# Project 4 - File System
## Phase 0
For phase 0 we started off by creating data structures for the superblock,   
root directory, and the file system.  

### File System
```c
typedef struct
{
    rootDir root[FS_FILE_MAX_COUNT];
    file fileArray[32];
    dataBlock *fat; 
    superblock *sblock;
} __attribute__((__packed__)) fileSystem;
```
Our file system structure is used to contain all the variables for the   
superblock, FAT, and the root directory. We only make one instance of   
the file system on execution of the program and it is used as a global variable.   

### Superblock
```c
typedef struct
{
    uint64_t signature;
    uint16_t totalVdBlocks;
    uint16_t rootDirBlockIndex;
    uint16_t dataBlockStartIndex;
    uint16_t numDataBlocks;
    uint8_t numFatBlocks;
    uint16_t padding[4096];
} __attribute__((__packed__)) superblock;
```
We have variables that track the total number of virtual disk blocks, the  
index of the root directory, the first index of all other data blocks, the  
number of data blocks and the number of data blocks in the FAT.  

### Root Directory
```c
typedef struct
{
    char fileName[16];  
    uint32_t fileSize;
    uint16_t indexFirstDataBlock;
    uint16_t padding[10];
}  __attribute__((__packed__)) rootDir;

```
The root directory here is treated as an array where each index contains a file.  
Each file contains the name of the file, its size, and the index of its first  
data block.   

### Data Block
```c
typedef struct
{
    uint16_t data; //16 bit blocks
} __attribute__((__packed__)) dataBlock;
```
Our FAT in the file system structure is an array of Data Blocks. Each data block     
only holds a data variable inside of them. The number inside the data variable  
will either be a 0 to signify that the data block is free, 0xFFFF to signify  
an end of chain for a file, or the number of the next data block in the file.   

## Phase 1
#### fs_mount() fs_info()
When we mount the disk in fs_mount() we decided that this would also be where we   
keep track of how many blocks are currently free. We made two global variables,   
rootBlockCount and numFreeFATBlocks, to keep track of free data blocks in the  
root directory and the FAT. These are used later in fs_info() to print out the    
ratios of free blocks to total blocks in the FAT and root directory.  

## Phase 2
#### fs_create()
In the function fs_create() we decided that we would find empty entries by   
using a for loop to look for files in the root directory that have a null   
file name. After adding the file to our root directory we use block_write()    
to write the file into the disk.  
 
#### fs_delete()
To delete files with fs_delete() we also use a for loop to search for the  
file specified in the parameter. When found, we use a second loop to set   
all data blocks in the FAT until the next EOC to 0 to indicate that those   
blocks are available for writing. Afterwards, we reset variables for the  
file in the root directory.  
 
#### fs_ls()
In fs_ls we simply print out every file name using a for loop on the  
condition that the file name is not null.  
 
## Phase 3
For this phase we added a new structure: File  

### File
```c
typedef struct 
{
    int fileDescriptor;
    int fileIndex;
    int fileOffset;
    int isOpen;
} __attribute__((__packed__)) file;
```
In file we contain a file descriptor, the index of the file in the FAT  
and the file's offest. The file system contains an array of 32 files.  
These files are the files that were opened in fs_open(). Only 32  
files can be open at a time and this is how we keep track of that.  

#### fs_open()
In fs_open, to make sure that no more than 32 files are open, we use a  
for loop that only changes a file in the file array if the file's file  
descriptor is equal to zero. Otherwise, no files are changed, or the  
function returns -1 if the file descriptor found is a negative number.  
If 32 files are opened, the function returns an error. Otherwise, we   
set the isOpen variable of our file to 1 and set the offest to 0.  
 
#### fs_close() fs_stat() and fs_lseek()
For these three functions, we use the same method of searching for the  
file in the root directory. We search through every file in the root   
directory with a for loop until we find the one with the same file   
descriptor as what was passed in. Then we conclude with the functionality   
of the respective functions: closing the file, returning the file size,  
and setting the offset.   
The only difference comes from fs_lseek which begins by calling fs_stat()   
This is to check if the file descriptor is valid. If fs_stat() returns -1,  
then fs_lseek() will also return -1.   

## Phase 4
We didn't get to finish phase 4.  

## Reflections
We probably should have started the program earlier, we started a bit late,  
so if we took more time to finish the program we probably could have had it   
done. Also, while we were implementing the functions, we erroneously believed  
that we were allowed to simply call the open() and close() system functions.  
We realized this error too late and we were unable to completely implement  
phase 4 correctly when we had to fix the code in the other functions.  
