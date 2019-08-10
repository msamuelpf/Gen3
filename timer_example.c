/* HAL-only entry function */
#include "hal_data.h"

#define COUNTS_PER_MILLISECONDS (120E6 / 1000)

void hal_entry(void)
{
    /* TODO: add your own code here */
    bool isOn = true;

    timer_size_t counts = 0;

    g_timer0.p_api->open ( g_timer0.p_ctrl, g_timer0.p_cfg);
    g_timer0.p_api->start(g_timer0.p_ctrl);

    while(1)
    {
        g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00,isOn);

        isOn = !isOn;

        while(1)
        {
            g_timer0.p_api->counterGet(g_timer0.p_ctrl, &counts);

            if(counts > (250*COUNTS_PER_MILLISECONDS))
            {
                g_timer0.p_api->reset(g_timer0.p_ctrl);
                break;
            }
        }
    }
}
