#ifndef SCHED_FEEDBACK_H
#define SCHED_FEEDBACK_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(SCHED_FB_TIMEOUT) || defined(DOXYGEN)
/**
 * @brief   Time between feedback calls in Units of SCHED_FB_TIMERBASE
 *
 * @details Defaults to 10ms
 */
#if MODULE_ZTIMER_MSEC
#define SCHED_FB_TIMEOUT 10
#else
#define SCHED_FB_TIMEOUT 10000
#endif
#endif

#if !defined(SCHED_FB_TIMERBASE) || defined(DOXYGEN)
/**
 * @brief   ztimer to use for the feedback scheduler
 *
 * @details Defaults to ZTIMER_MSEC if available else it uses ZTIMER_USEC
 */
#if MODULE_ZTIMER_MSEC
#define SCHED_FB_TIMERBASE ZTIMER_MSEC
#else
#define SCHED_FB_TIMERBASE ZTIMER_USEC
#endif
#endif

#if !defined(SCHED_FB_MASK) || defined(DOXYGEN)
/**
 * @brief   Masks off priorities that should not be scheduled default: 0 is masked
 *
 * @details Priority 0 (highest) should always be masked.
 *          Threads with that priority may not be programmed
 *          with the possibility of being scheduled in mind.
 */
#define SCHED_FB_MASK (1 << 0)
#endif

/**
 *  @brief Initialises the Feedback Scheduler
 */
void sched_feedback_init(void);

#ifdef __cplusplus
}
#endif

#endif
