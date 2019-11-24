#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/workqueue.h>
#include <linux/uaccess.h>

#define PIN_LED 11
#define PIN_BUTTON 8

//////////////////////////////////////////////////////////////////////
// Important : code defensively, handle error cases for each call ! //
//////////////////////////////////////////////////////////////////////

static int press_button_irq = -1;
static int nb_blinks = 0;

// other global declarations may be added here

// the deferrable workqueue function 
static void blink_work_func(unsigned long data)
{
  // blink the LED, plugged on PIN_LED, for "nb_blinks" times
  unsigned int i;
  for (i = 0; i < nb_blinks; i++){
    gpio_set_value(PIN_LED, 1);
    //gpio_set_value(PIN_LED, 0);
  }
  

}

// declare a work "w", and attach it to "blink_work_func"
// - use the macro DECLARE_DELAYED_WORK
DECLARE_DELAYED_WORK(w, blink_work_func);



// the press-button IH
static irqreturn_t press_button_ih(unsigned int irq, void *data)
{

  // something IMPORTANT should be considered here, what is it?
  
  // time-critical instructions:
  // - update "nb_blinks" according to the lab's instruction
  nb_blinks = (nb_blinks + 1) % 6;

  // deferrable instruction:
  // - schedule the work "w" after a delay of 1 second
  schedule_delayed_work(&w, 1e9);
  return IRQ_HANDLED;
}


static int __init gpio_button_work_led_blinker_init(void)
{
  // a variable used to save successively the error statuses of function calls
  int ret = 0;
  
  printk(KERN_INFO "%s\n", __func__);

  // request PIN_LED for LED D6, print a kernel success message 
  ret = gpio_request_one(PIN_LED, GPIOF_OUT_INIT_LOW, "led");
  
  if (ret){
      printk(KERN_ERR "PIN_LED wasn't loaded, err: %d\n", ret);
      return ret;
   }
   printk(KERN_INFO "PIN_LED was loaded successfully\n");
  

  // request PIN_BUTTON for the press-button, print a kernel success message 
  ret = gpio_request_one(PIN_BUTTON, GPIOF_IN, "button");
  
  if (ret){
      printk(KERN_ERR "PIN_BUTTON wasn't loaded, err: %d\n", ret);
      return ret;
   }
   printk(KERN_INFO "PIN_BUTTON was loaded successfully\n");

  
  // associate PIN_BUTTON to an IRQ number, print a kernel success message 
   ret = gpio_to_irq(PIN_BUTTON);
   printk(KERN_INFO "associated PIN_BUTTON to an IRQ number");

  
  // store the IRQ number in "press_button_irq"
  press_button_irq = ret;

  // allocate an IRQ line to "press_button_irq"
  // - interrupt are to be "falling-edge" triggered
  // - free the probed IRQ numbers "press_button_irq" and GPIOs
  // - print a kernel message in case of success
  ret = request_irq(press_button_irq,
                    (irq_handler_t) press_button_ih,
                    IRQF_TRIGGER_FALLING,
                    "gpio_handler",
                    NULL);
  if(!ret){
    printk(KERN_INFO "The interrupt request is a success");
  }
  

  return 0;
}


static void __exit gpio_button_work_led_blinker_exit(void)
{
  printk(KERN_INFO "%s\n", __func__);

  // cancel the work "w"
  cancel_delayed_work_sync(&w);
  // release "press_button_irq"
  free_irq(press_button_irq, NULL);
  // release PIN_LED and PIN_BUTTON properly
  //                                ========
  gpio_free(PIN_LED);
  gpio_free(PIN_BUTTON);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Buot, Adrien and Guicharnaud, Léo and Sabatey, Clara");
MODULE_DESCRIPTION("Press-button LED blinker using deferrable workqueues");

module_init(gpio_button_work_led_blinker_init);
module_exit(gpio_button_work_led_blinker_exit);
