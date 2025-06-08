/*
===============================================================================
 Name        : config_LPC1769.h
 Author      : D. Bechevet, F. Vannel, A. Lescourt, Ruben Wihler
 Copyright   : HES-SO hepia
 Year        : 2013-2014, 2025
===============================================================================
*/

#ifndef CONFIG_LPC1769_H_
#define CONFIG_LPC1769_H_

/*
 * Ce fichier contient les définitions des registres du microcontroleur LPC1769.
 * Ces définitions sont utilisées pour configurer les périphériques du microcontroleur.
 *
 * Les registres sont définis en utilisant des pointeurs vers les adresses mémoire
 * correspondantes (le mot clé volatile est utilisé pour ne pas optimiser les accès).
 * 
 * La documentation de la carte LPC1769 est disponible ici:
 * https://cyberlearn.hes-so.ch/pluginfile.php/2188512/mod_resource/content/1/UM10360.pdf
 *
 * La documentation de la carte MyLab2 est disponible ici:
 * https://hepialsn.hesge.ch/myLab2/hepia_mylab2_doc_v1_3.pdf
*/

//------------------------ GPIO ------------------------//
/*
 * Le GPIO (General Purpose Input/Output) est ce qui permet de communiquer
 * avec des periphériques externes. (Ex: LED, bouton poussoir, joystick, etc.)
 * 
 * Notre microcontroleur a 5 ports GPIO (FIO0, FIO1, FIO2, FIO3 et FIO4).
 * Chaque port a 32 pins (0-31). En gros, chaque port est un tableau de 32 bits.
 * Chaque bit du port correspond donc à une pin.
 * 
 * Chaque port a 5 registres:
 *   - DIR: Direction (0 = input, 1 = output)
 *   - MASK: Masque (0 = pas de changement, 1 = changement)
 *   - PIN: Valeur actuelle (0 = low, 1 = high)
 *   - SET: Met à 1 les bits du registre MASK
 *   - CLR: Met à 0 les bits du registre MASK
 *
 * Nous pouvons accéder à ces registres en utilisant des pointeurs.
 * Ces pointeurs sont définis ci-dessous.
*/

#define	FIO0DIR			(*((volatile uint32_t *) 0x2009C000))
#define	FIO0MASK		(*((volatile uint32_t *) 0x2009C010))
#define	FIO0PIN			(*((volatile uint32_t *) 0x2009C014))
#define	FIO0SET			(*((volatile uint32_t *) 0x2009C018))
#define	FIO0CLR			(*((volatile uint32_t *) 0x2009C01C))

#define	FIO1DIR			(*((volatile uint32_t *) 0x2009C020))
#define	FIO1MASK		(*((volatile uint32_t *) 0x2009C030))
#define	FIO1PIN			(*((volatile uint32_t *) 0x2009C034))
#define	FIO1SET			(*((volatile uint32_t *) 0x2009C038))
#define	FIO1CLR			(*((volatile uint32_t *) 0x2009C03C))

#define	FIO2DIR			(*((volatile uint32_t *) 0x2009C040))
#define	FIO2MASK		(*((volatile uint32_t *) 0x2009C050))
#define	FIO2PIN			(*((volatile uint32_t *) 0x2009C054))
#define	FIO2SET			(*((volatile uint32_t *) 0x2009C058))
#define	FIO2CLR			(*((volatile uint32_t *) 0x2009C05C))

#define	FIO3DIR			(*((volatile uint32_t *) 0x2009C060))
#define	FIO3MASK		(*((volatile uint32_t *) 0x2009C070))
#define	FIO3PIN			(*((volatile uint32_t *) 0x2009C074))
#define	FIO3SET			(*((volatile uint32_t *) 0x2009C078))
#define	FIO3CLR			(*((volatile uint32_t *) 0x2009C07C))

#define	FIO4DIR			(*((volatile uint32_t *) 0x2009C080))
#define	FIO4MASK		(*((volatile uint32_t *) 0x2009C090))
#define	FIO4PIN			(*((volatile uint32_t *) 0x2009C094))
#define	FIO4SET			(*((volatile uint32_t *) 0x2009C098))
#define	FIO4CLR			(*((volatile uint32_t *) 0x2009C09C))


//-------------------- INTERRUPTIONS --------------------//
/*
 *  Les interruptions sont des signaux qui permettent de signaler un événement.
 *  Elles peuvent être générées par des périphériques externes (ex: bouton poussoir)
 *  ou par le microcontrôleur lui-même (ex: timer).
 *
 *  Le fichier cr_startup_lcp175x_6x.c contient les fonctions d'interruption.
 *  Ces fonctions sont appelées lorsque l'interruption est générée.
 *
 *  Nous pouvons overrider ces fonctions en les définissant dans notre code.
 *  Quand l'interruption est générée, cette fonction sera appelée à la place de la 
 *  fonction par défaut (Attention: il faut que la fonction ait le même nom).
 *
 *  Les registres ci-dessous permettent de configurer les interruptions.
*/

//IO0 Interupt Enable Rising (montant) [READ/WRITE]
#define IO0IntEnR       (*((volatile uint32_t *) 0x40028090))
#define IO2IntEnR       (*((volatile uint32_t *) 0x400280B0))

//IO0 Interupt Enable Falling (descendant) [READ/WRITE]
#define IO0IntEnF       (*((volatile uint32_t *) 0x40028094))
#define IO2IntEnF       (*((volatile uint32_t *) 0x400280B4))

//IO0 Interupt Status Rising [READ ONLY]
#define IO0IntStatR     (*((volatile uint32_t *) 0x40028084))
#define IO2IntStatR     (*((volatile uint32_t *) 0x400280A4))

//IO0 Interupt Status Falling [READ ONLY]
#define IO0IntStatF     (*((volatile uint32_t *) 0x40028088))
#define IO2IntStatF     (*((volatile uint32_t *) 0x400280A8))

//IO0 Interupt Clear [WRITE ONLY]
//Permet de dire au microcontroleur que l'on a traité l'interruption
#define IO0IntClr       (*((volatile uint32_t *) 0x4002808C))
#define IO2IntClr       (*((volatile uint32_t *) 0x400280AC))

//Overall Interrupt Status [READ ONLY]
//Permet de savoir si une interruption est en cours
#define IntStatus       (*((volatile uint32_t *) 0x40028080))

// Interrupt Set-Enable Registers [WRITE ONLY]
// Active les interruptions pour les périphériques
#define ISER0           (*((volatile uint32_t *) 0xE000E100))
#define ISER1           (*((volatile uint32_t *) 0xE000E104))


//-------------------- System Tick Timer --------------------//
/*
 * Le System Tick Timer est un timer qui permet de générer des interruptions.
 * Il est utilisé pour générer des interruptions à intervalles réguliers.
 *
 * Il est configuré pour générer une interruption toutes les millisecondes.
 * (SYSCLOCK = 4MHz, donc 1ms = 4000 cycles)
 *
 * Les registres ci-dessous permettent de configurer le timer:
 *  - STCTRL: Contrôle du timer
 *  - STRELOAD: Valeur de rechargement
 *  - STCURR: Valeur actuelle
 *  - STCALIB: Valeur de calibration
*/


#define SYSCLOCK        100000000//hz

#define STCTRL          (*((volatile uint32_t *) 0xE000E010))
#define STRELOAD        (*((volatile uint32_t *) 0xE000E014))
#define STCURR          (*((volatile uint32_t *) 0xE000E018))
#define STCALIB         (*((volatile uint32_t *) 0xE000E01C))

#define	CCR				(*((volatile uint32_t *) 0xE000ED14))
#define	SysTick_CTRL	(*((volatile uint32_t *) 0xE000E010))
#define	SysTick_LOAD	(*((volatile uint32_t *) 0xE000E014))
   
//--------------------------- SPI ---------------------------//
/*
 * SPI (Serial Peripheral Interface) est un protocole de communication.
 * Il est utilisé pour communiquer avec des périphériques externes.
 *
 * C'est un modele Master/Slave.
 * Le microcontroleur est le Master et les périphériques sont les Slaves.
 *
 * Le microcontroleur envoie des données au périphérique et en reçoit des donnée.
 * Le master peut envoyer des données à plusieurs slaves en même temps.
 *
 * Le SPI utilise 4 lignes:
 *  - SCK: Horloge
 *  - MOSI: Données envoyées par le master
 *  - MISO: Données envoyées par le slave
 *  - CS: Chip Select (permet de sélectionner le slave)
*/

//SPI Control Register [READ/WRITE]
//Ce registre contrôle les opérations du SPI.
#define S0SPCR          (*((volatile uint32_t *) 0x40020000))

//SPI Status Register [READ-ONLY]
//Ce registre montre l'état du SPI.
#define S0SPSR          (*((volatile uint32_t *) 0x40020004))

//SPI Data Register [READ/WRITE]
//Sert à envoyer et recevoir des données.
#define S0SPDR          (*((volatile uint32_t *) 0x40020008))

//SPI Clock Configuration Register [READ/WRITE]
//Sert à configurer la fréquence d'horloge du SPI.
#define S0SPCCR         (*((volatile uint32_t *) 0x4002000C))

//SPI Interrupt Register [READ/WRITE]
//Permet d'activer et de désactiver les interruptions SPI.
#define S0SPINT         (*((volatile uint32_t *) 0x4002001C))

//Pin Function
#define PINSEL0         (*((volatile uint32_t *) 0x4002C000))
#define PINSEL1         (*((volatile uint32_t *) 0x4002C004))
#define PINSEL2         (*((volatile uint32_t *) 0x4002C008))
#define PINSEL3         (*((volatile uint32_t *) 0x4002C00C))
#define PINSEL4         (*((volatile uint32_t *) 0x4002C010))

#endif /* CONFIG_LPC1769_H_ */



//--------------------------- AUTRE ---------------------------//
// Syscon Miscellaneous Registers
#define SCS				(*((volatile uint32_t *) 0x400FC1A0))
// CLK SOURCE SELECTION
#define CLKSRCSEL		(*((volatile uint32_t *) 0x400FC10C))
// PLL0, Main PLL
#define PLL0CON			(*((volatile uint32_t *) 0x400FC080))
#define PLL0CFG			(*((volatile uint32_t *) 0x400FC084))
#define PLL0STAT		(*((volatile uint32_t *) 0x400FC088))
#define PLL0FEED		(*((volatile uint32_t *) 0x400FC08C))
// PLL1, UBS PLL
#define PLL1CON			(*((volatile uint32_t *) 0x400FC0A0))
#define PLL1CFG			(*((volatile uint32_t *) 0x400FC0A4))
#define PLL1STAT		(*((volatile uint32_t *) 0x400FC0A8))
#define PLL1FEED		(*((volatile uint32_t *) 0x400FC0AC))
// CLOCK DIVIDER
#define CCLKCFG			(*((volatile uint32_t *) 0x400FC104))
#define USBCLKCFG		(*((volatile uint32_t *) 0x400FC108))
#define PCLKSEL0		(*((volatile uint32_t *) 0x400FC1A8))
#define PCLKSEL1		(*((volatile uint32_t *) 0x400FC1AC))
// POWER CONTROL
#define PCON			(*((volatile uint32_t *) 0x400FC0C0))
#define PCONP			(*((volatile uint32_t *) 0x400FC0C4))
// Utility
#define CLKOUTCFG		(*((volatile uint32_t *) 0x400FC1C8))

// Flash Accelerator
#define FLASHCFG		(*((volatile uint32_t *) 0x400FC000))
