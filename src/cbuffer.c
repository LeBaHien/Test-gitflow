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

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (cb == NULL || buf == NULL || !cb->active)
        return NOT_VALID;
    uint32_t count = 0;
    while (count < nbytes)
    {
        if (cb_data_count(cb) == NOT_VALID)
            break;
        else
        {
            ((uint8_t*)buf)[count] = cb->data[cb->reader];
            cb->reader = (cb->reader + 1) % cb->size;
        }    
        count++;
    }
    return count;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (cb == NULL || buf == NULL || !(cb->active))
        return NOT_VALID;
    uint32_t count = 0;
    while (count < nbytes)
    {
        if (cb_space_count(cb) == NOT_VALID)
        {
            cb->overflow = nbytes - count;
            break;
        }
        else
        {
            cb->data[cb->writer] = ((uint8_t*)buf)[count];
            cb->writer = (cb->writer + 1) % cb->size;
        }    
        count++;
    }
    return count;
}

uint32_t cb_data_count(cbuffer_t *cb)
{
    if (cb == NULL) 
        return NOT_VALID;
    if (cb->reader <= cb->writer)
        return cb->writer - cb->reader;
    else
        return cb->writer + cb->size - cb->reader;
}

uint32_t cb_space_count(cbuffer_t *cb);