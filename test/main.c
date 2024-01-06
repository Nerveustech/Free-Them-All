/* FTA - Free Them All
 * Copyright (C) 2024  Andrea Michael Maria Molino
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/free_them_all.h"

void test_case_fta_malloc(void){
    printf("Testing FTA_malloc()");
    
    FTA_Manager malloc_manager = {0};

    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 1);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    
    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));
    
    printf(" \033[32mSuccess\033[0m\n");
}

void test_case_fta_add(void){
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
}

void test_case_fta_free(void){
    printf("Testing FTA_free()");
    FTA_Manager malloc_manager = {0};

    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 1);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    int return_value = FTA_free(&malloc_manager);
    assert(return_value == SUCCESS);

    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
}

void test_case_fta_free_address(void){
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
}

void test_case_free_them_all(void){
    printf("Testing free_them_all()");
    FTA_Manager malloc_manager = {0};
    
    char* str_hello = (char*)FTA_malloc(&malloc_manager, ((13)*sizeof(char)), 2);
    assert(check_malloc_status(str_hello) == true);
    strcpy(str_hello, "Hello World");

    free_them_all(&malloc_manager);
    assert(is_empty(&malloc_manager));

    printf(" \033[32mSuccess\033[0m\n");
}

int main(void){
    printf("\nTesting Free Them All:\n\n");
    
    test_case_fta_malloc();
    test_case_fta_add();
    test_case_fta_free();
    test_case_fta_free_address();
    test_case_free_them_all();
    
    printf("\n All Done!!!\n");

    return 0;
}