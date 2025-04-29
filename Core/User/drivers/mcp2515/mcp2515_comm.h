#ifndef MCP2515_COMM_H
#define MCP2515_COMM_H

#include <cmsis_os2.h>
#include "drivers/mcp2515/mcp2515.h"

typedef struct
{
    uint32_t id;          // CAN ID (11-bit)
    uint8_t dlc;          // Data Length Code (0~8)
    uint8_t data[8];      // 데이터 (최대 8바이트)
} MCP2515_CANMessage;

extern osMessageQueueId_t canTxQueueHandle;
extern osMessageQueueId_t canRxQueueHandle;

HAL_StatusTypeDef MCP2515_SendMessage(const MCP2515_CANMessage *msg);
HAL_StatusTypeDef MCP2515_ReceiveMessage(MCP2515_CANMessage *msg);
HAL_StatusTypeDef MCP2515_InitMessageQueues(void);

#endif // MCP2515_COMM_H
