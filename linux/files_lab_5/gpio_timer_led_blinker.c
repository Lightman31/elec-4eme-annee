#include <linux/module.h>	
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/gpio.h>

#define PIN_LED 11

static struct timer_list blink_timer;

static void timer_callback(unsigned long data)
{
  printk(KERN_INFO "%s\n", __func__);

  gpio_set_value(PIN_LED, data); 
  
  blink_timer.data = !data;  
  blink_timer.expires = jiffies + 1*HZ;
  add_timer(&blink_timer);
}



static int __init gpio_timer_led_blinker_init(void)
{
  int ret = 0;
  
  printk(KERN_INFO "%s\n", __func__);
  
  ret = gpio_request_one(PIN_LED, GPIOF_OUT_INIT_LOW, "led");
  
  if (ret) {
    printk(KERN_ERR "Unable to request GPIOs: %d\n", ret);
    return ret;
  }
  
  init_timer(&blink_timer);
  blink_timer.function = timer_callback;
  blink_timer.data = 1L; 
  blink_timer.expires = jiffies + 1*HZ; 
  add_timer(&blink_timer);
  
  return ret;
}



static void __exit gpio_timer_led_blinker_exit(void)
{
  printk(KERN_INFO "%s\n", __func__);
  del_timer_sync(&blink_timer);
  gpio_set_value(PIN_LED, 0); 
  gpio_free(PIN_LED);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebti Mouelhi");
MODULE_DESCRIPTION("Basic LED blinker using kernel timers.");
module_init(gpio_timer_led_blinker_init);
module_exit(gpio_timer_led_blinker_exit);
