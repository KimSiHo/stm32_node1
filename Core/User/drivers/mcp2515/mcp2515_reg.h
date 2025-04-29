#ifndef MCP2515_REG_H
#define MCP2515_REG_H

// Control & Status
#define MCP2515_REG_CANCTRL            0x0F
#define MCP2515_REG_CANSTAT            0x0E
#define MCP2515_REG_CNF1               0x2A
#define MCP2515_REG_CNF2               0x29
#define MCP2515_REG_CNF3               0x28

// Interrupts
#define MCP2515_REG_CANINTE            0x2B
#define MCP2515_REG_CANINTF            0x2C
#define MCP2515_REG_TXB0CTRL           0x30
#define MCP2515_REG_TXB1CTRL           0x40
#define MCP2515_REG_TXB2CTRL           0x50

// RX Buffer 0
#define MCP2515_REG_RXB0CTRL           0x60
#define MCP2515_REG_RXB0SIDH           0x61
#define MCP2515_REG_RXB0SIDL           0x62
#define MCP2515_REG_RXB0DLC            0x65
#define MCP2515_REG_RXB0D0             0x66

// RX Buffer 1
#define MCP2515_REG_RXB1CTRL           0x70
#define MCP2515_REG_RXB1SIDH           0x71
#define MCP2515_REG_RXB1SIDL           0x72
#define MCP2515_REG_RXB1DLC            0x75
#define MCP2515_REG_RXB1D0             0x76

// TX Buffer 0
#define MCP2515_REG_TXB0SIDH           0x31

#endif // MCP2515_REG_H
