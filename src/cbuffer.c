/**
 * @file       cbuffer.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Group 5
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       None
 */
/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"

/* Public macros ------------------------------------------------------ */
#define NOT_VALID                   0

/* Public function ---------------------------------------------------- */
void cb_init(cbuffer_t *cb, void *buf, uint32_t size){
    if (cb == NULL || buf == NULL)
        return;
    cb->data = (uint8_t*)buf;
    cb->size = size;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    cb->active = true;
    return;
}

void cb_clear(cbuffer_t *cb)
{
    if (cb == NULL)
        return;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    return;
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes);

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes);

uint32_t cb_data_count(cbuffer_t *cb);

uint32_t cb_space_count(cbuffer_t *cb);