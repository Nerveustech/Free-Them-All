: '
 FTA - Free Them All
 Copyright (C) 2024  Andrea Michael Maria Molino

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
'

#!/bin/bash

set -xe

COMPILE_FLAGS="-c -g -Wall -Wextra -D FTA_PRINT_STATUS" 

compile(){
    gcc $COMPILE_FLAGS src/free_them_all.c test/main.c
    gcc -o main main.o free_them_all.o
}

run_test(){
    ./main
}

cleanup(){
    rm -rf main.o free_them_all.o main
}

compile
run_test
cleanup