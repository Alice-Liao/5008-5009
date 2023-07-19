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

void traverseList(TreeNode* root, uint32_t oddColors[], uint32_t evenColors[]) {
    TreeNode* current = root;

    int num_leds = ledstring.channel[0].count;
    int num_odd_colors = sizeof(oddColors) / sizeof(oddColors[0]);
    int num_even_colors = sizeof(evenColors) / sizeof(evenColors[0]);

    // Set the LED colors based on their index
    for (int i = 0; i < num_leds; i++) {
        uint32_t color;

        if (i % 2 == 0) {
            // Even index
            int index = i / 2 % num_even_colors;
            color = evenColors[index];
        } else {
            // Odd index
            int index = (i - 1) / 2 % num_odd_colors;
            color = oddColors[index];
        }

        ledstring.channel[0].leds[i] = color;
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

int main() {
    ws2811_return_t ret;

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
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

    // Define the colors for odd and even lights
    uint32_t oddColors[] = {0xF8B195, 0xF67280, 0xC06C84, 0x6C5B7B, 0x355C7D};
    uint32_t evenColors[] = {0x99B898, 0xFECEAB, 0xFF847C, 0xE84A5F, 0x2A363B};

    while (seconds_elapsed < 16) {
        if (seconds_elapsed % 2 == 0) {
            // Even seconds: Turn on even lights
            traverseList(root, oddColors, evenColors);
        } else {
            // Odd seconds: Turn on odd lights
            traverseList(root, evenColors, oddColors);
        }

        ws2811_render(&ledstring);

        usleep(1000000); // wait for 1 second

        seconds_elapsed++;
    }

    // Turn off all LEDs
    memset(ledstring.channel[0].leds, 0, LED_COUNT * sizeof(ws2811_led_t));
    ws2811_render(&ledstring);

    // Free the memory allocated for the list
    freeList(root);

    ws2811_fini(&ledstring);
    return ret;
}
ledtree2.c: In function ‘traverseList’:
ledtree2.c:74:32: warning: ‘sizeof’ on array function parameter ‘oddColors’ will return size of ‘uint32_t *’ {aka ‘unsigned int *’} [-Wsizeof-array-argument]
     int num_odd_colors = sizeof(oddColors) / sizeof(oddColors[0]);
                                ^
ledtree2.c:70:44: note: declared here
 void traverseList(TreeNode* root, uint32_t oddColors[], uint32_t evenColors[]) {
                                   ~~~~~~~~~^~~~~~~~~~~
ledtree2.c:75:33: warning: ‘sizeof’ on array function parameter ‘evenColors’ will return size of ‘uint32_t *’ {aka ‘unsigned int *’} [-Wsizeof-array-argument]
     int num_even_colors = sizeof(evenColors) / sizeof(evenColors[0]);
                                 ^
ledtree2.c:70:66: note: declared here
 void traverseList(TreeNode* root, uint32_t oddColors[], uint32_t evenColors[]) {


