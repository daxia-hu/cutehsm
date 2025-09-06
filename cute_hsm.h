// cute_hsm.h
#pragma once
#include <stdint.h>
#include <stdio.h>

#define CUTE_HSM_MAX_DEPTH 16

// 事件类型
typedef enum
{
    CUTE_EVT_ENTRY = 0x0001, // 进入状态
    CUTE_EVT_EXIT = 0x0002,  // 退出状态
    CUTE_EVT_TICK = 0x0004,  // 状态滴答
    CUTE_EVT_USER = 0x1000   // 用户事件起点
} CuteEvent;

typedef struct CuteState_t CuteState;
typedef struct CuteHSM_t CuteHSM;

// 状态处理函数
typedef void (*CuteHandler)(CuteHSM *hsm, uint32_t event, uint32_t param);

// 状态结构
typedef struct CuteState_t
{
    const char *name;    // 状态名称
    CuteState *parent;   // 父状态
    CuteState *child;    // 默认子状态
    CuteHandler handler; // 状态处理函数
} CuteState;

// 状态机结构
typedef struct CuteHSM_t
{
    CuteState *active; // 当前活动状态
    void *context;     // 用户上下文
    uint32_t tick;     // 状态机滴答
} CuteHSM;

// API接口
void cute_hsm_init(CuteHSM *hsm, CuteState *state, void *context);
void cute_hsm_trans(CuteHSM *hsm, CuteState *target);
void cute_hsm_tick(CuteHSM *hsm);
void cute_hsm_event(CuteHSM *hsm, uint32_t event, uint32_t param);
