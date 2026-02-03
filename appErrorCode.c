/* -----------------------------------------------------------------------------
 * @file appErrorCode.c
 * @brief 统一错误码实现
 *
 * @author: Lion Cao
 * @date: 2026-01-16
 * ---------------------------------------------------------------------------*/

#include "appErrorCode.h"
#include <stdbool.h>
#include <stdio.h>


/* 错误描述字符串表 */
typedef struct
{
    app_err_t code;
    const char *name;
    const char *description;
} app_err_entry_t;

/* 可恢复错误列表（超时、忙碌等暂时性错误） */
static const app_err_t s_recoverableErrors[] = {
    APP_ERR_TIMEOUT,
    APP_ERR_BUSY,
    APP_ERR_COMM_TX_BUSY,
    APP_ERR_COMM_QUEUE_FULL,
    APP_ERR_UART_TX_BUSY,
    APP_ERR_UART_TX_TIMEOUT,
    APP_ERR_PROTO_FRAME_TIMEOUT,
};

static const uint32_t s_recoverableErrorCount = sizeof(s_recoverableErrors) / sizeof(s_recoverableErrors[0]);

/* 错误码表 */
static const app_err_entry_t s_errorTable[] = {
    /* 通用错误 */
    {APP_ERR_OK, "APP_ERR_OK", "Success"},
    {APP_ERR_NULL_PTR, "APP_ERR_NULL_PTR", "Null pointer"},
    {APP_ERR_INVALID_PARAM, "APP_ERR_INVALID_PARAM", "Invalid parameter"},
    {APP_ERR_NOT_INIT, "APP_ERR_NOT_INIT", "Not initialized"},
    {APP_ERR_ALREADY_INIT, "APP_ERR_ALREADY_INIT", "Already initialized"},
    {APP_ERR_NOT_SUPPORTED, "APP_ERR_NOT_SUPPORTED", "Not supported"},
    {APP_ERR_NO_MEMORY, "APP_ERR_NO_MEMORY", "Out of memory"},
    {APP_ERR_TIMEOUT, "APP_ERR_TIMEOUT", "Timeout"},
    {APP_ERR_BUSY, "APP_ERR_BUSY", "Resource busy"},
    {APP_ERR_FAIL, "APP_ERR_FAIL", "Generic failure"},
    {APP_ERR_UNKNOWN, "APP_ERR_UNKNOWN", "Unknown error"},

    /* 通信模块错误 */
    {APP_ERR_COMM_NOT_INIT, "APP_ERR_COMM_NOT_INIT", "Communication not initialized"},
    {APP_ERR_COMM_TX_BUSY, "APP_ERR_COMM_TX_BUSY", "Communication transmit busy"},
    {APP_ERR_COMM_QUEUE_FULL, "APP_ERR_COMM_QUEUE_FULL", "Communication queue full"},
    {APP_ERR_COMM_PAYLOAD_TOO_LARGE, "APP_ERR_COMM_PAYLOAD_TOO_LARGE", "Payload too large"},
    {APP_ERR_COMM_INVALID_UART, "APP_ERR_COMM_INVALID_UART", "Invalid UART channel"},
    {APP_ERR_COMM_SEND_FAIL, "APP_ERR_COMM_SEND_FAIL", "Communication send failed"},

    /* 协议模块错误 */
    {APP_ERR_PROTO_FRAME_TIMEOUT, "APP_ERR_PROTO_FRAME_TIMEOUT", "Protocol frame timeout"},
    {APP_ERR_PROTO_CRC_ERROR, "APP_ERR_PROTO_CRC_ERROR", "Protocol CRC error"},
    {APP_ERR_PROTO_INVALID_STATE, "APP_ERR_PROTO_INVALID_STATE", "Protocol invalid state"},
    {APP_ERR_PROTO_BUFFER_OVERFLOW, "APP_ERR_PROTO_BUFFER_OVERFLOW", "Protocol buffer overflow"},
    {APP_ERR_PROTO_INVALID_FRAME, "APP_ERR_PROTO_INVALID_FRAME", "Protocol invalid frame"},
    {APP_ERR_PROTO_INCOMPLETE_FRAME, "APP_ERR_PROTO_INCOMPLETE_FRAME", "Protocol incomplete frame"},
    {APP_ERR_PROTO_ESCAPE_ERROR, "APP_ERR_PROTO_ESCAPE_ERROR", "Protocol escape error"},

    /* 串口模块错误 */
    {APP_ERR_UART_NOT_INIT, "APP_ERR_UART_NOT_INIT", "UART not initialized"},
    {APP_ERR_UART_TX_BUSY, "APP_ERR_UART_TX_BUSY", "UART transmit busy"},
    {APP_ERR_UART_TX_TIMEOUT, "APP_ERR_UART_TX_TIMEOUT", "UART transmit timeout"},
    {APP_ERR_UART_RX_ERROR, "APP_ERR_UART_RX_ERROR", "UART receive error"},
    {APP_ERR_UART_DMA_ERROR, "APP_ERR_UART_DMA_ERROR", "UART DMA error"},
    {APP_ERR_UART_INVALID_CH, "APP_ERR_UART_INVALID_CH", "UART invalid channel"},
    {APP_ERR_UART_BUFFER_FULL, "APP_ERR_UART_BUFFER_FULL", "UART buffer full"},

    /* 传感器模块错误 */
    {APP_ERR_SENSOR_NOT_RESPONDING, "APP_ERR_SENSOR_NOT_RESPONDING", "Sensor not responding"},
    {APP_ERR_SENSOR_INVALID_DATA, "APP_ERR_SENSOR_INVALID_DATA", "Sensor invalid data"},
    {APP_ERR_SENSOR_CHECKSUM, "APP_ERR_SENSOR_CHECKSUM", "Sensor checksum error"},
    {APP_ERR_SENSOR_NOT_FOUND, "APP_ERR_SENSOR_NOT_FOUND", "Sensor not found"},
};

static const uint32_t s_errorTableSize = sizeof(s_errorTable) / sizeof(s_errorTable[0]);

/**
 * @brief   获取错误码的字符串描述
 * @param   errCode 错误码
 * @retval  错误描述字符串
 */
const char *app_Err_ToString(app_err_t errCode)
{
    for (uint32_t i = 0; i < s_errorTableSize; i++)
    {
        if (s_errorTable[i].code == errCode)
        {
            return s_errorTable[i].name;
        }
    }
    static char unknownStr[32];
    snprintf(unknownStr, sizeof(unknownStr), "UNKNOWN_ERROR_0x%08lX", (unsigned long)errCode);
    return unknownStr;
}

/**
 * @brief   获取错误的详细描述
 * @param   errCode 错误码
 * @retval  错误详细描述字符串
 */
const char *app_Err_GetDescription(app_err_t errCode)
{
    for (uint32_t i = 0; i < s_errorTableSize; i++)
    {
        if (s_errorTable[i].code == errCode)
        {
            return s_errorTable[i].description;
        }
    }
    return "Unknown error code";
}

/**
 * @brief   判断错误码是否属于指定模块
 * @param   errCode    错误码
 * @param   module     模块标识
 * @retval  true       属于该模块
 * @retval  false      不属于该模块
 */
bool app_Err_IsModule(app_err_t errCode, uint32_t module)
{
    return ((errCode & APP_ERR_MODULE_MASK) == module);
}

/**
 * @brief   判断错误码是否属于指定类别
 * @param   errCode    错误码
 * @param   category   类别标识
 * @retval  true       属于该类别
 * @retval  false      不属于该类别
 */
bool app_Err_IsCategory(app_err_t errCode, uint32_t category)
{
    return ((errCode & APP_ERR_CATEGORY_MASK) == category);
}

/**
 * @brief   判断错误是否可恢复
 * @param   errCode    错误码
 * @retval  true       可恢复
 * @retval  false      不可恢复
 */
bool app_Err_IsRecoverable(app_err_t errCode)
{
    for (uint32_t i = 0; i < s_recoverableErrorCount; i++)
    {
        if (s_recoverableErrors[i] == errCode)
        {
            return true;
        }
    }
    return false;
}
