#Les makefile
Chaque Makefile correspond à un fichier .c
- Makefile_1 : gpio_timer_led_blinker.c (fichier test fait par le prof)
- Makefile_2 : gpio_sysfsconf_hrtimer_led_blinker.c
- Makefile_3 : gpio_button_work_led_blinker.c
- Makefile_4 : gpio_protected_led_blinker.c

renomer un par un chaque makefile en "Makefile" et run la commande "make"

#Envoi vers la raspberry
utiliser la commande scp :
`scp nom_fichier.ko pi@192.164.43.76:nom_fichier.ko`

exemple pour le premier : 
`scp gpio_timer_led_blinker.ko pi@192.164.43.76:gpio_timer_led_blinker.ko`

#Run du fichier sur la raspberry
- Pour load le fichier on doit faire la commande :
`sudo insmod nom_fichier.ko`

- Pour unload le fichier :
`sudo rmmod nom_fichier.ko`

- Pour afficher les messages générés pendant le load, durant l'action et pendant l'unload :
`dmesg` (faut pas s'inquieter si on voit 1000 trucs au dessus c'est normal et ça nous intéresse pas)

#Résultats attendus
- gpio_timer_led_blinker.ko
	Une led qui s'allume et s'éteint sur une période de 1s, les messages affichés sont un message de load,
	un message d'unload et un message à chaque allumage de la led.

- gpio_sysfsconf_hrtimer_led_blinker.ko
	Je sais pas encore, à modifier.

- gpio_button_work_led_blinker.ko
	Je sais pas encore, à modifier.

- gpio_protected_led_blinker.ko
	Je sais pas encore, à modifier.