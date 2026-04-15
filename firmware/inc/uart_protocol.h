#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <stdint.h>

void uart_send_telemetry(uint8_t mode, float pos, float vel, float torque, float output);
uint8_t uart_receive_packet(uint8_t *buffer, uint8_t len, uint32_t timeout_ms);

#endif
