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

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum ErrorOr {
    SUCCESS = 0,
    EFTAQE = 1,         //Free Them All Queue Empty
    ENOMEM = 5,         //Malloc Out of Memory

} ErrorOr;

typedef struct fta_data{
    void* malloc_address;
    int   identifier;

    struct fta_data* next;
}fta_data;

typedef struct{
    fta_data* head;
    fta_data* tail;
}FTA_Manager;

void FTA_init(FTA_Manager* queue);

void* FTA_malloc(FTA_Manager* queue, size_t size, int identifier);
void* FTA_calloc(FTA_Manager* queue, size_t nmemb, size_t size, int identifier);
ErrorOr FTA_add(FTA_Manager* queue, void* malloc_address, int identifier);
ErrorOr FTA_free(FTA_Manager* queue);
ErrorOr FTA_free_address(FTA_Manager* queue, int identifier);

void* find_address_from_identifier(FTA_Manager* queue, int identifier);

bool FTA_status(FTA_Manager* queue);
void free_them_all(FTA_Manager* queue);
bool is_empty(FTA_Manager* queue);


bool check_malloc_status(void* malloc_address);