#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ws2811.h>
#include <unistd.h>
#include <math.h>

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18  // this should be the GPIO pin you connected DIN to
#define DMA                     5
#define LED_COUNT               45  // the number of LEDs in your ring

ws2811_t ledstring = {
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel = {
        [0] = {
            .gpionum = GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
            .strip_type = WS2811_STRIP_RGB,
        },
        [1] = {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

// TreeNode structure
typedef struct TreeNode {
    int led_index;
    struct TreeNode* next;
} TreeNode;

TreeNode* createNode(int led_index) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    newNode->led_index = led_index;
    newNode->next = NULL;

    return newNode;
}

void hsv_to_rgb(float h, float s, float v, uint8_t* r, uint8_t* g, uint8_t* b);  // Function prototype

void traverseList(TreeNode* root) {
    TreeNode* current = root;

    int num_leds = ledstring.channel[0].count;

    // Set a different color for each LED
    for (int i = 0; i < num_leds; i++) {
        float hue = (float)i / num_leds;  // Calculate hue value (0.0 to 1.0)

        // Convert hue to RGB color
        uint8_t r, g, b;
        hsv_to_rgb(hue, 1.0, 1.0, &r, &g, &b);

        // Set LED color
        ledstring.channel[0].leds[i] = (r << 16) | (g << 8) | b;
    }
}

void hsv_to_rgb(float h, float s, float v, uint8_t* r, uint8_t* g, uint8_t* b) {
    if (s == 0.0f) {
        *r = *g = *b = (uint8_t)(v * 255);
        return;
    }

    h *= 6.0;
    int i = (int)floor(h);
    float f = h - i;
    float p = v * (1.0 - s);
    float q = v * (1.0 - s * f);
    float t = v * (1.0 - s * (1.0 - f));

    switch (i) {
        case 0:
            *r = (uint8_t)(v * 255);
            *g = (uint8_t)(t * 255);
            *b = (uint8_t)(p * 255);
            break;
        case 1:
            *r = (uint8_t)(q * 255);
            *g = (uint8_t)(v * 255);
            *b = (uint8_t)(p * 255);
            break;
        case 2:
            *r = (uint8_t)(p * 255);
            *g = (uint8_t)(v * 255);
            *b = (uint8_t)(t * 255);
            break;
        case 3:
            *r = (uint8_t)(p * 255);
            *g = (uint8_t)(q * 255);
            *b = (uint8_t)(v * 255);
            break;
        case 4:
            *r = (uint8_t)(t * 255);
            *g = (uint8_t)(p * 255);
            *b = (uint8_t)(v * 255);
            break;
        default:
            *r = (uint8_t)(v * 255);
            *g = (uint8_t)(p * 255);
            *b = (uint8_t)(q * 255);
            break;
    }
}

void freeList(TreeNode* root) {
    TreeNode* tmp;

    while (root != NULL) {
       tmp = root;
       root = root->next;
       free(tmp);
    }
}

int main()
{
    ws2811_return_t ret;

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    // Initialize the root of the list
    TreeNode* root = createNode(0); // LED 1
    TreeNode* current = root;

    // Create the rest of the nodes in a linked list
    for (int i = 1; i < LED_COUNT; i++) {
        current->next = createNode(i);
        current = current->next;
    }

    int seconds_elapsed = 0;

    while (1) {
        if (seconds_elapsed < 16) {
            traverseList(root);
        } else {
            // Turn off all LEDs
            memset(ledstring.channel[0].leds, 0, LED_COUNT * sizeof(ws2811_led_t));
        }

        ws2811_render(&ledstring);

        usleep(1000000); // wait for 1 second

        seconds_elapsed++;
    }

    // Free the memory allocated for the list
    freeList(root);

    ws2811_fini(&ledstring);
    return ret;
}
