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

#include "free_them_all.h"


void FTA_init(FTA_Manager* queue){
    queue->head = NULL;
    queue->tail = NULL;
}

void* FTA_malloc(FTA_Manager* queue, size_t size, int identifier){
    void* internal_malloc_address = malloc(size);
    if(!check_malloc_status(internal_malloc_address)) return NULL;

    FTA_add(queue, internal_malloc_address, identifier);

    return internal_malloc_address;
}

void* FTA_calloc(FTA_Manager* queue, size_t nmemb, size_t size, int identifier){
    void* internal_calloc_address = calloc(nmemb, size);
    if(!check_malloc_status(internal_calloc_address)) return NULL;

    FTA_add(queue, internal_calloc_address, identifier);
    
    return internal_calloc_address;
}

ErrorOr FTA_add(FTA_Manager* queue, void* malloc_address, int identifier){
    if(!check_malloc_status(malloc_address)) return ENOMEM;

    fta_data* new_data = (fta_data*)malloc(sizeof(fta_data));
    if(!check_malloc_status(new_data)) return ENOMEM;

    new_data->malloc_address = malloc_address;
    new_data->identifier = identifier;
    new_data->next = NULL;
    
    if(is_empty(queue))
        queue->head = new_data;
    else
        queue->tail->next = new_data;
    
    queue->tail = new_data;
    return SUCCESS;
}

ErrorOr FTA_free(FTA_Manager* queue){
    if(is_empty(queue)) return EFTAQE;

    if(check_malloc_status(queue->head->malloc_address))
        free(queue->head->malloc_address);
    
    fta_data* temp_index = queue->head;
    
    if(queue->head->next == NULL)
        queue->tail = NULL;
    queue->head = queue->head->next;
    
    free(temp_index);
    
    return SUCCESS;
}

ErrorOr FTA_free_address(FTA_Manager* queue, int identifier){
    if(is_empty(queue)) return EFTAQE;

    void* malloc_address = find_address_from_identifier(queue, identifier);
    
    if(check_malloc_status(malloc_address))
        free(malloc_address);
    
    fta_data* temp_index = queue->head;
    
    if(queue->head->next == NULL)
        queue->tail = NULL;
    queue->head = queue->head->next;

    free(temp_index);

    return SUCCESS;
}

void* find_address_from_identifier(FTA_Manager* queue, int identifier){
    if(is_empty(queue)) return NULL;

    fta_data* cursor = queue->head;

    while(cursor != NULL){
        if(cursor->identifier == identifier)
            return cursor->malloc_address;
        cursor = cursor->next;
    }
    return NULL;
}

#ifdef FTA_PRINT_STATUS
bool FTA_status(FTA_Manager* queue){
    if(is_empty(queue)) return false;

    fta_data* cursor = queue->head;

    while (cursor != NULL){
        printf("[INFO - FTA] Address of malloc: %p\n", cursor->malloc_address);
        printf("[INFO - FTA] Identifier: %d\n", cursor->identifier);
        cursor = cursor->next;
    }
    return true;
    
}
#endif

void free_them_all(FTA_Manager* queue){
    while (!is_empty(queue)){
        FTA_free(queue);
    }

    return;
}


bool is_empty(FTA_Manager* queue){
    if(queue->head == NULL)
        return true;
    return false;
}


bool check_malloc_status(void* malloc_address){
    if(malloc_address == NULL)
        return false;
    return true;
}