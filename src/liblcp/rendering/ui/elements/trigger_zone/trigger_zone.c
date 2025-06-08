#include "trigger_zone.h"
#include "../../../../log/log.h"

static trigger_zone_manager_t trigger_zone_manager_singleton;

bool trigger_zone_init()
{
    if (trigger_zone_manager_singleton.zones != NULL)
    {
        LOG_ERROR("Trigger_zone_manager_singleton is already exist !", false);
        return false;
    }

    trigger_zone_manager_singleton.zones = dyn_array_create(4, sizeof(trigger_zone_t), NULL);
    if (!trigger_zone_manager_singleton.zones) return false;

    return true;
}

void trigger_zone_add(const trigger_zone_t tzone)
{
    dyn_array_push_back(trigger_zone_manager_singleton.zones, &tzone);
}

void trigger_zone_clear()
{
    dyn_array_clear(trigger_zone_manager_singleton.zones);
}

//regarde si la position est dans une des zones de trigger
void trigger_zone_test(const uint16_t x, const uint16_t y)
{
    int count = dyn_array_count(trigger_zone_manager_singleton.zones);
    for (int i = 0; i < count; i++)
    {
        trigger_zone_t *tzone = dyn_array_get(trigger_zone_manager_singleton.zones, i);
        if (in_rect(tzone->rect, x, y))
        {
            tzone->on_trigger();
            break;
        }
    }
}

