#include "sched.h"
#include "thread.h"
#include "ztimer.h"
#include "sched_feedback.h"

#define ENABLE_DEBUG 1
#include "debug.h"

static void _sched_feedback_cb(void *d);

static ztimer_t _fb_timer = { .callback = _sched_feedback_cb };

void _sched_feedback_cb(void *d)
{
    (void)d;
    thread_t *active_thread = thread_get_active();
    switch (active_thread->priority)
    {
        case 2:
            sched_change_priority(active_thread, active_thread->priority+1);
            break;
        case 3:
            sched_change_priority(active_thread, active_thread->priority+1);
            break;
        case 4:
            sched_runq_advance(4);
            thread_yield_higher();
            break;
        default:
            sched_runq_advance(4);
            thread_yield_higher();
            break;
    }
    return;
}

static inline void _sched_feedback_remove(void)
{
    ztimer_remove(SCHED_FB_TIMERBASE, &_fb_timer);
}

static inline void _sched_feedback_set(uint8_t prio)
{
    if (prio == 0) {
        return;
    }
    ztimer_set(SCHED_FB_TIMERBASE, &_fb_timer, 500);
}

void sched_runq_callback(uint8_t prio)
{
    // Check if the parameter passed is not
    // a masked priority or a 0
    if (SCHED_FB_MASK & (1 << prio) || prio == 0) {
        return;
    }
    switch(prio)
    {
        case 1:
            break;
        case 15:
            _sched_feedback_remove();
            break;
        default:
            _sched_feedback_set(prio);
            break;
    }
    return;
}

void sched_feedback_init(void)
{
    // init fb scheduler
    thread_t *active_thread = thread_get_active();
    if (active_thread) {
        DEBUG("First executed thread %s. PID: %u. Priority: %u.\n", active_thread->name, active_thread->pid, active_thread->priority);
        sched_runq_callback(active_thread->priority);
    }
}
