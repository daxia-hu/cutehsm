// demo.c
#include "cute_hsm.h"
#include <stdio.h>
#include <windows.h>

// 状态处理函数
void normal_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void idle_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void charge_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void config_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void adjust_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void float_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void test_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);
void protect_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param);

// 状态实例定义
CuteState state_protect = {
    .name = "保护状态",
    .parent = NULL,
    .child = NULL,
    .handler = protect_state_handler,
};

CuteState state_test = {
    .name = "测试状态",
    .parent = NULL,
    .child = NULL,
    .handler = test_state_handler,
};

CuteState state_config = {
    .name = "配置状态",
    .parent = NULL,
    .child = NULL,
    .handler = config_state_handler,
};

CuteState state_adjust = {
    .name = "调节状态",
    .parent = NULL,
    .child = NULL,
    .handler = adjust_state_handler,
};

CuteState state_float = {
    .name = "浮充状态",
    .parent = NULL,
    .child = NULL,
    .handler = float_state_handler,
};

CuteState state_charge = {
    .name = "充电状态",
    .parent = NULL,
    .child = &state_config,
    .handler = charge_state_handler,
};

CuteState state_idle = {
    .name = "空闲状态",
    .parent = NULL,
    .child = NULL,
    .handler = idle_state_handler,
};

CuteState state_normal = {
    .name = "正常状态",
    .parent = NULL,
    .child = &state_idle,
    .handler = normal_state_handler,
};

// 设置父子关系
void setup_state_hierarchy()
{
    state_charge.parent = &state_normal;
    state_idle.parent = &state_normal;
    state_config.parent = &state_charge;
    state_adjust.parent = &state_charge;
    state_float.parent = &state_charge;
    state_test.parent = NULL;    // 顶级状态
    state_protect.parent = NULL; // 顶级状态
}

// 状态处理函数实现
void normal_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("[正常状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("[正常状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("[正常状态] 滴答: %d\n", param);
        break;
    }
}

void idle_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("  [空闲状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("  [空闲状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("  [空闲状态] 滴答: %d\n", param);
        break;
    }
}

void charge_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("  [充电状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("  [充电状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("  [充电状态] 滴答: %d\n", param);
        break;
    }
}

void config_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("    [配置状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("    [配置状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("    [配置状态] 滴答: %d\n", param);
        break;
    }
}

void adjust_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("    [调节状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("    [调节状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("    [调节状态] 滴答: %d\n", param);
        break;
    }
}

void float_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("    [浮充状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("    [浮充状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("    [浮充状态] 滴答: %d\n", param);
        break;
    }
}

void test_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("[测试状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("[测试状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("[测试状态] 滴答: %d\n", param);
        break;
    }
}

void protect_state_handler(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    switch (event)
    {
    case CUTE_EVT_ENTRY:
        printf("[保护状态] 进入\n");
        break;
    case CUTE_EVT_EXIT:
        printf("[保护状态] 退出\n");
        break;
    case CUTE_EVT_TICK:
        printf("[保护状态] 滴答: %d\n", param);
        break;
    }
}

int main()
{
    printf("=== CUTEHSM 状态机演示 ===\n");

    // 设置状态层次关系
    setup_state_hierarchy();

    // 创建状态机
    CuteHSM hsm;
    cute_hsm_init(&hsm, &state_normal, NULL);

    printf("\n--- 初始状态 ---\n");
    for (int i = 0; i < 3; i++)
    {
        cute_hsm_tick(&hsm);
        Sleep(1000);
    }

    printf("\n--- 切换到充电状态 ---\n");
    cute_hsm_trans(&hsm, &state_charge);
    for (int i = 0; i < 3; i++)
    {
        cute_hsm_tick(&hsm);
        Sleep(1000);
    }

    printf("\n--- 切换到浮充状态 ---\n");
    cute_hsm_trans(&hsm, &state_float);
    for (int i = 0; i < 3; i++)
    {
        cute_hsm_tick(&hsm);
        Sleep(1000);
    }

    printf("\n--- 切换到测试状态 ---\n");
    cute_hsm_trans(&hsm, &state_test);
    for (int i = 0; i < 3; i++)
    {
        cute_hsm_tick(&hsm);
        Sleep(1000);
    }

    printf("\n--- 切换回正常状态 ---\n");
    cute_hsm_trans(&hsm, &state_normal);
    for (int i = 0; i < 3; i++)
    {
        cute_hsm_tick(&hsm);
        Sleep(1000);
    }

    printf("\n=== 演示结束 ===\n");
    return 0;
}
