#include "rm_motor.h"

#include "stm32f4xx_hal_can.h"

__weak CAN_HandleTypeDef hcan1 = {};
__weak CAN_HandleTypeDef hcan2 = {};

/*static*/ int16_t rm_current_cmd[2][8] = {};
/*static*/ volatile RM_Feedback rm_feedback[2][8] = {};

static void rm_pack_current_cmd(uint8_t data[8], const int16_t current_cmd[4]) {
  data[0] = current_cmd[0] >> 8;
  data[1] = current_cmd[0];
  data[2] = current_cmd[1] >> 8;
  data[3] = current_cmd[1];
  data[4] = current_cmd[2] >> 8;
  data[5] = current_cmd[2];
  data[6] = current_cmd[3] >> 8;
  data[7] = current_cmd[3];
}

static void from_bigendian(const uint8_t* in, volatile void* out) {
  volatile uint8_t* o = out;
  *o = *(in + 1);
  *(o + 1) = *in;
}

static void rm_unpack_feedback(const uint8_t data[8], volatile RM_Feedback* feedback) {
  from_bigendian(data, &feedback->encoder);
  from_bigendian(data + 2, &feedback->vel_rpm);
  from_bigendian(data + 4, &feedback->raw_current);
  feedback->temperature = data[6];

  feedback->current = (float)feedback->raw_current / RM_CURRENT_RAW_MAX * RM_CURRENT_MAX;
}

static HAL_StatusTypeDef rm_can_tx(CAN_HandleTypeDef* hcan, uint32_t id, const uint8_t* data, uint8_t len) {
  CAN_TxHeaderTypeDef tx_header = {
      .StdId = id,
      .IDE = CAN_ID_STD,
      .RTR = CAN_RTR_DATA,
      .DLC = len,
      .TransmitGlobalTime = DISABLE,
  };

  uint32_t tx_mailbox;
  return HAL_CAN_AddTxMessage(hcan, &tx_header, data, &tx_mailbox);
}

void rm_can_init(CAN_HandleTypeDef* hcan) {
  CAN_FilterTypeDef filter_config = {
      .FilterIdHigh = 0x000,
      .FilterIdLow = 0x000,
      .FilterMaskIdHigh = 0x000,
      .FilterMaskIdLow = 0x000,
      .FilterFIFOAssignment = CAN_FILTER_FIFO0,
      .FilterMode = CAN_FILTERMODE_IDMASK,
      .FilterScale = CAN_FILTERSCALE_32BIT,
      .FilterActivation = ENABLE,
      .FilterBank = hcan == &hcan1 ? 0 : 14,
      .SlaveStartFilterBank = 14,
  };

  HAL_CAN_ConfigFilter(hcan, &filter_config);
  HAL_CAN_Start(hcan);
  HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void rm_ctrl_loop(CAN_HandleTypeDef* hcan) {
  uint8_t data[8];

  rm_pack_current_cmd(data, rm_current_cmd[hcan == &hcan1 ? 0 : 1] + 0);
  rm_can_tx(hcan, RM_CAN_TX_GRP1_ID, data, sizeof(data));

  rm_pack_current_cmd(data, rm_current_cmd[hcan == &hcan1 ? 0 : 1] + 4);
  rm_can_tx(hcan, RM_CAN_TX_GRP2_ID, data, sizeof(data));
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
  CAN_RxHeaderTypeDef rx_header;
  uint8_t rx_data[8];
  while (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK) {
    if (rx_header.StdId < RM_CAN_RX_ID_BASE || rx_header.StdId >= RM_CAN_RX_ID_BASE + NUM_OF_RM_MOTORS) {
      continue;
    }

    if (rx_header.DLC != 8) {
      continue;
    }

    RM_Motor motor = rx_header.StdId - RM_CAN_RX_ID_BASE;
    rm_unpack_feedback(rx_data, &rm_feedback[hcan == &hcan1 ? 0 : 1][motor]);
  }
}

void rm_set_current_setpoint(CAN_HandleTypeDef* hcan, RM_Motor motor, float current) {
  if (current > RM_CURRENT_SOFT_MAX) {
    current = RM_CURRENT_SOFT_MAX;
  } else if (current < -RM_CURRENT_SOFT_MAX) {
    current = -RM_CURRENT_SOFT_MAX;
  }

  int16_t raw_current = current / RM_CURRENT_MAX * RM_CURRENT_RAW_MAX;
  rm_current_cmd[hcan == &hcan1 ? 0 : 1][motor] = raw_current;
}

float rm_get_current_setpoint(CAN_HandleTypeDef* hcan, RM_Motor motor) {
  return (float)rm_current_cmd[hcan == &hcan1 ? 0 : 1][motor] / RM_CURRENT_RAW_MAX * RM_CURRENT_MAX;
}

const volatile RM_Feedback* rm_get_feedback(CAN_HandleTypeDef* hcan, RM_Motor motor) {
  return &rm_feedback[hcan == &hcan1 ? 0 : 1][motor];
}

uint16_t rm_get_encoder(CAN_HandleTypeDef* hcan, RM_Motor motor) { return rm_get_feedback(hcan, motor)->encoder; }

int16_t rm_get_actual_vel(CAN_HandleTypeDef* hcan, RM_Motor motor) { return rm_get_feedback(hcan, motor)->vel_rpm; }

float rm_get_actual_current(CAN_HandleTypeDef* hcan, RM_Motor motor) {
  return (float)rm_get_feedback(hcan, motor)->current;
}

uint8_t rm_get_temperature(CAN_HandleTypeDef* hcan, RM_Motor motor) {
  return rm_get_feedback(hcan, motor)->temperature;
}
