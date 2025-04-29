#include <stdio.h>
#include "mcp2515_comm.h"

osMessageQueueId_t canTxQueueHandle;
osMessageQueueId_t canRxQueueHandle;

HAL_StatusTypeDef MCP2515_InitMessageQueues(void) {
    uint32_t queueLength = 10;

    canTxQueueHandle = osMessageQueueNew(queueLength, sizeof(MCP2515_CANMessage), NULL);
    if (canTxQueueHandle == NULL) {
        printf("Error: Failed to create CAN TX queue\r\n");
        return HAL_ERROR;
    }

    canRxQueueHandle = osMessageQueueNew(queueLength, sizeof(MCP2515_CANMessage), NULL);
    if (canRxQueueHandle == NULL) {
        printf("Error: Failed to create CAN RX queue\r\n");
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef MCP2515_SendMessage(const MCP2515_CANMessage *msg) {
    if (msg == NULL)
        return HAL_ERROR;

    // 1. ID 설정 (Standard ID 11bit 기준)
    uint8_t sidh = (msg->id >> 3) & 0xFF;
    uint8_t sidl = (msg->id << 5) & 0xE0;

    MCP2515_WriteRegister(0x31, sidh); // TXB0SIDH
    MCP2515_WriteRegister(0x32, sidl); // TXB0SIDL

    // 2. DLC (Data Length Code)
    MCP2515_WriteRegister(0x35, msg->dlc & 0x0F); // TXB0DLC

    // 3. 데이터 전송
    for (uint8_t i = 0; i < msg->dlc; i++) {
        MCP2515_WriteRegister(0x36 + i, msg->data[i]); // TXB0Dm
    }

    // 4. 전송 요청 (TXREQ 비트 세트)
    MCP2515_BitModify(0x30, 0x08, 0x08); // TXB0CTRL

    return HAL_OK;
}

HAL_StatusTypeDef MCP2515_ReceiveMessage(MCP2515_CANMessage *msg) {
    if (msg == NULL)
        return HAL_ERROR;

    uint8_t canintf;
    if (MCP2515_ReadRegister(MCP2515_REG_CANINTF, &canintf) != HAL_OK)
        return HAL_ERROR;

    // RXB0 수신 여부 확인 (RX0IF = bit 0)
    if (canintf & 0x01) {
        uint8_t sidh, sidl, dlc;
        if (MCP2515_ReadRegister(MCP2515_REG_RXB0SIDH, &sidh) != HAL_OK ||
            MCP2515_ReadRegister(MCP2515_REG_RXB0SIDL, &sidl) != HAL_OK ||
            MCP2515_ReadRegister(MCP2515_REG_RXB0DLC, &dlc) != HAL_OK)
            return HAL_ERROR;

        msg->id = ((uint32_t)sidh << 3) | (sidl >> 5);
        msg->dlc = dlc & 0x0F;

        for (uint8_t i = 0; i < msg->dlc; i++) {
            if (MCP2515_ReadRegister(MCP2515_REG_RXB0D0 + i, &msg->data[i]) != HAL_OK)
                return HAL_ERROR;
        }

        MCP2515_BitModify(MCP2515_REG_CANINTF, 0x01, 0x00); // RX0IF 클리어
        return HAL_OK;
    }

    // RXB1 수신 여부 확인 (RX1IF = bit 1)
    if (canintf & 0x02) {
        uint8_t sidh, sidl, dlc;
        if (MCP2515_ReadRegister(MCP2515_REG_RXB1SIDH, &sidh) != HAL_OK ||
            MCP2515_ReadRegister(MCP2515_REG_RXB1SIDL, &sidl) != HAL_OK ||
            MCP2515_ReadRegister(MCP2515_REG_RXB1DLC, &dlc) != HAL_OK)
            return HAL_ERROR;

        msg->id = ((uint32_t)sidh << 3) | (sidl >> 5);
        msg->dlc = dlc & 0x0F;

        for (uint8_t i = 0; i < msg->dlc; i++) {
            if (MCP2515_ReadRegister(MCP2515_REG_RXB1D0 + i, &msg->data[i]) != HAL_OK)
                return HAL_ERROR;
        }

        MCP2515_BitModify(MCP2515_REG_CANINTF, 0x02, 0x00); // RX1IF 클리어
        return HAL_OK;
    }

    return HAL_ERROR; // 수신된 메시지 없음
}
