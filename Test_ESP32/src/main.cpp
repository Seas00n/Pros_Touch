// #include <Arduino.h>
// #include "servor.hpp"
// #include <driver/uart.h>
// #define LED 2

// int interruptCounter = 0;
// hw_timer_t *timer = NULL;

// int deg = 0;
// int delta = 1;

// const int uart_buffer_size = (1024*2);
// uint8_t uart_buffer[uart_buffer_size] = {0}; 
// QueueHandle_t  uart_queue;


// // void IRAM_ATTR TimerEvent(){
// //   Serial.printf("InteruptCounter = %d\r\n",interruptCounter++);
// //   if(interruptCounter>5){
// //     interruptCounter = 1;
// //   }
// // }

// void setup(){
//     Serial.begin(115200);
//     pinMode(LED,OUTPUT);
//     // timer = timerBegin(0,80,true);
//     // timerAttachInterrupt(timer, &TimerEvent, true);
//     // timerAlarmWrite(timer, 1000000, true); 
//     // timerAlarmEnable(timer);
//     // Servor_Init(1, 13);

//     uart_config_t  uart_config = {
//       .baud_rate = 115200,
//       .data_bits = UART_DATA_8_BITS,
//       .parity = UART_PARITY_DISABLE,
//       .stop_bits = UART_STOP_BITS_1,
//       .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//       .source_clk = UART_SCLK_APB
//     };
//     uart_driver_install(UART_NUM_2, uart_buffer_size, 0, 0, NULL,0);
//     uart_param_config(UART_NUM_2, &uart_config);
//     uart_set_pin(UART_NUM_2,GPIO_NUM_17,GPIO_NUM_16,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);


// }
// void loop(){
//   // digitalWrite(LED,HIGH);
//   // delay(100);
//   // digitalWrite(LED,LOW);
//   // delay(100);
//   int len = uart_read_bytes(UART_NUM_2, uart_buffer, uart_buffer_size, 20/portTICK_RATE_MS);
//   printf("Receive %d\r\n",len);
//   uart_write_bytes(UART_NUM_2, (const char*)uart_buffer, len);
// }


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

/**
 * This is an example which echos any data it receives on UART1 back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: UART1
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below
 */

#define ECHO_TEST_TXD  (GPIO_NUM_23)
#define ECHO_TEST_RXD  (GPIO_NUM_18)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define BUF_SIZE (1024)

static void echo_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        // Write data back to the UART
        uart_write_bytes(UART_NUM_1, (const char *) data, len);
    }
}

void setup(){
  xTaskCreate(echo_task, "uart_echo_task", 1024, NULL, 10, NULL);
}
void loop(void)
{

}