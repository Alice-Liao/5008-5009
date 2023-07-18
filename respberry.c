#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ws2811.h>
#include <wiringPi.h>

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18  // this should be the GPIO pin you connected DIN to
#define DMA                     5
#define LED_COUNT               16  // the number of LEDs in your ring
#define SWITCH_PIN              2   // this should be the GPIO pin you connected the switch to

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
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int led_index) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    newNode->led_index = led_index;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void traverseTree(TreeNode* root, uint32_t color_on, uint32_t color_off) {
    if (root == NULL)
        return;

    // Toggle the LED associated with this node
    ws2811_led_t color = root->led_index % 2 == 0 ? color_on : color_off;
    ledstring.channel[0].leds[root->led_index] = color;

    traverseTree(root->left, color_on, color_off);
    traverseTree(root->right, color_on, color_off);
}

volatile int state = 0;
void switchInterrupt(void) {
    state = !state; // toggle state

    uint32_t evenColor = state == 1 ? 0x00ff00 : 0x000000; // green or off
    uint32_t oddColor = state == 1 ? 0x000000 : 0xff0000; // off or red

    TreeNode* root = createNode(0); // LED 1
    root->left = createNode(1); // LED 2
    root->right = createNode(2); // LED 3
    // ... Continue creating the tree nodes for your LED configuration ...

    traverseTree(root, evenColor, oddColor);

    ws2811_render(&ledstring);
}

int main()
{
    if (wiringPiSetupGpio() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi\n");
        return 1;
    }

    wiringPiISR(SWITCH_PIN, INT_EDGE_BOTH, switchInterrupt);

    ws2811_return_t ret;

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    while (1) {
        // The switchInterrupt function will handle all the LED control.
        // The main thread just needs to sleep.
        delay(1000);
    }

    ws2811_fini(&ledstring);
    return ret;
}
