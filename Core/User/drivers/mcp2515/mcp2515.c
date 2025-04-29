#include <stdio.h>
#include "mcp2515.h"

HAL_StatusTypeDef MCP2515_Reset(void) {
    MCP2515_CS_LOW();

    uint8_t cmd = MCP2515_CMD_RESET;
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);

    MCP2515_CS_HIGH();

    if (ret != HAL_OK) {
        printf("[MCP2515] SPI Reset command failed!\r\n");
    } else {
        printf("[MCP2515] Reset command sent OK\r\n");
    }

    HAL_Delay(100);

    return ret;
}

HAL_StatusTypeDef MCP2515_ReadRegister(uint8_t address, uint8_t *data) {
    if (data == NULL)
        return HAL_ERROR;

    uint8_t tx[2] = {MCP2515_CMD_READ, address};

    MCP2515_CS_LOW();

    HAL_StatusTypeDef ret;
    ret = HAL_SPI_Transmit(&hspi1, tx, 2, HAL_MAX_DELAY);

    if (ret != HAL_OK) {
        MCP2515_CS_HIGH();
        return ret;
    }

    ret = HAL_SPI_Receive(&hspi1, data, 1, HAL_MAX_DELAY);
    MCP2515_CS_HIGH();

    return ret;
}

HAL_StatusTypeDef MCP2515_WriteRegister(uint8_t address, uint8_t data) {
    uint8_t tx[3] = {MCP2515_CMD_WRITE, address, data};

    MCP2515_CS_LOW();
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(&hspi1, tx, 3, HAL_MAX_DELAY);
    MCP2515_CS_HIGH();

    return ret;
}

HAL_StatusTypeDef MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data) {
    uint8_t tx[4] = {MCP2515_CMD_BIT_MODIFY, address, mask, data};

    MCP2515_CS_LOW();
    HAL_StatusTypeDef ret = HAL_SPI_Transmit(&hspi1, tx, 4, HAL_MAX_DELAY);
    MCP2515_CS_HIGH();

    return ret;
}

HAL_StatusTypeDef MCP2515_SetMode(uint8_t mode) {
    if (MCP2515_BitModify(MCP2515_REG_CANCTRL, 0xE0, (mode << 5)) != HAL_OK) {
        printf("Error: Failed to set mode %u via BitModify\r\n", mode);
        return HAL_ERROR;
    }

    HAL_Delay(10);

    uint8_t canstat;
    if (MCP2515_ReadRegister(MCP2515_REG_CANSTAT, &canstat) != HAL_OK)
        return HAL_ERROR;

    uint8_t opmod = (canstat >> 5) & 0x07;
    if (opmod != mode) {
        printf("Error: Mode mismatch. Requested=%u, Actual(CANSTAT)=0x%02X\r\n", mode, canstat);
        return HAL_ERROR;
    }

    printf("MCP2515 entered mode %u (CANSTAT=0x%02X)\r\n", mode, canstat);
    return HAL_OK;
}

HAL_StatusTypeDef MCP2515_Initialize(void) {
    printf("MCP2515 Initialize Start\r\n");

    // 1. Reset MCP2515
    if (MCP2515_Reset() != HAL_OK) {
        printf("Error: MCP2515 Reset failed\r\n");
        return HAL_ERROR;
    }

    // 2. Configuration Mode 진입 확인
    uint8_t canstat;
    if (MCP2515_ReadRegister(MCP2515_REG_CANSTAT, &canstat) != HAL_OK)
        return HAL_ERROR;

    uint8_t opmod = (canstat >> 5) & 0x07;
    if (opmod != MCP2515_MODE_CONFIGURATION) {
        printf("Error: Not in Configuration Mode (CANSTAT=0x%02X)\r\n", canstat);
        return HAL_ERROR;
    }

    printf("MCP2515 entered Configuration Mode\r\n");

    // 3. Bit Timing 설정
    if (MCP2515_WriteRegister(MCP2515_REG_CNF1, 0x01) != HAL_OK ||
        MCP2515_WriteRegister(MCP2515_REG_CNF2, 0xB1) != HAL_OK ||
        MCP2515_WriteRegister(MCP2515_REG_CNF3, 0x02) != HAL_OK) {
        printf("Error: Failed to set bit timing\r\n");
        return HAL_ERROR;
    }

    printf("Bit Timing set for 500kbps\r\n");

    // 4. Normal Mode 진입
    return MCP2515_SetMode(MCP2515_MODE_NORMAL);

    // 4. Loopback Mode 진입
    // return MCP2515_SetMode(MCP2515_MODE_LOOPBACK);
}
