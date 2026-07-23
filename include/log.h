#ifndef __GTP5G_LOG_H__
#define __GTP5G_LOG_H__

#include <linux/netdevice.h>

#define DBG(level, dev, fmt, args...) do {      \
    if (level <= get_dbg_lvl()) {               \
        if (dev)                                \
            printk_ratelimited("%s:[gtp5g] %s: "fmt, netdev_name(dev), __func__, ##args);   \
        else                                    \
            printk_ratelimited("[gtp5g] %s: " fmt, __func__, ##args);       \
    } \
} while(0)

#define GTP5G_LOG(dev, fmt, args...) DBG(0, dev, fmt, ##args)
#define GTP5G_ERR(dev, fmt, args...) DBG(1, dev, fmt, ##args)
#define GTP5G_WAR(dev, fmt, args...) DBG(2, dev, fmt, ##args)
#define GTP5G_INF(dev, fmt, args...) DBG(3, dev, fmt, ##args)
#define GTP5G_TRC(dev, fmt, args...) DBG(4, dev, fmt, ##args)

/*
 * Drop reason codes consumed by 5G-DPOP's eBPF agent.
 *
 * Keep these values in sync with:
 *   /home/ubuntu25/5G-DPOP/internal/ebpf/bpf/upf_monitor.bpf.c
 */
enum gtp5g_drop_reason {
    GTP5G_DROP_PKT_DROPPED        = 1,
    GTP5G_DROP_ECHO_RESP_CREATE   = 2,
    GTP5G_DROP_NO_ROUTE           = 3,
    GTP5G_DROP_PULL_FAILED        = 4,
    GTP5G_DROP_INVALID_EXT_HDR    = 5,
    GTP5G_DROP_NO_PDR             = 6,
    GTP5G_DROP_GENERAL            = 7,
    GTP5G_DROP_UL_GATE_CLOSED     = 8,
    GTP5G_DROP_DL_GATE_CLOSED     = 9,
    GTP5G_DROP_PDR_NULL           = 10,
    GTP5G_DROP_NO_F_TEID          = 11,
    GTP5G_DROP_URR_REPORT_FAIL    = 12,
    GTP5G_DROP_RED_PACKET         = 13,
    GTP5G_DROP_IP_XMIT_FAIL       = 14,
    GTP5G_DROP_NOT_TPDU           = 15,
    GTP5G_DROP_PULL_HDR_FAIL      = 16,
    GTP5G_DROP_NETIF_RX_FAIL      = 17,
    GTP5G_DROP_UNSUPPORTED_L3     = 18,
    GTP5G_DROP_SKB_PREPARE_FAIL   = 19,
    GTP5G_DROP_FAR_MISSING        = 20,
    GTP5G_DROP_INVALID_FAR_ACTION = 21,
    GTP5G_DROP_OHR_MISSING        = 22,
    GTP5G_DROP_OHC_MISSING        = 23,
};

int get_dbg_lvl(void);
void set_dbg_lvl(int);
noinline void gtp5g_trace_drop(enum gtp5g_drop_reason reason, struct sk_buff *skb);

#endif // __GTP5G_LOG_H__
