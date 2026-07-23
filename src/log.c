#include "log.h"
#include <linux/export.h>
#include <linux/skbuff.h>

int dbg_trace_lvl = 1;

int get_dbg_lvl(){
    return dbg_trace_lvl;
}

void set_dbg_lvl(int val){
    dbg_trace_lvl = val;
}

noinline void gtp5g_trace_drop(enum gtp5g_drop_reason reason, struct sk_buff *skb)
{
    /*
     * Intentionally empty: 5G-DPOP attaches an eBPF kprobe here and reads
     * both arguments. EXPORT_SYMBOL_GPL keeps the hook visible and stable
     * after the module is loaded.
     */
}
EXPORT_SYMBOL_GPL(gtp5g_trace_drop);
