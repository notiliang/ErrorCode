# ErrorCode

统一嵌入式程序设计中的返回值错误码定义库。

## 概述

本库提供了一套结构化的错误码定义系统，用于统一嵌入式 C 项目中的函数返回值处理。通过分层设计，使错误码具有清晰的模块归属和错误类别，便于问题定位和调试。

## 错误码设计

### 设计原则

1. **分层设计**：采用 `模块(8bit) | 类别(4bit) | 具体错误(12bit)` 的三层结构
2. **零值成功**：`0` 表示成功，非零表示错误
3. **唯一性**：每个错误码在全局范围内唯一
4. **可扩展性**：预留充足的模块和错误编码空间

### 错误码格式

```
0xMCCCEEEE
│ │   │
│ │   └─ EEEE: 具体错误码 (12 bit, 0x000-0xFFF)
│ └───── CC:   错误类别   (4 bit, 0x0-0xF)
└─────── M:    模块标识   (8 bit, 0x00-0xFF)
```

### 模块定义 (Module)

| 模块标识 | 值 | 说明 |
|---------|-----|------|
| `APP_ERR_MODULE_SYSTEM`   | 0x00 | 系统通用 |
| `APP_ERR_MODULE_COMM`     | 0x01 | 通信模块 |
| `APP_ERR_MODULE_PROTOCOL` | 0x02 | 协议处理 |
| `APP_ERR_MODULE_UART`     | 0x03 | 串口驱动 |
| `APP_ERR_MODULE_TIMER`    | 0x04 | 定时器 |
| `APP_ERR_MODULE_IO`       | 0x05 | IO控制 |
| `APP_ERR_MODULE_MEMORY`   | 0x06 | 内存管理 |
| `APP_ERR_MODULE_TASK`     | 0x07 | 任务调度 |
| `APP_ERR_MODULE_SENSOR`   | 0x08 | 传感器模块 |
| `APP_ERR_MODULE_USER`     | 0xFF | 用户自定义 |

### 类别定义 (Category)

| 类别标识 | 值 | 说明 |
|---------|-----|------|
| `APP_ERR_CATEGORY_SUCCESS`  | 0x0 | 成功 |
| `APP_ERR_CATEGORY_PARAM`    | 0x1 | 参数错误 |
| `APP_ERR_CATEGORY_STATE`    | 0x2 | 状态错误 |
| `APP_ERR_CATEGORY_TIMEOUT`  | 0x3 | 超时错误 |
| `APP_ERR_CATEGORY_BUSY`     | 0x4 | 忙碌/资源占用 |
| `APP_ERR_CATEGORY_NOMEM`    | 0x5 | 内存不足 |
| `APP_ERR_CATEGORY_IO`       | 0x6 | IO错误 |
| `APP_ERR_CATEGORY_CHECKSUM` | 0x7 | 校验错误 |
| `APP_ERR_CATEGORY_PROTOCOL` | 0x8 | 协议错误 |
| `APP_ERR_CATEGORY_HARDWARE` | 0x9 | 硬件错误 |
| `APP_ERR_CATEGORY_INTERNAL` | 0xA | 内部错误 |

## API 接口

### 类型定义

```c
typedef uint32_t app_err_t;
```

### 判断宏

| 宏 | 说明 |
|---|---|
| `APP_ERR_SUCCESS(code)` | 判断是否成功 |
| `APP_ERR_FAILED(code)` | 判断是否失败 |
| `APP_ERR_GET_MODULE(code)` | 提取模块标识 |
| `APP_ERR_GET_CATEGORY(code)` | 提取类别标识 |

### 函数接口

| 函数 | 说明 |
|------|------|
| `app_Err_ToString(errCode)` | 获取错误码名称字符串 |
| `app_Err_GetDescription(errCode)` | 获取错误详细描述 |
| `app_Err_IsModule(errCode, module)` | 判断是否属于指定模块 |
| `app_Err_IsCategory(errCode, category)` | 判断是否属于指定类别 |
| `app_Err_IsRecoverable(errCode)` | 判断错误是否可恢复 |

## 常用错误码

### 系统通用错误

| 错误码 | 值 | 说明 |
|-------|-----|------|
| `APP_ERR_OK` | 0x00000000 | 成功 |
| `APP_ERR_NULL_PTR` | 0x00100101 | 空指针 |
| `APP_ERR_INVALID_PARAM` | 0x00100102 | 无效参数 |
| `APP_ERR_NOT_INIT` | 0x00200101 | 未初始化 |
| `APP_ERR_ALREADY_INIT` | 0x00200102 | 重复初始化 |
| `APP_ERR_NOT_SUPPORTED` | 0x00100103 | 不支持的功能 |
| `APP_ERR_NO_MEMORY` | 0x00500101 | 内存不足 |
| `APP_ERR_TIMEOUT` | 0x00300101 | 超时 |
| `APP_ERR_BUSY` | 0x00400101 | 忙碌 |
| `APP_ERR_FAIL` | 0x00A00101 | 通用失败 |
| `APP_ERR_UNKNOWN` | 0x00A00102 | 未知错误 |

### 通信模块错误

| 错误码 | 说明 |
|-------|------|
| `APP_ERR_COMM_NOT_INIT` | 通信未初始化 |
| `APP_ERR_COMM_TX_BUSY` | 发送忙碌 |
| `APP_ERR_COMM_QUEUE_FULL` | 发送队列满 |
| `APP_ERR_COMM_PAYLOAD_TOO_LARGE` | 负载过大 |
| `APP_ERR_COMM_INVALID_UART` | 无效串口号 |
| `APP_ERR_COMM_SEND_FAIL` | 发送失败 |

### 协议模块错误

| 错误码 | 说明 |
|-------|------|
| `APP_ERR_PROTO_FRAME_TIMEOUT` | 帧超时 |
| `APP_ERR_PROTO_CRC_ERROR` | CRC错误 |
| `APP_ERR_PROTO_INVALID_STATE` | 无效状态 |
| `APP_ERR_PROTO_BUFFER_OVERFLOW` | 缓冲区溢出 |
| `APP_ERR_PROTO_INVALID_FRAME` | 无效帧格式 |
| `APP_ERR_PROTO_INCOMPLETE_FRAME` | 不完整帧 |
| `APP_ERR_PROTO_ESCAPE_ERROR` | 转义错误 |

### 串口模块错误

| 错误码 | 说明 |
|-------|------|
| `APP_ERR_UART_NOT_INIT` | 串口未初始化 |
| `APP_ERR_UART_TX_BUSY` | 发送忙碌 |
| `APP_ERR_UART_TX_TIMEOUT` | 发送超时 |
| `APP_ERR_UART_RX_ERROR` | 接收错误 |
| `APP_ERR_UART_DMA_ERROR` | DMA错误 |
| `APP_ERR_UART_INVALID_CH` | 无效通道 |
| `APP_ERR_UART_BUFFER_FULL` | 缓冲区满 |

### 传感器模块错误

| 错误码 | 说明 |
|-------|------|
| `APP_ERR_SENSOR_NOT_RESPONDING` | 传感器无响应 |
| `APP_ERR_SENSOR_INVALID_DATA` | 无效数据 |
| `APP_ERR_SENSOR_CHECKSUM` | 校验失败 |
| `APP_ERR_SENSOR_NOT_FOUND` | 传感器未找到 |

## 使用示例

### 基本用法

```c
#include "appErrorCode.h"

app_err_t my_function(void *param)
{
    if (param == NULL) {
        return APP_ERR_NULL_PTR;
    }

    if (some_condition) {
        return APP_ERR_TIMEOUT;
    }

    return APP_ERR_OK;
}

// 调用处理
app_err_t ret = my_function(ptr);
if (APP_ERR_FAILED(ret)) {
    printf("Error: %s - %s\n",
           app_Err_ToString(ret),
           app_Err_GetDescription(ret));
}
```

### 模块和类别判断

```c
app_err_t ret = some_comm_function();

if (APP_ERR_FAILED(ret)) {
    // 判断是否为通信模块错误
    if (app_Err_IsModule(ret, APP_ERR_MODULE_COMM)) {
        printf("Communication module error\n");
    }

    // 判断是否为超时错误
    if (app_Err_IsCategory(ret, APP_ERR_CATEGORY_TIMEOUT)) {
        printf("Timeout occurred, retrying...\n");
    }

    // 判断是否可恢复
    if (app_Err_IsRecoverable(ret)) {
        // 重试逻辑
        retry();
    }
}
```

### 自定义错误码

```c
// 定义自定义模块和错误码
#define MY_ERR_MODULE 0x09000000U

#define MY_ERR_CUSTOM_FAIL (MY_ERR_MODULE | APP_ERR_CATEGORY_INTERNAL | 0x001)

app_err_t my_custom_function(void)
{
    return MY_ERR_CUSTOM_FAIL;
}
```

## 扩展新模块

添加新模块的错误码，按照以下模板：

```c
/* 在 appErrorCode.h 中添加 */

// 1. 定义模块标识（如果需要新模块）
#define APP_ERR_MODULE_MYNEW 0x09000000U  // 使用未占用的模块号

// 2. 定义具体错误码
#define APP_ERR_MYNEW_ERROR1 (APP_ERR_MODULE_MYNEW | APP_ERR_CATEGORY_STATE | 0x001)
#define APP_ERR_MYNEW_ERROR2 (APP_ERR_MODULE_MYNEW | APP_ERR_CATEGORY_TIMEOUT | 0x001)

/* 在 appErrorCode.c 的 s_errorTable 中添加条目 */
{APP_ERR_MYNEW_ERROR1, "APP_ERR_MYNEW_ERROR1", "Description here"},
{APP_ERR_MYNEW_ERROR2, "APP_ERR_MYNEW_ERROR2", "Description here"},
```

## 可恢复错误

以下错误被定义为可恢复错误（可重试）：

- `APP_ERR_TIMEOUT` - 通用超时
- `APP_ERR_BUSY` - 资源忙碌
- `APP_ERR_COMM_TX_BUSY` - 通信发送忙碌
- `APP_ERR_COMM_QUEUE_FULL` - 通信队列满
- `APP_ERR_UART_TX_BUSY` - UART发送忙碌
- `APP_ERR_UART_TX_TIMEOUT` - UART发送超时
- `APP_ERR_PROTO_FRAME_TIMEOUT` - 协议帧超时

## 文件说明

| 文件 | 说明 |
|------|------|
| [appErrorCode.h](appErrorCode.h) | 错误码定义头文件 |
| [appErrorCode.c](appErrorCode.c) | 错误码实现文件 |

## 许可证

本项目采用开源许可证，具体请参阅项目文件。
