#ifndef SCTP_LWIP_THREAD_SAFE_H
#define SCTP_LWIP_THREAD_SAFE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Thread-safe wrapper for sctp_init_ifns_for_vrf
 *
 * This function ensures that the network interface operations happen in the TCPIP thread
 * to avoid thread safety issues with LWIP when CONFIG_LWIP_CHECK_THREAD_SAFETY is enabled.
 *
 * @param vrfid The VRF ID to initialize interfaces for
 */
void sctp_lwip_init_ifns_for_vrf_safe(uint32_t vrfid);

/**
 * Run fn(arg) with lwIP's core state protected, as the TCPIP thread would run it.
 *
 * - Already in the TCPIP context (on the TCPIP thread, or holding the core
 *   lock): fn runs in place. Handing off from there would wait on itself.
 * - LWIP_TCPIP_CORE_LOCKING: fn runs under the core lock, with no hand-off.
 * - Otherwise: fn is handed to the TCPIP thread and waited for.
 *
 * @return true once fn has run. false if it could not be scheduled or the wait
 *         timed out; after a timeout fn may still run, so arg must stay valid.
 */
bool sctp_lwip_call_in_tcpip(void (*fn)(void *arg), void *arg, uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif

#endif /* SCTP_LWIP_THREAD_SAFE_H */
