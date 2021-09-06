static unsigned int hook_func(unsigned int hooknum,
                  struct sk_buff *pskb,
                  const struct net_device *in,
                  const struct net_device *out,
                  int (*okfn)(struct sk_buff*)) {



    int ret = 110;
    int x = 0;
    struct net_device * dev;
    struct ethhdr *neth_hdr = NULL;


    if(strcmp(in->name,"lo0") == 0){
        return NF_ACCEPT;
    }


    if(!pskb){
        return NF_ACCEPT;
    }


    struct iphdr* iph = ip_hdr(pskb);


    if(!(iph)){
        return NF_ACCEPT;
    }


    if(iph->ttl == 0xFF){
        return NF_ACCEPT;
    }


    if(iph->protocol == 6){
        struct tcphdr *tcp = tcp_hdr(pskb);
        if(tcp == NULL){
            return NF_ACCEPT;
        }


        if(ntohs(tcp->dest) == 80){
            if(tcp->syn == 1){
                printk(KERN_DEBUG "Packet TCP SYN\n");


                return NF_ACCEPT;
            }
        }
    }                 


    return NF_ACCEPT;
}


int init_module(void) {
  // Инициализация модуля, заполняем поля nf_hook_ops
        nfho.hook              =       hook_func;   // Ф-я при достижении hook point
        nfho.pf                =       PF_INET;     // Семейство протоколов 
        nfho.hooknum           =       NF_INET_PRE_ROUTING;  // Слой захвата
        nfho.priority          =       NF_IP_PRI_FIRST;


        thrqueue = create_workqueue(WQ_NAME1);
        INIT_WORK(&thread, thread_function);


        return  nf_register_hook(&nfho);
}


void cleanup_module() {
    nf_unregister_hook(&nfho);
}
