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