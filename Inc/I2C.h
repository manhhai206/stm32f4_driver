#ifndef DRIVERS_INC_I2C_H_
#define DRIVERS_INC_I2C_H_

#include "stm32f4.h"

//I2C_CR1
#define I2C_CR1_PE 		0
#define I2C_CR1_NOSTRETCH	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_ACK			10
#define I2C_CR1_SWRST		15


//I2C_CR2
#define I2C_CR2_FREQ		0
#define I2C_CR2_ITERREN		8
#define I2C_CR2_ITEVTEN		9
#define I2C_CR2_ITBUFEN		10

//I2C_OAR1
#define I2C_OAR1_ADD0		0
#define I2C_OAR1_ADD71		1
#define I2C_OAR1_ADD98		8
#define I2C_OAR1_ADDMODE	15

//I2C_SR1
#define I2C_SR1_SB			0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF			2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE			7
#define I2C_SR1_BERR		8
#define I2C_SR1_ARLO		9
#define I2C_SR1_AF			10
#define I2C_SR1_OVR			11
#define I2C_SR1_TIMEOUT		14

//I2C_SR2
#define I2C_SR2_MSL			0
#define I2C_SR2_BUSY		1
#define I2C_SR2_TRA			2
#define I2C_SR2_GENCALL		4
#define I2C_SR2_DUALF		7

//I2C_CCR
#define I2C_CCR_CRR 		0
#define I2C_CCR_DUTY		14
#define	I2C_CCR_FS			15

typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t	I2C_DeviceAddress;
	uint8_t I2C_AckControl;
	uint8_t I2C_FMDutyCycle;
}I2C_Config_t;

typedef struct
{
	I2C_TypeDef  	*pI2Cx;
	I2C_Config_t 	I2C_Config;
	uint8_t 		*pTxBuffer;
	uint8_t 		*pRxBuffer;
	uint32_t 		TxLen;
	uint32_t 		RxLen;
	uint8_t  		RxTxState;
	uint8_t			DevAddr;	//slave/device address
	uint32_t 		RxSize;
	uint8_t 		Sr;  //repeated start value
}I2C_Handle_t;

#define I2C_READY		0
#define I2C_BUSY_IN_RX	1
#define I2C_BUSY_IN_TX	2

//I2C_SCLSpeed
#define I2C_SCL_SPEED_SM	100000
#define I2C_SCL_SPEED_FM4K	400000

//I2C_AckControl
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE		0

//I2C_FMDutyCycle
#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1

//flag
#define I2C_FLAG_SB			(1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR		(1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF		(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADD10		(1 << I2C_SR1_ADD10)
#define I2C_FLAG_STOPF		(1 << I2C_SR1_STOPF)
#define I2C_FLAG_RXNE		(1 << I2C_SR1_RXNE)
#define I2C_FLAG_TXE		(1 << I2C_SR1_TXE)
#define I2C_FLAG_BERR		(1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO		(1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF			(1 << I2C_SR1_AF)
#define I2C_FLAG_OVR		(1 << I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT	(1 << I2C_SR1_TIMEOUT)

#define I2C_DISABLE_SR		RESET
#define I2C_ENABLE_SR		SET

//application events
#define I2C_EV_TX_CMPLT		0
#define I2C_EV_RX_CMPLT		1
#define I2C_EV_STOP			2
#define I2C_ERROR_BERR		3
#define I2C_ERROR_ARLO		4
#define I2C_ERROR_AF		5
#define I2C_ERROR_OVR		6
#define I2C_ERROR_TIMEOUT	7
#define I2C_EV_DATA_REQ		8
#define I2C_EV_DATA_RCV		9

void I2C_PeriClockControl(I2C_TypeDef *pI2Cx, uint8_t EnorDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_TypeDef *pI2Cx);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_SlaveSendData(I2C_TypeDef *pI2Cx, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_TypeDef *pI2Cx);

void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

uint8_t I2C_GetFlagStatus(I2C_TypeDef *pI2Cx, uint32_t StatusFlagName);
void I2C_PeripheralControl(I2C_TypeDef *pI2Cx, uint8_t EnorDi);
void I2C_ManageAcking(I2C_TypeDef *pI2Cx,uint8_t EnorDi);
void I2C_GenerateStopCondition(I2C_TypeDef *pI2Cx);

void I2C_SlaveEnableDisableCallbackEvents(I2C_TypeDef *pI2Cx,uint8_t EnorDi);

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv);

#endif /* DRIVERS_INC_I2C_H_ */
