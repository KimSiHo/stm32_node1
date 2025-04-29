#include <stdio.h>
#include "can_app.h"

void AppCatorTask(void *argument) {
    MCP2515_CANMessage msg;
    uint8_t counter = 0;

    for (;;) {
        msg.id = 0x321;
        msg.dlc = 2;
        msg.data[0] = counter++;
        msg.data[1] = 0x55;

        if (osMessageQueuePut(canTxQueueHandle, &msg, 0, 0) == osOK) {
        	printf("[App] Sent to CAN TX queue: ID=0x%X Data=%02X %02X\r\n",
        	       (unsigned int)msg.id, msg.data[0], msg.data[1]);
        } else {
            printf("[App] Failed to send to CAN TX queue\r\n");
        }

        osDelay(1000);
    }
}
