#ifndef CAN_TX_TASK_H
#define CAN_TX_TASK_H

#include "cmsis_os2.h"
#include "drivers/mcp2515/mcp2515_comm.h"

void StartCanTxTask(void *argument);

#endif // CAN_TX_TASK_H
