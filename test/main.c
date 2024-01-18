/*
 * MIT License
 *
 * Copyright (c) 2024 Andrea Michael M. Molino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/free_them_all.h"

#define TEST_CASE 6

int test_case_fta_malloc(void){
    printf("Testing FTA_malloc()");
    
    FTA_Manager malloc_manager = {0};

    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 1);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    
    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));
    
    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int test_case_fta_calloc(void){
    printf("Testing FTA_calloc()");

    FTA_Manager calloc_manager = {0};
    
    int* num_test = (int*)FTA_calloc(&calloc_manager, 10, sizeof(int), 1);
    assert(check_malloc_status(num_test) == true);
    
    for(int i = 0; i < 10; i++){
        assert(num_test[i] == 0);
    }

    free_them_all(&calloc_manager);
    assert(is_empty(&calloc_manager));
    
    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int test_case_fta_add(void){
    printf("Testing FTA_add()");
    FTA_Manager malloc_manager = {0};

    char* str_hello = (char*)malloc((13)*sizeof(char));
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    int return_value = FTA_add(&malloc_manager, str_hello, 1);
    assert(return_value == SUCCESS);

    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int test_case_fta_free(void){
    printf("Testing FTA_free()");
    FTA_Manager malloc_manager = {0};

    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 1);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    int return_value = FTA_free(&malloc_manager);
    assert(return_value == SUCCESS);

    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int test_case_fta_free_address(void){
    printf("Testing FTA_free_address");
    FTA_Manager malloc_manager = {0};
    
    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 2);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    int return_value = FTA_free_address(&malloc_manager, 2);
    assert(return_value == SUCCESS);

    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int test_case_free_them_all(void){
    printf("Testing free_them_all()");
    FTA_Manager malloc_manager = {0};
    
    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 2);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
    return 0;
}

int check_test_result(void){
    int test_success = 0;

    if(test_case_fta_malloc() == 0) test_success++;
    if(test_case_fta_calloc() == 0) test_success++;
    if(test_case_fta_add() == 0) test_success++;
    if(test_case_fta_free() == 0) test_success++;
    if(test_case_fta_free_address() == 0) test_success++;
    if(test_case_free_them_all() == 0) test_success++;
    
    return test_success;
}

int main(void){
    int test_success = 0;

    printf("\nTesting Free Them All:\n\n");
    
    test_success = check_test_result();
    
    printf("\n\nTest:[%d] Result:[%d]\n", TEST_CASE, test_success);
    printf("All Done!!!\n");

    return 0;
}