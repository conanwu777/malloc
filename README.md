# malloc
My implementation of the libc malloc, realloc and free functions using system mmap

##Features

  * Size segmentation: divides requests into SMALL, MEDIUM and LARGE, use pre-allocated zones for SMALL and MEDIUM requests
  
  * De-fragment freed spaces to optimize re-usage
  
  * Hexdump allocated memory functionality
  
## Demo of malloced random bytes
![alt text](/1.png)
- Dark green: headers of freed blocks
- Dark red: headers of malloced blocks
- Light green: unused blocks
- Orange: malloced blocks

## Functions implemented:
  
  * malloc -  allocates “size” bytes of memory and returns a pointer to the allocated memory
  
  * realloc - tries to change the size of the allocation pointed to by “ptr” to “size”, and returns “ptr”. If there is not enough room to enlarge the memory allocation pointed to by ptr, realloc() creates a new allocation, copies as much of the old data pointed to by “ptr” as will fit to the new allocation, frees the old allocation, and returns a pointer to the allocated memory.
  
  * free - deallocates the memory allocation pointed to by “ptr”. If “ptr”is a NULL pointer, no operation is performed
  
  * show_alloc_mem (see image)
  
![alt text](/2.png)
