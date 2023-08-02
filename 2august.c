#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ws2811.h>
#include <unistd.h>

#define TARGET_FREQ WS2811_TARGET_FREQ
#define GPIO_PIN 18
#define DMA 5
#define LED_COUNT 45

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

// TreeNode structure for creating a binary tree of LEDs
typedef struct TreeNode {
    int led_index;
    struct TreeNode* left;  // Left child
    struct TreeNode* right; // Right child
} TreeNode;

TreeNode* createNode(int led_index) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    newNode->led_index = led_index;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void traverseTree(TreeNode* root, uint32_t color_on, uint32_t color_off) {
    if (root != NULL) {
        ws2811_led_t color = root->led_index % 2 == 0 ? color_on : color_off;
        ledstring.channel[0].leds[root->led_index] = color;
        traverseTree(root->left, color_on, color_off); // Traverse left subtree
        traverseTree(root->right, color_on, color_off); // Traverse right subtree
    }
}

void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    ws2811_return_t ret;

    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    // Create the binary tree of LEDs
    TreeNode* root = createNode(0); // Root
    TreeNode* current = root;

    for (int i = 1; i < LED_COUNT; i++) {
        if (i % 2 != 0) {
            current->left = createNode(i);
            current = current->left;
        } else {
            current->right = createNode(i);
            current = current->right;
        }
    }

    int state = 0;
    while (1) {
        state = !state; // Toggle state
        uint32_t evenColor = state == 1 ? 0x00ff00 : 0x000000; // Green or off
        uint32_t oddColor = state == 1 ? 0x000000 : 0xff0000; // Off or red

        traverseTree(root, evenColor, oddColor);

        ws2811_render(&ledstring);

        usleep(1000000); // Wait for 1 second
    }

    // Cleanup
    freeTree(root);
    ws2811_fini(&ledstring);
    return ret;
}
