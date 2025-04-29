#include <stdio.h>
#include "can_rx_task.h"

void StartCanRxTask(void *argument) {
    MCP2515_CANMessage rxMsg;

    for (;;) {
        if (MCP2515_ReceiveMessage(&rxMsg) == HAL_OK) {
            printf("[CAN RX Task] Recv ID: 0x%03X DLC: %d\r\n", (unsigned int)rxMsg.id, rxMsg.dlc);
        }

        osDelay(10); // 과도한 폴링 방지
    }
}
