#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

static struct nf_hook_ops nfho;

static unsigned int hook_func(void *priv,
                              struct sk_buff *skb,
                              const struct nf_hook_state *state)
{
    struct iphdr *iph;
    const char *proto_str = "UNKNOWN";

    if (!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);
    if (!iph)
        return NF_ACCEPT;

    switch (iph->protocol) {
        case IPPROTO_TCP: {
            struct tcphdr *tcph;
            tcph = (struct tcphdr *)((__u32 *)iph + iph->ihl);
            proto_str = "TCP";
            printk(KERN_INFO "  Packet [%s] from %pI4:%u to %pI4:%u\n",
                   proto_str,
                   &iph->saddr, ntohs(tcph->source),
                   &iph->daddr, ntohs(tcph->dest));
            break;
        }
        case IPPROTO_UDP: {
            struct udphdr *udph;
            udph = (struct udphdr *)((__u32 *)iph + iph->ihl);
            proto_str = "UDP";
            printk(KERN_INFO "  Packet [%s] from %pI4:%u to %pI4:%u\n",
                   proto_str,
                   &iph->saddr, ntohs(udph->source),
                   &iph->daddr, ntohs(udph->dest));
            break;
        }
        case IPPROTO_ICMP:
            proto_str = "ICMP";
            printk(KERN_INFO "  Packet [%s] from %pI4 to %pI4\n",
                   proto_str, &iph->saddr, &iph->daddr);
            break;
        default:
            printk(KERN_INFO "  Packet [%u] from %pI4 to %pI4\n",
                   iph->protocol, &iph->saddr, &iph->daddr);
            break;
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

static int __init start_module(void)
{
    printk(KERN_INFO "kmodule73: == STARTING ==\n");
    run_exercise();
    return 0;
}

static void __exit end_module(void)
{
    unregister_hook();
    printk(KERN_INFO "kmodule73: == EXITING ==\n");
}

module_init(start_module);
module_exit(end_module);

MODULE_LICENSE("GPL");
