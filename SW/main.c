#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN 25  // Define the GPIO pin for the LED (GPIO 25)

bool ledState = true;  // Track the LED state (on/off)

// Interrupt Service Routine (ISR) for the timer
bool repeating_timer_callback(struct repeating_timer *t) {
    // Toggle the LED state every time the interrupt triggers
    ledState = !ledState;
    gpio_put(LED_PIN, ledState);  // Update the LED based on ledState
    return true; // Return true to keep the timer running
}

int main() {
    // Initialize standard I/O and GPIO
    stdio_init_all();

    // Initialize the LED pin (GPIO 25)
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);  // Set LED pin as an output

    struct repeating_timer timer;

    // Initialize the timer to trigger every 1 second (1000 milliseconds)
    add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);
    
    // Main loop: Do nothing, just waiting for the timer interrupt
    while (1) {
        tight_loop_contents();  // Let the ISR handle the LED toggling
    }
}