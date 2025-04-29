#include <stdio.h>
#include "can_tx_task.h"

void StartCanTxTask(void *argument) {
    MCP2515_CANMessage txMsg;

    for (;;) {
        if (osMessageQueueGet(canTxQueueHandle, &txMsg, NULL, osWaitForever) == osOK) {
            MCP2515_SendMessage(&txMsg);
            printf("[CAN TX Task] Sent ID: 0x%03X DLC: %d\r\n", (unsigned int)txMsg.id, txMsg.dlc);
        }
    }
}
