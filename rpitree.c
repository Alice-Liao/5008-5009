#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ws2811.h>
#include <unistd.h>

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

void traverseList(TreeNode* root, uint32_t color_on, uint32_t color_off) {
    TreeNode* current = root;

    while(current != NULL) {
        // Toggle the LED associated with this node
        ws2811_led_t color = current->led_index % 2 == 0 ? color_on : color_off;
        ledstring.channel[0].leds[current->led_index] = color;

        current = current->next;
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

int state = 0;

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

    while (1) {
        state = !state; // toggle state

        uint32_t evenColor = state == 1 ? 0x00ff00 : 0x000000; // green or off
        uint32_t oddColor = state == 1 ? 0x000000 : 0xff0000; // off or red

        traverseList(root, evenColor, oddColor);

        ws2811_render(&ledstring);

        usleep(1000000); // wait for 1 second
    }

    // Free the memory allocated for the list
    freeList(root);

    ws2811_fini(&ledstring);
    return ret;
}
