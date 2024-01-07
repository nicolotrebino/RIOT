/*
 * Copyright (C) 2023 AFN_Security
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 * @file
 * @brief       Test sys/sched_feedback
 * @author      Nicolò Trebino <nicolo.trebino@gmail.com> @nicolotrebino
 * @author      Federico Garau <fedegarau02@gmail.com> @fedeg202
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "thread.h"
#include "ztimer.h"
#include "timex.h"

#define ENABLE_DEBUG 1
#include "debug.h"

static kernel_pid_t main_pid;

// Each thread gets a stack
static char stack[5][THREAD_STACKSIZE_DEFAULT];

#define QUANTUM 100

uint8_t counter = 0;

// Threads' service time definition
uint32_t A_s_time = 3000;
uint32_t B_s_time = 6000;
uint32_t C_s_time = 4000;
uint32_t D_s_time = 5000;
uint32_t E_s_time = 2000;

void print_thread(char name, uint32_t s_time){
    // Execution time
    uint32_t ex_time = 0;
    // Remaining seconds
    uint32_t r_sec = 0;
    // Remaining tenths of a second
    uint32_t r_tenths = 0;
    counter++;
    while (ex_time < s_time-QUANTUM){
        ztimer_spin(ZTIMER_MSEC, QUANTUM);
        ex_time += QUANTUM;
        r_sec = (s_time - ex_time)/1000;
        r_tenths = ((s_time - ex_time) % 1000) / 100;
        printf("%c - REMAINING TIME: %u.%us\n", name, r_sec, r_tenths);
        counter++;
    }
    ex_time += QUANTUM;
    r_sec = (s_time - ex_time)/1000;
    r_tenths = ((s_time - ex_time) % 1000) / 100;
    printf("%c - REMAINING TIME: %u.%us\n", name, r_sec, r_tenths);
}

void *thread_A(void *d)
{
    (void) d;
    print_thread('A', A_s_time);
    DEBUG("Thread A finished after %u quantums\n", counter);
    return NULL;
}

void *thread_B(void *d)
{
    (void) d;
    print_thread('B', B_s_time);
    DEBUG("Thread B finished after %u quantums\n", counter);
    return NULL;
}

void *thread_C(void *d)
{
    (void) d;
    print_thread('C', C_s_time);
    DEBUG("Thread C finished after %u quantums\n", counter);
    return NULL;
}

void *thread_D(void *d)
{
    (void) d;
    print_thread('D', D_s_time);
    DEBUG("Thread D finished after %u quantums\n", counter);
    return NULL;
}

void *thread_E(void *d)
{
    (void) d;
    print_thread('E', E_s_time);
    DEBUG("Thread E finished after %u quantums\n", counter);
    return NULL;
}

int main(void)
{
    DEBUG_PUTS("Starting Threads");
    main_pid = thread_getpid();

    thread_create(stack[0], sizeof(stack[0]), THREAD_PRIORITY_MAIN+1, THREAD_CREATE_STACKTEST, thread_A, NULL, "A");
    thread_create(stack[1], sizeof(stack[1]), THREAD_PRIORITY_MAIN+2, THREAD_CREATE_STACKTEST, thread_B, NULL, "B");
    thread_create(stack[2], sizeof(stack[2]), THREAD_PRIORITY_MAIN+3, THREAD_CREATE_STACKTEST, thread_C, NULL, "C");
    thread_create(stack[3], sizeof(stack[3]), THREAD_PRIORITY_MAIN+4, THREAD_CREATE_STACKTEST, thread_D, NULL, "D");
    thread_create(stack[4], sizeof(stack[4]), THREAD_PRIORITY_MAIN+5, THREAD_CREATE_STACKTEST, thread_E, NULL, "E");

    DEBUG_PUTS("Thread Main is finished!");
}
