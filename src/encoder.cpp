#include "encoder.h"

static void __encoder_isr_a(void* ctx) {
    encoder_t* enc = (encoder_t*)ctx;

    // What do we do now? We have spun in a certain direction
}

static void __encoder_isr_b(void* ctx) {
    encoder_t* enc = (encoder_t*)ctx;

    // What do we do now? We have spun in a certain direction
}

static void __encoder_isr_btn(void* ctx) {
    encoder_t* enc = (encoder_t*)ctx;
    // how to call the callback
    if (enc->button_cb) enc->button_cb(enc);
}

void encoder_init(encoder_t* enc, pin_t pin_a, pin_t pin_b, pin_t pin_btn) {
    // Initialize the encoder struct by giving it reasonable values
    // And initialize the hardware if needed
    enc->pin_a = pin_a;
    enc->pin_b = pin_b; 
    enc->pin_btn = pin_btn;
}

void encoder_set_spin_callback(encoder_t* enc, void (*cb)(encoder_t* enc, int32_t delta)) {
    enc->spin_cb = cb;
}

void encoder_set_button_callback(encoder_t* enc, void (*cb)(encoder_t* enc)) {
    enc->button_cb = cb;
}

int32_t encoder_get_position(const encoder_t* enc) {
    return enc->position;
}

void encoder_set_position(encoder_t* enc, int32_t pos) {
    enc->position = pos;
}

void attach_encoder_interrupts(encoder_t* enc) {
    attachInterruptArg(digitalPinToInterrupt(enc->pin_a), __encoder_isr_a, enc, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(enc->pin_b), __encoder_isr_b, enc, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(enc->pin_btn), __encoder_isr_btn, enc, RISING);
}
