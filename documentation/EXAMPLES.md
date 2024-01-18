# Examples

```c
#include "free_them_all.h"
#include <stdio.h>

int main(int argc, char** argv){
    FTA_Manager malloc_manager = {0};

    char* string_ex = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 1);
    strcpy(string_ex, "Hello World");

    
    free_them_all(&malloc_manager);
    
    printf("%s \n", string_ex);
    
    return 0;
}
```