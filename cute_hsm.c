// cute_hsm.c
#include "cute_hsm.h"
#include <assert.h>

// 初始化状态机
void cute_hsm_init(CuteHSM *hsm, CuteState *state, void *context)
{
    assert(hsm && state);
    hsm->context = context;
    hsm->tick = 0;
    hsm->active = state;

    // 进入初始状态链
    CuteState *current = state;
    while (current)
    {
        hsm->active = current;
        current->handler(hsm, CUTE_EVT_ENTRY, 0);
        current = current->child;
    }
}

// 查找最低共同祖先
static CuteState *cute_find_lca(CuteState *a, CuteState *b)
{
    if (!a || !b)
        return NULL;
    if (a == b)
        return a;

    // 计算深度
    int depth_a = 0, depth_b = 0;
    for (CuteState *t = a; t; t = t->parent)
        depth_a++;
    for (CuteState *t = b; t; t = t->parent)
        depth_b++;

    // 调整到同一深度
    while (depth_a > depth_b)
    {
        a = a->parent;
        depth_a--;
    }
    while (depth_b > depth_a)
    {
        b = b->parent;
        depth_b--;
    }

    // 同时向上查找
    while (a && b && a != b)
    {
        a = a->parent;
        b = b->parent;
    }
    return a;
}

// 状态转换
void cute_hsm_trans(CuteHSM *hsm, CuteState *target)
{
    assert(hsm && target);
    if (hsm->active == target)
        return;

    CuteState *lca = cute_find_lca(hsm->active, target);
    if (!lca)
    {
        // 直接切换到目标状态
        hsm->active = target;
        target->handler(hsm, CUTE_EVT_ENTRY, 0);

        // 进入子状态链
        CuteState *current = target;
        while (current->child)
        {
            current = current->child;
            hsm->active = current;
            current->handler(hsm, CUTE_EVT_ENTRY, 0);
        }
        return;
    }

    // 1. 退出当前状态链
    CuteState *current = hsm->active;
    while (current != lca)
    {
        current->handler(hsm, CUTE_EVT_EXIT, 0);
        current = current->parent;
    }

    // 2. 收集进入路径
    CuteState *path[CUTE_HSM_MAX_DEPTH];
    int path_len = 0;

    // 计算从target到lca的路径长度
    int depth = 0;
    for (CuteState *s = target; s != lca; s = s->parent)
    {
        depth++;
    }

    // 按正确顺序填充路径
    CuteState *s = target;
    for (int i = depth - 1; i >= 0 && path_len < CUTE_HSM_MAX_DEPTH; i--)
    {
        for (int j = 0; j < i; j++)
        {
            s = s->parent;
        }
        path[path_len++] = s;
        s = target;
    }

    // 3. 进入路径上的状态
    for (int i = 0; i < path_len; i++)
    {
        hsm->active = path[i];
        path[i]->handler(hsm, CUTE_EVT_ENTRY, 0);
    }

    // 4. 进入子状态链
    current = target;
    while (current->child)
    {
        current = current->child;
        hsm->active = current;
        current->handler(hsm, CUTE_EVT_ENTRY, 0);
    }
}

// 状态机滴答
void cute_hsm_tick(CuteHSM *hsm)
{
    if (hsm && hsm->active)
    {
        hsm->tick++;
        hsm->active->handler(hsm, CUTE_EVT_TICK, hsm->tick);
    }
}

// 事件处理
void cute_hsm_event(CuteHSM *hsm, uint32_t event, uint32_t param)
{
    if (!hsm || !hsm->active)
        return;

    // 事件冒泡
    for (CuteState *s = hsm->active; s; s = s->parent)
    {
        s->handler(hsm, event, param);
    }
}
