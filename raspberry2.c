#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ws2811.h>

#define LED_COUNT   16      // Number of LEDs
#define TARGET_FREQ 800000  // Frequency of the WS281x LED signal
#define GPIO_PIN    18      // GPIO pin connected to the LEDs
#define DMA_NUM     5       // DMA channel to use, we are using 5 as it is not used

int main()
{
    ws2811_t ledstring = 
    {
        .freq = TARGET_FREQ,
        .dmanum = DMA_NUM,
        .channel = 
        {
            [0] = 
            {
                .gpionum = GPIO_PIN,
                .count = LED_COUNT,
                .invert = 0,
                .brightness = 255,
            },
            [1] = 
            {
                .gpionum = 0,
                .count = 0,
                .invert = 0,
                .brightness = 0,
            },
        },
    };

    // Initialize the library
    if (ws2811_init(&ledstring))
    {
        printf("Failed to initialize the library. Exiting.\n");
        return -1;
    }

    // Turn on each LED
    for (int i = 0; i < LED_COUNT; i++)
    {
        ledstring.channel[0].leds[i] = 0xFFFFFF;  // Set color to white
    }

    // Send the colors to the LED strip
    if (ws2811_render(&ledstring))
    {
        printf("Failed to render the colors. Exiting.\n");
        return -1;
    }

    // Wait a bit, then turn off all LEDs
    sleep(5);

    for (int i = 0; i < LED_COUNT; i++)
    {
        ledstring.channel[0].leds[i] = 0;  // Set color to off
    }

    // Send the off command to the LED strip
    if (ws2811_render(&ledstring))
    {
        printf("Failed to render the colors. Exiting.\n");
        return -1;
    }

    // Clean up and exit
    ws2811_fini(&ledstring);

    return 0;
}
