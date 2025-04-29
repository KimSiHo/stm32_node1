#ifndef MCP2515_CMD_H
#define MCP2515_CMD_H

// Basic SPI Commands
#define MCP2515_CMD_RESET              0xC0
#define MCP2515_CMD_READ               0x03
#define MCP2515_CMD_WRITE              0x02
#define MCP2515_CMD_BIT_MODIFY         0x05
#define MCP2515_CMD_READ_STATUS        0xA0
#define MCP2515_CMD_RX_STATUS          0xB0

// Request-to-Send
#define MCP2515_CMD_RTS_TX0            0x81
#define MCP2515_CMD_RTS_TX1            0x82
#define MCP2515_CMD_RTS_TX2            0x84

// Read RX Buffer
#define MCP2515_CMD_READ_RXB0_ID_D0    0x90
#define MCP2515_CMD_READ_RXB0_D0       0x92
#define MCP2515_CMD_READ_RXB1_ID_D0    0x94
#define MCP2515_CMD_READ_RXB1_D0       0x96

// Load TX Buffer
#define MCP2515_CMD_LOAD_TXB0_ID_D0    0x40
#define MCP2515_CMD_LOAD_TXB0_D0       0x41
#define MCP2515_CMD_LOAD_TXB1_ID_D0    0x42
#define MCP2515_CMD_LOAD_TXB2_ID_D0    0x44

#endif // MCP2515_CMD_H
