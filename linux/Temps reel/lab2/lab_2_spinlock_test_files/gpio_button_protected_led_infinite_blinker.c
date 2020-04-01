#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/workqueue.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#define PIN_LED 11
#define PIN_BUTTON 8

static int button_irq = -1;
static int start_stop = 0;
static unsigned long last_interrupt_time = 0;

static struct workqueue_struct *wq;

DEFINE_SPINLOCK(sl);

static void blink_work_func(struct work_struct *w)
{

  spin_lock(&sl);
  
  while(start_stop) {
    gpio_set_value(PIN_LED,!gpio_get_value(PIN_LED));
    msleep(100);
  }
  gpio_set_value(PIN_LED,0);
  spin_unlock(&sl);
}



DECLARE_DELAYED_WORK(w, blink_work_func);

static irqreturn_t button_ih(unsigned int irq, void *data)
{

  
  unsigned long interrupt_time = jiffies;
  
  if (interrupt_time - last_interrupt_time > msecs_to_jiffies(200)) 
  {
    start_stop = !start_stop;
    queue_delayed_work_on(0, wq, &w, msecs_to_jiffies(1000));
  }
  last_interrupt_time = interrupt_time;
  
  return IRQ_HANDLED;
   
}


static int __init gpio_button_protected_infinite_led_blinker_init(void)
{ 
  int ret = 0;
  
  printk(KERN_INFO "%s\n", __func__);
  
  ret = gpio_request_one(PIN_LED, GPIOF_OUT_INIT_LOW, "led");
  
  if (ret) {
    printk(KERN_ERR "Unable to request GPIOs for LED: %d\n", ret);
    return ret; 
  }
  
  printk(KERN_INFO "Successfully requested GPIO %d for LED \n", PIN_LED);


  
  
  ret = gpio_request_one(PIN_BUTTON, GPIOF_IN, "button");
  
  if (ret) {
    printk(KERN_ERR "Unable to request GPIO %d for BUTTON: %d\n", PIN_BUTTON, ret);
    return ret;
  }
  
  printk(KERN_INFO "Successfully requested GPIO %d for BUTTON \n", PIN_BUTTON);
  
  
  ret = gpio_to_irq(PIN_BUTTON);
  
  if(ret < 0) {
    printk(KERN_ERR "Unable to request IRQ: %d\n", ret); 
    gpio_free(PIN_BUTTON);
    gpio_free(PIN_LED);
    return ret;
  }
  
  printk(KERN_INFO "Successfully IRQ created for GPIO %d\n", PIN_BUTTON);
  
  button_irq = ret;
  
  ret = request_irq(button_irq,                 
                    (irq_handler_t) button_ih, 
                    IRQF_TRIGGER_FALLING,      
                    "buttih",              
                    NULL);
  
  if(ret) {
    printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
    free_irq(button_irq, NULL);
    gpio_free(PIN_BUTTON);
    gpio_free(PIN_LED);
    return ret;
  }

  printk(KERN_INFO "Successfully requested IRQ \n");


  wq = create_workqueue("own_wq");

  
  return 0;
}


static void __exit gpio_button_protected_infinite_led_blinker_exit(void)
{
  printk(KERN_INFO "%s\n", __func__);

  cancel_delayed_work_sync(&w);
  destroy_workqueue(wq);

  free_irq(button_irq, NULL);

  gpio_set_value(PIN_LED, 0); 
  gpio_free(PIN_LED);
  gpio_free(PIN_BUTTON);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebti Mouelhi");
MODULE_DESCRIPTION("Button-driven infinite LED blinker using deferrable works");

module_init(gpio_button_protected_infinite_led_blinker_init);
module_exit(gpio_button_protected_infinite_led_blinker_exit);
