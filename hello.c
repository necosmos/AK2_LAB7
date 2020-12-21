#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/ktime.h>

struct head_list {
  struct head_list *next;
  ktime_t time;
};

MODULE_AUTHOR("Pinchuk IV-82");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static uint number = 1;
module_param(number,uint,S_IRUGO);
MODULE_PARM_DESC(number, "Output Repeating");

static int __init hello_world(void)
{
  uint i = 0;
  struct head_list *var_1, *var_2, *m, *var;

  head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

  var_1 = head;


  if(number == 0) {
    pr_warn("number = 0");
  }else if(number >=5 && number <= 10) {
    pr_warn("number is between 5 and 10");
  }
  BUG_ON(number>10);

  for(i = 0; i < number; i++){
    m = kmalloc(sizeof(struct head_list), GFP_KERNEL);
    if (i == 7){
        m = NULL;
    }
    if (ZERO_OR_NULL_PTR(m)){
        pr_err("No memory available");
        while (head != NULL && number != 0) {
            var = head;
            head = var->next;
            kfree(var);
        }
        BUG_ON(!m);
        return -ENOMEM;
    }
    var_1->time = ktime_get();
    pr_info("Hello World!");
    var_2 = var_1;
    var_1 = m;
  }
  if (number != 0) {
    kfree(var_2->next);
    var_2->next = NULL;
  }
  pr_info("Repeat number: %d\n", number);
  return 0;
}

static void __exit bye_world(void)
{
  struct head_list *var;

  while (head != NULL && number != 0) {
    var = head;
    pr_info("Time: %lld", var->time);
    head = var->next;
    kfree(var);
  }
  pr_info("");
}


module_init(hello_world);
module_exit(bye_world);
