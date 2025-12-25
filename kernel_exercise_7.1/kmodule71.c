#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

static struct nf_hook_ops nfho;

static unsigned int hook_func(void *priv,
                              struct sk_buff *skb,
                              const struct nf_hook_state *state)
{
    struct iphdr *iph;

    if (!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);
    if (iph) {
        printk(KERN_INFO "  Intercepted network packet from %pI4 to %pI4\n",
               &iph->saddr, &iph->daddr);
    }

    return NF_ACCEPT;
}

static void run_exercise(void)
{
    nfho.hook     = hook_func;
    nfho.hooknum  = NF_INET_PRE_ROUTING;
    nfho.pf       = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "  Netfilter hook registered.\n");
}

static void unregister_hook(void)
{
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "  Netfilter hook unregistered.\n");
}

static int __init start_module(void) {
    printk(KERN_INFO "kmodule71: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit exit_module(void) {
    unregister_hook();
    printk(KERN_INFO "kmodule71: == EXITING ==\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
