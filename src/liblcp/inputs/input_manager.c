#include "input_manager.h"
#include "../log/log.h"
#include "../gpio/gpio.h"
#include "../gpio/gpio_interrupts.h"
#include "touch_screen/touch_screen.h"

#include <stdlib.h>

const uint16_t INPUT_TYPE_COUNT = 4;

static input_manager_t *input_manager_singleton = NULL;

static void enable_handling(const input_type_e type);
static void handle_button_a(void);
static void handle_button_b(void);
static void handle_joystick(void);
static void handle_touch_screen(void);

input_manager_t *input_manager_get_instance()
{
    if (input_manager_singleton == NULL)
    {
        LOG_ERROR("input manager instance does not exist ! You may need to initialize it !", false);
        return NULL;
    }

    return input_manager_singleton;
}

input_manager_t *input_manager_init()
{
    if (input_manager_singleton != NULL)
    {
        LOG_ERROR("input manager instance already exists !", false);
        return NULL;
    }

    input_manager_singleton = malloc(sizeof(input_manager_t));
    if (!input_manager_singleton)
    {
        LOG_ERROR("Failed to allocate memory for input manager instance", false);
        return NULL;
    }

    input_manager_singleton->input_handlers = malloc(INPUT_TYPE_COUNT * sizeof(dyn_array_t*));
    if (!input_manager_singleton->input_handlers)
    {
        LOG_ERROR("Failed to allocate memory for input manager instance", false);
        free(input_manager_singleton);
        return NULL;
    }

    for (int i = 0; i < INPUT_TYPE_COUNT; i++)
    {
        input_manager_singleton->input_handlers[i] = dyn_array_create(2, sizeof(void*), NULL);
        if (!input_manager_singleton->input_handlers[i])
        {
            LOG_ERROR("Failed to create input handler array", false);
            return NULL;
        }
    }

    touch_screen_init();
    gpio_int_init();
    gpio_int_enable();

    return input_manager_singleton;
}

void input_manager_destroy()
{
    input_manager_t *manager = input_manager_get_instance();

    gpio_int_free();

    for (int i = 0; i < INPUT_TYPE_COUNT; i++)
    {
        dyn_array_destroy(manager->input_handlers[i]);
    }

    free(manager->input_handlers);
    free(manager);
    input_manager_singleton = NULL;
}

void input_manager_add_listener(const input_type_e type, void* fn_listener)
{
    input_manager_t *manager = input_manager_get_instance();
    dyn_array_push_back(manager->input_handlers[type], &fn_listener);

    if (dyn_array_count(manager->input_handlers[type]) == 1)
    {
        enable_handling(type);
    }
}

static void enable_handling(const input_type_e type)
{
    switch (type) 
    {
    case BUTTON_A: 
        gpio_int_set_fn(2, 10, 'F', handle_button_a);
        break;

    case BUTTON_B: 
        gpio_int_set_fn(0, 19, 'F', handle_button_b);
        break;

    case JOYSTICK:
        LOG_ERROR("JOYSTICK input type is not supported !", false);
        break;

    case TOUCH_SCREEN:
        gpio_int_set_fn(2, 11, 'F', handle_touch_screen);
        break;

    default: 
        LOG_ERROR("Unknown input type", false);
        break;
    }
}

static void handle_button_a(void)
{
    int count = dyn_array_count(INPUT_MANAGER->input_handlers[BUTTON_A]);
    for (int i = 0; i < count; i++)
    {
        void** fn = dyn_array_get(INPUT_MANAGER->input_handlers[BUTTON_A], i);
        ((void(*)())*fn)();
    }
}

static void handle_button_b(void)
{
    int count = dyn_array_count(INPUT_MANAGER->input_handlers[BUTTON_B]);
    for (int i = 0; i < count; i++)
    {
        void** fn = dyn_array_get(INPUT_MANAGER->input_handlers[BUTTON_B], i);
        ((void(*)())*fn)();
    }
}

static void handle_joystick(void)
{
    joystick_state_e state = gpio_joystick_get_state();
    if (state > JOYSTICK_NONE)
    {
        int count = dyn_array_count(INPUT_MANAGER->input_handlers[JOYSTICK]);
        for (int i = 0; i < count; i++)
        {
            void** fn = dyn_array_get(INPUT_MANAGER->input_handlers[JOYSTICK], i);
            ((void(*)(joystick_state_e))*fn)(state);
        }
    }
}

static void handle_touch_screen(void)
{
    uint16_t x_f1 = 0, y_f1 = 0, x_f2 = 0, y_f2 = 0;
    uint8_t finger_count = touch_screen_get_position(&x_f1, &y_f1, &x_f2, &y_f2);

    int count = dyn_array_count(INPUT_MANAGER->input_handlers[TOUCH_SCREEN]);

    for (int i = 0; i < count; i++)
    {
        void** fn = dyn_array_get(INPUT_MANAGER->input_handlers[TOUCH_SCREEN], i);
        ((void(*)(uint8_t, uint16_t, uint16_t, uint16_t, uint16_t))*fn)(finger_count, x_f1, y_f1, x_f2, y_f2);
    }
}
