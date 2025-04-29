#ifndef CAN_RX_TASK_H
#define CAN_RX_TASK_H

#include "cmsis_os2.h"
#include "drivers/mcp2515/mcp2515_comm.h"

void StartCanRxTask(void *argument);

#endif // CAN_RX_TASK_H
