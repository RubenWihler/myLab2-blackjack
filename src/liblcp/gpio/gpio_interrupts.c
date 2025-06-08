#include "gpio_interrupts.h"
#include "../config_LPC1769.h"
#include "../log/log.h"

#include <stdlib.h>
#include <string.h>

typedef enum {
    INT_REG_TYPE_ENABLE,
    INT_REG_TYPE_STATUS,
    INT_REG_TYPE_CLEAR,
} int_reg_type_e;

typedef struct {
    uint8_t port, pin;
    volatile uint32_t *reg_enable, *reg_status, *reg_clear;
    int_fn_t fn;
} gpio_int_t;

typedef struct {
    dyn_array_t *interrupts;
    uint32_t status[3];
} gpio_int_manager_t;

static volatile uint32_t* get_int_reg(const unsigned char port, const unsigned char mode, const int_reg_type_e reg_type);

static gpio_int_manager_t *singleton = NULL;
static gpio_int_manager_t* get_inst()
{
    if (!singleton)
    {
        LOG_ERROR("GPIO interrupts manager not initilized !", false);
        return NULL;
    }

    return singleton;
}

bool gpio_int_init()
{
    if (singleton != NULL)
    {
        LOG_ERROR("GPIO interrupts manager already initilized !", false);
        return false;
    }

    singleton = malloc(sizeof(*singleton));
    if (!singleton) return false;

    memset(singleton, 0, sizeof(*singleton));

    singleton->interrupts = dyn_array_create(2, sizeof(gpio_int_t), NULL);
    if (!singleton->interrupts) return (free(singleton), false);

    return true;
}

void gpio_int_free()
{
    if (!singleton) return;

    dyn_array_destroy(singleton->interrupts);
    free(singleton);
    singleton = NULL;
}

void gpio_int_enable()
{
    ISER0 |= (1 << 21);
}

void gpio_int_set_fn(const uint8_t port, const uint8_t pin, const unsigned char mode, int_fn_t fn)
{
    const bool valid_param = (port == 0 || port == 2) //le port 1 n'est pas utilise
        && pin < 32 
        && fn != NULL
        && (mode == 'R' || mode == 'F');

    if (!valid_param)
    {
        LOG_ERROR("Failed setting interrupts function : parameter invalid !", false);
        return;
    }

    const gpio_int_t interrupt = {
        .port = port,
        .pin = pin,
        .reg_status = get_int_reg(port, mode, INT_REG_TYPE_STATUS),
        .reg_enable = get_int_reg(port, mode, INT_REG_TYPE_ENABLE),
        .reg_clear = get_int_reg(port, mode, INT_REG_TYPE_CLEAR),
        .fn = fn
    };

    gpio_int_manager_t *manager = get_inst();
    dyn_array_push_back(manager->interrupts, &interrupt);

    *interrupt.reg_enable |= (1 << interrupt.pin);
}

void gpio_int_handle()
{
    gpio_int_manager_t *manager = get_inst();

    if (manager->status[0] == 0 && manager->status[2] == 0) return;

    const int count = dyn_array_count(manager->interrupts);

    for (int i = 0; i < count; i++)
    {
        gpio_int_t *interrupt = dyn_array_get(manager->interrupts, i);

        //on regarde si le statut est a 1 : si oui on appele le callback 
        if ((manager->status[interrupt->port] >> interrupt->pin) & 1)
        {
            interrupt->fn();
        }
    }

    //met toutes les interuptions a 0
    memset(manager->status, 0, sizeof(manager->status));
}


void GPIO_IRQHandler(void)
{
    gpio_int_manager_t *manager = get_inst();
    int count = dyn_array_count(manager->interrupts);

    for (int i = 0; i < count; i++)
    {
        gpio_int_t *interrupt = dyn_array_get(manager->interrupts, i);

        if ((*interrupt->reg_status >> interrupt->pin) & 1)
        {
            *interrupt->reg_clear = (1 << interrupt->pin);
            manager->status[interrupt->port] |= (1 << interrupt->pin);
        }
    }
}

static volatile uint32_t* get_int_reg(const unsigned char port, const unsigned char mode, const int_reg_type_e reg_type)
{
    if (reg_type == INT_REG_TYPE_ENABLE)
    {
        switch (port)
        {
            case 0:  return (mode == 'R') ? &IO0IntEnR : &IO0IntEnF;
            case 2:  return (mode == 'R') ? &IO2IntEnR : &IO2IntEnF;
            default: return NULL;
        }
    }
    else if (reg_type == INT_REG_TYPE_STATUS)
    {
        switch (port)
        {
            case 0:  return (mode == 'R') ? &IO0IntStatR : &IO0IntStatF;
            case 2:  return (mode == 'R') ? &IO2IntStatR : &IO2IntStatF;
            default: return NULL;
        }
    }
    else if (reg_type == INT_REG_TYPE_CLEAR)
    {
        switch (port)
        {
            case 0:  return &IO0IntClr;
            case 2:  return &IO2IntClr;
            default: return NULL;
        }
    }

    return NULL;
}

