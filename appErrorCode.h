/* -----------------------------------------------------------------------------
 * @file appErrorCode.h
 * @brief 统一错误码定义
 *
 * 错误码设计原则：
 * 1. 采用分层设计：模块(8bit) | 类别(4bit) | 具体错误(12bit)
 * 2. 0 表示成功，非0表示错误
 * 3. 错误码具有唯一性和可扩展性
 *
 * 错误码格式: 0xMCCCEEEE
 *   M - Module (模块): 0x00-0xFF
 *   CC - Category (类别): 0x00-0x0F
 *   EEEE - Error (具体错误): 0x000-0xFFF
 *
 * ----------------------------------------------------------------------------*/

#ifndef APP_ERROR_CODE_H
#define APP_ERROR_CODE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* ======================================================================== */
    /*                                模块定义                                 */
    /* ======================================================================== */

#define APP_ERR_MODULE_BASE 0x00000000U
#define APP_ERR_MODULE_MASK 0xFF000000U

/* 模块分配 (高8位) */
#define APP_ERR_MODULE_SYSTEM   0x00000000U /* 系统通用 */
#define APP_ERR_MODULE_COMM     0x01000000U /* 通信模块 */
#define APP_ERR_MODULE_PROTOCOL 0x02000000U /* 协议处理 */
#define APP_ERR_MODULE_UART     0x03000000U /* 串口驱动 */
#define APP_ERR_MODULE_TIMER    0x04000000U /* 定时器 */
#define APP_ERR_MODULE_IO       0x05000000U /* IO控制 */
#define APP_ERR_MODULE_MEMORY   0x06000000U /* 内存管理 */
#define APP_ERR_MODULE_TASK     0x07000000U /* 任务调度 */
#define APP_ERR_MODULE_SENSOR   0x08000000U /* 传感器模块 */
#define APP_ERR_MODULE_USER     0xFF0000FFU /* 用户自定义 */

    /* ======================================================================== */
    /*                                类别定义                                   */
    /* ======================================================================== */

#define APP_ERR_CATEGORY_BASE 0x00000000U
#define APP_ERR_CATEGORY_MASK 0x00F00000U

/* 错误类别 (次4位) */
#define APP_ERR_CATEGORY_SUCCESS  0x00000000U /* 成功 */
#define APP_ERR_CATEGORY_PARAM    0x00100000U /* 参数错误 */
#define APP_ERR_CATEGORY_STATE    0x00200000U /* 状态错误 */
#define APP_ERR_CATEGORY_TIMEOUT  0x00300000U /* 超时错误 */
#define APP_ERR_CATEGORY_BUSY     0x00400000U /* 忙碌/资源占用 */
#define APP_ERR_CATEGORY_NOMEM    0x00500000U /* 内存不足 */
#define APP_ERR_CATEGORY_IO       0x00600000U /* IO错误 */
#define APP_ERR_CATEGORY_CHECKSUM 0x00700000U /* 校验错误 */
#define APP_ERR_CATEGORY_PROTOCOL 0x00800000U /* 协议错误 */
#define APP_ERR_CATEGORY_HARDWARE 0x00900000U /* 硬件错误 */
#define APP_ERR_CATEGORY_INTERNAL 0x00A00000U /* 内部错误 */

    /* ======================================================================== */
    /*                              通用错误码                                 */
    /* ======================================================================== */

/* 成功 */
#define APP_ERR_OK 0x00000000U

/* 系统通用错误 */
#define APP_ERR_NULL_PTR      (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_PARAM | 0x001)    /* 空指针 */
#define APP_ERR_INVALID_PARAM (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_PARAM | 0x002)    /* 无效参数 */
#define APP_ERR_NOT_INIT      (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_STATE | 0x001)    /* 未初始化 */
#define APP_ERR_ALREADY_INIT  (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_STATE | 0x002)    /* 重复初始化 */
#define APP_ERR_NOT_SUPPORTED (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_PARAM | 0x003)    /* 不支持的功能 */
#define APP_ERR_NO_MEMORY     (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_NOMEM | 0x001)    /* 内存不足 */
#define APP_ERR_TIMEOUT       (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_TIMEOUT | 0x001)  /* 超时 */
#define APP_ERR_BUSY          (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_BUSY | 0x001)     /* 忙碌 */
#define APP_ERR_FAIL          (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_INTERNAL | 0x001) /* 通用失败 */
#define APP_ERR_UNKNOWN       (APP_ERR_MODULE_SYSTEM | APP_ERR_CATEGORY_INTERNAL | 0x002) /* 未知错误 */

    /* ======================================================================== */
    /*                              通信模块错误                               */
    /* ======================================================================== */

#define APP_ERR_COMM_NOT_INIT          (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_STATE | 0x001) /* 通信未初始化 */
#define APP_ERR_COMM_TX_BUSY           (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_BUSY | 0x001)  /* 发送忙碌 */
#define APP_ERR_COMM_QUEUE_FULL        (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_NOMEM | 0x001) /* 发送队列满 */
#define APP_ERR_COMM_PAYLOAD_TOO_LARGE (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_PARAM | 0x001) /* 负载过大 */
#define APP_ERR_COMM_INVALID_UART      (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_PARAM | 0x002) /* 无效串口号 */
#define APP_ERR_COMM_SEND_FAIL         (APP_ERR_MODULE_COMM | APP_ERR_CATEGORY_IO | 0x001)    /* 发送失败 */

    /* ======================================================================== */
    /*                              协议模块错误                               */
    /* ======================================================================== */

#define APP_ERR_PROTO_FRAME_TIMEOUT    (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_TIMEOUT | 0x001)  /* 帧超时 */
#define APP_ERR_PROTO_CRC_ERROR        (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_CHECKSUM | 0x001) /* CRC错误 */
#define APP_ERR_PROTO_INVALID_STATE    (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_STATE | 0x001)    /* 无效状态 */
#define APP_ERR_PROTO_BUFFER_OVERFLOW  (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_NOMEM | 0x001)    /* 缓冲区溢出 */
#define APP_ERR_PROTO_INVALID_FRAME    (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_PROTOCOL | 0x001) /* 无效帧格式 */
#define APP_ERR_PROTO_INCOMPLETE_FRAME (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_PROTOCOL | 0x002) /* 不完整帧 */
#define APP_ERR_PROTO_ESCAPE_ERROR     (APP_ERR_MODULE_PROTOCOL | APP_ERR_CATEGORY_PROTOCOL | 0x003) /* 转义错误 */

    /* ======================================================================== */
    /*                              串口模块错误                               */
    /* ======================================================================== */

#define APP_ERR_UART_NOT_INIT    (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_STATE | 0x001)    /* 串口未初始化 */
#define APP_ERR_UART_TX_BUSY     (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_BUSY | 0x001)     /* 发送忙碌 */
#define APP_ERR_UART_TX_TIMEOUT  (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_TIMEOUT | 0x001)  /* 发送超时 */
#define APP_ERR_UART_RX_ERROR    (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_IO | 0x001)       /* 接收错误 */
#define APP_ERR_UART_DMA_ERROR   (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_HARDWARE | 0x001) /* DMA错误 */
#define APP_ERR_UART_INVALID_CH  (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_PARAM | 0x001)    /* 无效通道 */
#define APP_ERR_UART_BUFFER_FULL (APP_ERR_MODULE_UART | APP_ERR_CATEGORY_NOMEM | 0x001)    /* 缓冲区满 */

    /* ======================================================================== */
    /*                              传感器模块错误                             */
    /* ======================================================================== */

#define APP_ERR_SENSOR_NOT_RESPONDING (APP_ERR_MODULE_SENSOR | APP_ERR_CATEGORY_TIMEOUT | 0x001)  /* 传感器无响应 */
#define APP_ERR_SENSOR_INVALID_DATA   (APP_ERR_MODULE_SENSOR | APP_ERR_CATEGORY_PROTOCOL | 0x001) /* 无效数据 */
#define APP_ERR_SENSOR_CHECKSUM       (APP_ERR_MODULE_SENSOR | APP_ERR_CATEGORY_CHECKSUM | 0x001) /* 校验失败 */
#define APP_ERR_SENSOR_NOT_FOUND      (APP_ERR_MODULE_SENSOR | APP_ERR_CATEGORY_STATE | 0x001)    /* 传感器未找到 */

    /* ======================================================================== */
    /*                            错误码类型定义                                */
    /* ======================================================================== */

    typedef uint32_t app_err_t;

    /* ======================================================================== */
    /*                              错误码宏                                    */
    /* ======================================================================== */

#define APP_ERR_SUCCESS(code) ((code) == APP_ERR_OK)
#define APP_ERR_FAILED(code)  ((code) != APP_ERR_OK)

#define APP_ERR_GET_MODULE(code)   (((code) & APP_ERR_MODULE_MASK) >> 24)
#define APP_ERR_GET_CATEGORY(code) (((code) & APP_ERR_CATEGORY_MASK) >> 20)

    /* ======================================================================== */
    /*                            API 函数声明                                  */
    /* ======================================================================== */

    /**
     * @brief   获取错误码的字符串描述
     * @param   errCode 错误码
     * @retval  错误描述字符串
     */
    const char *app_Err_ToString(app_err_t errCode);

    /**
     * @brief   获取错误的详细描述
     * @param   errCode 错误码
     * @retval  错误详细描述字符串
     */
    const char *app_Err_GetDescription(app_err_t errCode);

    /**
     * @brief   判断错误码是否属于指定模块
     * @param   errCode    错误码
     * @param   module     模块标识
     * @retval  true       属于该模块
     * @retval  false      不属于该模块
     */
    bool app_Err_IsModule(app_err_t errCode, uint32_t module);

    /**
     * @brief   判断错误码是否属于指定类别
     * @param   errCode    错误码
     * @param   category   类别标识
     * @retval  true       属于该类别
     * @retval  false      不属于该类别
     */
    bool app_Err_IsCategory(app_err_t errCode, uint32_t category);

    /**
     * @brief   判断错误是否可恢复
     * @param   errCode    错误码
     * @retval  true       可恢复
     * @retval  false      不可恢复
     */
    bool app_Err_IsRecoverable(app_err_t errCode);

#ifdef __cplusplus
}
#endif

#endif /* APP_ERROR_CODE_H */
