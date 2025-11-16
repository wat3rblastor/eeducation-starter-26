#include "button.h"

void button_init(button_t* btn, pin_t pin) {
    // Setup the button by setting it's pin, and telling
    // associated hardware what it should do

    // (Hint), you'll want to set up an interrupt!
    btn->pin = pin;
    attach_button_interrupt(btn, pin);
}

void button_set_callback(button_t* btn, void (*cb)(button_t* ctx), void* ctx) {    
    // Update button struct to set user callback
    btn->callback = cb;

    // Update button struct with user data
    btn->ctx = ctx;
}

bool button_read(const button_t* btn) {
    // Check if this button has been read
    return false;
}

static void __button_callback(void *ctx) {
    button_t *btn = (button_t *)(ctx);

    // Something has triggered the interrupt, what should happen?
    // Perhaps call the user callback?
    btn->callback(btn);
}

void attach_button_interrupt(button_t *btn, pin_t pin) {
    attachInterruptArg(digitalPinToInterrupt(pin), __button_callback, btn, pin);
}