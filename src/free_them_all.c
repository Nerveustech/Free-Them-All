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
    
    if(check_malloc_status(temp_index))
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