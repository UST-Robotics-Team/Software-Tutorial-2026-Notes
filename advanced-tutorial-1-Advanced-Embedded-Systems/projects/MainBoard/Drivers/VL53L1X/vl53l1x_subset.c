/**
 ******************************************************************************
 * @file    vl53l0x_class.cpp
 * @author  IMG
 * @version V0.0.1
 * @date    14-December-2018
 * @brief   Implementation file for the VL53L1X driver class
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
*/


/* C subset adapted from ST's ULD Arduino class, mirrored by SparkFun.
 * Source commit e88f55d6d82a4a8c519ec90a2660e6ec799b4579.
 * Only the functions used by this course are retained; this is not the full ULD.
 * Platform errors are latched to prevent later successful calls hiding failures.
 */
#include "vl53l1x_subset.h"
#include "vl53l1_platform.h"
const uint8_t VL51L1X_DEFAULT_CONFIGURATION[] = {
	0x00, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
	0x01, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
	0x01, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
	0x01, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low (bits 3:0 must be 0x1), use SetInterruptPolarity() */
	0x02, /* 0x31 : bit 1 = interrupt depending on the polarity, use CheckForDataReady() */
	0x00, /* 0x32 : not user-modifiable */
	0x02, /* 0x33 : not user-modifiable */
	0x08, /* 0x34 : not user-modifiable */
	0x00, /* 0x35 : not user-modifiable */
	0x08, /* 0x36 : not user-modifiable */
	0x10, /* 0x37 : not user-modifiable */
	0x01, /* 0x38 : not user-modifiable */
	0x01, /* 0x39 : not user-modifiable */
	0x00, /* 0x3a : not user-modifiable */
	0x00, /* 0x3b : not user-modifiable */
	0x00, /* 0x3c : not user-modifiable */
	0x00, /* 0x3d : not user-modifiable */
	0xff, /* 0x3e : not user-modifiable */
	0x00, /* 0x3f : not user-modifiable */
	0x0F, /* 0x40 : not user-modifiable */
	0x00, /* 0x41 : not user-modifiable */
	0x00, /* 0x42 : not user-modifiable */
	0x00, /* 0x43 : not user-modifiable */
	0x00, /* 0x44 : not user-modifiable */
	0x00, /* 0x45 : not user-modifiable */
	0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high, 2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
	0x0b, /* 0x47 : not user-modifiable */
	0x00, /* 0x48 : not user-modifiable */
	0x00, /* 0x49 : not user-modifiable */
	0x02, /* 0x4a : not user-modifiable */
	0x0a, /* 0x4b : not user-modifiable */
	0x21, /* 0x4c : not user-modifiable */
	0x00, /* 0x4d : not user-modifiable */
	0x00, /* 0x4e : not user-modifiable */
	0x05, /* 0x4f : not user-modifiable */
	0x00, /* 0x50 : not user-modifiable */
	0x00, /* 0x51 : not user-modifiable */
	0x00, /* 0x52 : not user-modifiable */
	0x00, /* 0x53 : not user-modifiable */
	0xc8, /* 0x54 : not user-modifiable */
	0x00, /* 0x55 : not user-modifiable */
	0x00, /* 0x56 : not user-modifiable */
	0x38, /* 0x57 : not user-modifiable */
	0xff, /* 0x58 : not user-modifiable */
	0x01, /* 0x59 : not user-modifiable */
	0x00, /* 0x5a : not user-modifiable */
	0x08, /* 0x5b : not user-modifiable */
	0x00, /* 0x5c : not user-modifiable */
	0x00, /* 0x5d : not user-modifiable */
	0x01, /* 0x5e : not user-modifiable */
	0xdb, /* 0x5f : not user-modifiable */
	0x0f, /* 0x60 : not user-modifiable */
	0x01, /* 0x61 : not user-modifiable */
	0xf1, /* 0x62 : not user-modifiable */
	0x0d, /* 0x63 : not user-modifiable */
	0x01, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), use SetSigmaThreshold(), default value 90 mm  */
	0x68, /* 0x65 : Sigma threshold LSB */
	0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB), use SetSignalThreshold() */
	0x80, /* 0x67 : Min count Rate LSB */
	0x08, /* 0x68 : not user-modifiable */
	0xb8, /* 0x69 : not user-modifiable */
	0x00, /* 0x6a : not user-modifiable */
	0x00, /* 0x6b : not user-modifiable */
	0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register, use SetIntermeasurementInMs() */
	0x00, /* 0x6d : Intermeasurement period */
	0x0f, /* 0x6e : Intermeasurement period */
	0x89, /* 0x6f : Intermeasurement period LSB */
	0x00, /* 0x70 : not user-modifiable */
	0x00, /* 0x71 : not user-modifiable */
	0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB), use SetD:tanceThreshold() */
	0x00, /* 0x73 : distance threshold high LSB */
	0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB), use SetD:tanceThreshold() */
	0x00, /* 0x75 : distance threshold low LSB */
	0x00, /* 0x76 : not user-modifiable */
	0x01, /* 0x77 : not user-modifiable */
	0x0f, /* 0x78 : not user-modifiable */
	0x0d, /* 0x79 : not user-modifiable */
	0x0e, /* 0x7a : not user-modifiable */
	0x0e, /* 0x7b : not user-modifiable */
	0x00, /* 0x7c : not user-modifiable */
	0x00, /* 0x7d : not user-modifiable */
	0x02, /* 0x7e : not user-modifiable */
	0xc7, /* 0x7f : ROI center, use SetROI() */
	0xff, /* 0x80 : XY ROI (X=Width, Y=Height), use SetROI() */
	0x9B, /* 0x81 : not user-modifiable */
	0x00, /* 0x82 : not user-modifiable */
	0x00, /* 0x83 : not user-modifiable */
	0x00, /* 0x84 : not user-modifiable */
	0x01, /* 0x85 : not user-modifiable */
	0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
	0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(), If you want an automatic start after VL53L1X_init() call, put 0x40 in location 0x87 */
};

/* Adaptation: bounded initialization and immediate IO-error propagation. */
VL53L1X_ERROR VL53L1X_SensorInit(uint16_t dev)
{
    for (uint16_t reg=0x2D; reg<=0x87; ++reg) {
        VL53L1X_ERROR status=VL53L1_WrByte(dev, reg, VL51L1X_DEFAULT_CONFIGURATION[reg-0x2D]);
        if (status) return status;
    }
    VL53L1X_ERROR status=VL53L1X_StartRanging(dev);
    if (status) return status;
    uint32_t started=VL53L1_PlatformTick();
    uint8_t ready=0;
    while (!ready) {
        status=VL53L1X_CheckForDataReady(dev, &ready);
        if (status) return status;
        if ((uint32_t)(VL53L1_PlatformTick()-started)>=500U) return -2;
        VL53L1_PlatformDelay(2);
    }
    if ((status=VL53L1X_ClearInterrupt(dev))) return status;
    if ((status=VL53L1X_StopRanging(dev))) return status;
    if ((status=VL53L1_WrByte(dev, VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND, 0x09))) return status;
    return VL53L1_WrByte(dev, 0x0B, 0);
}
VL53L1X_ERROR VL53L1X_ClearInterrupt(uint16_t dev)
{
	VL53L1X_ERROR status = 0;

	status = VL53L1_WrByte(dev, SYSTEM__INTERRUPT_CLEAR, 0x01);
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetInterruptPolarity(uint16_t dev, uint8_t *pInterruptPolarity)
{
	uint8_t Temp;
	VL53L1X_ERROR status = 0;

	status = VL53L1_RdByte(dev, GPIO_HV_MUX__CTRL, &Temp);
	Temp = Temp & 0x10;
	*pInterruptPolarity = !(Temp >> 4);
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_StartRanging(uint16_t dev)
{
	VL53L1X_ERROR status = 0;
	VL53L1_WrByte(dev, SYSTEM__INTERRUPT_CLEAR, 0x01); /* clear interrupt trigger */
	status = VL53L1_WrByte(dev, SYSTEM__MODE_START, 0x40); /* Enable VL53L1X */
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_StopRanging(uint16_t dev)
{
	VL53L1X_ERROR status = 0;

	status = VL53L1_WrByte(dev, SYSTEM__MODE_START, 0x00); /* Disable VL53L1X */
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_CheckForDataReady(uint16_t dev, uint8_t *isDataReady)
{
	uint8_t Temp;
	uint8_t IntPol;
	VL53L1X_ERROR status = 0;

	status = VL53L1X_GetInterruptPolarity(dev, &IntPol);
	status = VL53L1_RdByte(dev, GPIO__TIO_HV_STATUS, &Temp);
	/* Read in the register to check if a new value is available */
	if (status == 0)
	{
		if ((Temp & 1) == IntPol)
			*isDataReady = 1;
		else
			*isDataReady = 0;
	}
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_SetTimingBudgetInMs(uint16_t dev, uint16_t TimingBudgetInMs)
{
	uint16_t DM = 0;
	VL53L1X_ERROR status = 0;

	status = VL53L1X_GetDistanceMode(dev, &DM);
	if (DM == 0)
		return 1;
	else if (DM == 1)
	{ /* Short DistanceMode */
		switch (TimingBudgetInMs)
		{
		case 15: /* only available in short distance mode */
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x01D);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x0027);
			break;
		case 20:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x0051);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x006E);
			break;
		case 33:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x00D6);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x006E);
			break;
		case 50:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x1AE);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x01E8);
			break;
		case 100:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x02E1);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x0388);
			break;
		case 200:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x03E1);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x0496);
			break;
		case 500:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x0591);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x05C1);
			break;
		default:
			status = 1;
			break;
		}
	}
	else
	{
		switch (TimingBudgetInMs)
		{
		case 20:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x001E);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x0022);
			break;
		case 33:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x0060);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x006E);
			break;
		case 50:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x00AD);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x00C6);
			break;
		case 100:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x01CC);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x01EA);
			break;
		case 200:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x02D9);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x02F8);
			break;
		case 500:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI,
						  0x048F);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
						  0x04A4);
			break;
		default:
			status = 1;
			break;
		}
	}
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetTimingBudgetInMs(uint16_t dev, uint16_t *pTimingBudget)
{
	uint16_t Temp;
	VL53L1X_ERROR status = 0;

	status = VL53L1_RdWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, &Temp);
	switch (Temp)
	{
	case 0x001D:
		*pTimingBudget = 15;
		break;
	case 0x0051:
	case 0x001E:
		*pTimingBudget = 20;
		break;
	case 0x00D6:
	case 0x0060:
		*pTimingBudget = 33;
		break;
	case 0x1AE:
	case 0x00AD:
		*pTimingBudget = 50;
		break;
	case 0x02E1:
	case 0x01CC:
		*pTimingBudget = 100;
		break;
	case 0x03E1:
	case 0x02D9:
		*pTimingBudget = 200;
		break;
	case 0x0591:
	case 0x048F:
		*pTimingBudget = 500;
		break;
	default:
		*pTimingBudget = 0;
		break;
	}
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_SetDistanceMode(uint16_t dev, uint16_t DM)
{
	uint16_t TB = 0;
	VL53L1X_ERROR status = 0;

	status = VL53L1X_GetTimingBudgetInMs(dev, &TB);
	switch (DM)
	{
	case 1:
		status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x07);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x05);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0x38);
		status = VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0705);
		status = VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0606);
		break;
	case 2:
		status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8);
		status = VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0F0D);
		status = VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E);
		break;
	default:
		break;
	}
	status = VL53L1X_SetTimingBudgetInMs(dev, TB);
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetDistanceMode(uint16_t dev, uint16_t *DM)
{
	uint8_t TempDM, status = 0;

	status = VL53L1_RdByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, &TempDM);
	if (TempDM == 0x14)
		*DM = 1;
	if (TempDM == 0x0A)
		*DM = 2;
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_SetInterMeasurementInMs(uint16_t dev, uint16_t InterMeasMs)
{
	uint16_t ClockPLL;
	VL53L1X_ERROR status = 0;

	status = VL53L1_RdWord(dev, VL53L1_RESULT__OSC_CALIBRATE_VAL, &ClockPLL);
	ClockPLL = ClockPLL & 0x3FF;
	VL53L1_WrDWord(dev, VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD,
				   (uint32_t)(ClockPLL * InterMeasMs * 1.075));
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_BootState(uint16_t dev, uint8_t *state)
{
	VL53L1X_ERROR status = 0;
	uint8_t tmp = 0;

	status = VL53L1_RdByte(dev, VL53L1_FIRMWARE__SYSTEM_STATUS, &tmp);
	*state = tmp;
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetSensorId(uint16_t dev, uint16_t *sensorId)
{
	VL53L1X_ERROR status = 0;
	uint16_t tmp = 0;

	status = VL53L1_RdWord(dev, VL53L1_IDENTIFICATION__MODEL_ID, &tmp);
	*sensorId = tmp;
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetDistance(uint16_t dev, uint16_t *distance)
{
	VL53L1X_ERROR status = 0;
	uint16_t tmp;

	status = (VL53L1_RdWord(dev,
							VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0, &tmp));
	*distance = tmp;
	return status ? status : VL53L1_PlatformError();
}

VL53L1X_ERROR VL53L1X_GetRangeStatus(uint16_t dev, uint8_t *rangeStatus)
{
	VL53L1X_ERROR status = 0;
	uint8_t RgSt;

	status = VL53L1_RdByte(dev, VL53L1_RESULT__RANGE_STATUS, &RgSt);
	RgSt = RgSt & 0x1F;
	switch (RgSt)
	{
	case 9:
		RgSt = 0;
		break;
	case 6:
		RgSt = 1;
		break;
	case 4:
		RgSt = 2;
		break;
	case 8:
		RgSt = 3;
		break;
	case 5:
		RgSt = 4;
		break;
	case 3:
		RgSt = 5;
		break;
	case 19:
		RgSt = 6;
		break;
	case 7:
		RgSt = 7;
		break;
	case 12:
		RgSt = 9;
		break;
	case 18:
		RgSt = 10;
		break;
	case 22:
		RgSt = 11;
		break;
	case 23:
		RgSt = 12;
		break;
	case 13:
		RgSt = 13;
		break;
	default:
		RgSt = 255;
		break;
	}
	*rangeStatus = RgSt;
	return status ? status : VL53L1_PlatformError();
}
