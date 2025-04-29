#ifndef MCP2515_H
#define MCP2515_H

#include "stm32f1xx_hal.h"
#include "spi.h"

#include "mcp2515_cmd.h"
#include "mcp2515_reg.h"
#include "mcp2515_mode.h"
#include "mcp2515_gpio.h"

// Function Prototypes
HAL_StatusTypeDef MCP2515_Reset(void);
HAL_StatusTypeDef MCP2515_ReadRegister(uint8_t address, uint8_t *data);
HAL_StatusTypeDef MCP2515_WriteRegister(uint8_t address, uint8_t data);
HAL_StatusTypeDef MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);
HAL_StatusTypeDef MCP2515_Initialize(void);
HAL_StatusTypeDef MCP2515_SetMode(uint8_t mode);

#endif // MCP2515_H
