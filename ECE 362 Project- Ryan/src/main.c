#include "stm32f0xx.h"
#include <stdio.h>

void internal_clock();

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

uint16_t highscore;
char highscorestring[16];
uint16_t currentscore;
char currentscorestring[16];


void initc() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER |= 0x00005500; //setting output pins
    GPIOC->MODER &= 0xFFFFFF00; //setting input pins
    GPIOC->PUPDR |= 0x000000AA; //setting pull down resistors
    GPIOC->BSRR = 1 << 6;
}

//100 Hz update
void init_tim2(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //clock enable
    TIM2->DIER |= TIM_DIER_UIE; //update interrupt enable
    TIM2->PSC = 47; //1 hz configuration
    TIM2->ARR = 99999;
    NVIC->ISER[0] |= 1 << 15; //tim 2 interrupt enable
    TIM2->CR1 |= TIM_CR1_CEN; //count enable
}

void init_spi1() {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= 0x80008800; //afmode for pins 5,7,15
    GPIOA->AFR[0] &= 0x0F0FFFFF; //af0 for pins 5,7
    GPIOA->AFR[1] &= 0x0FFFFFFF; //af0 for pin 15
    SPI1->CR1 &= ~SPI_CR1_SPE; //spe clear
    SPI1->CR1 |= 0x0038; //baud rate minimum
    SPI1->CR2 |= 0x0900; //10bit word size
    SPI1->CR2 &= ~0x0600; //clear for middle bits
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_NSSP | SPI_CR2_TXDMAEN;
    SPI1->CR1 |= SPI_CR1_SPE; //spe enable
}

void spi_cmd(unsigned int data) {
    while ((SPI1->SR & SPI_SR_TXE) == 0) { }
    SPI1->DR = data;
}

//0x200 is the bitmask for a register read/write as opposed to a command
void spi_data(unsigned int data) {
    spi_cmd(data | 0x200);
}

void spi1_init_oled() {
    nano_wait(1000000); //wait 1 ms
    spi_cmd(0x38); //function set
    nano_wait(1000000);
    spi_cmd(0x08); //display off
    nano_wait(1000000);
    spi_cmd(0x01); //clear display
    nano_wait(2000000); //wait 2 ms
    spi_cmd(0x06); //entry mode
    nano_wait(1000000);
    spi_cmd(0x02); //cursor home
    nano_wait(1000000);
    spi_cmd(0x0C); //display on
    nano_wait(1000000);
}

void spi1_display1(const char *string) {
    spi_cmd(0x02); //cursor home position
    int i = 0;
    while (string[i] != '\0') {
        spi_data(string[i]);
        i++;
    }
}

void spi1_display2(const char *string) {
    spi_cmd(0xC0); //cursor second row
    int i = 0;
    while (string[i] != '\0') {
        spi_data(string[i]);
        i++;
    }
}

//OLED Display Update
void TIM2_IRQHandler() {
    TIM2->SR &= ~TIM_SR_UIF;
    int c = (GPIOC->IDR & (1 << 1)) ? 1 : 0;
    nano_wait(100000); //wait 0.1 ms
    if (c) {
        currentscore +=1;
    }
    if (currentscore >= highscore) {
        highscore = currentscore;
    }
    sprintf(highscorestring, "High Score:%d", highscore); //update
    spi1_display1(highscorestring);
    sprintf(currentscorestring, "Curr Score:%d", currentscore); //update
    spi1_display2(currentscorestring);
}



int main(void) {
    internal_clock();
    highscore=10;
    currentscore=0;

    initc();
    init_tim2();
    init_spi1();
    spi1_init_oled();
    
}
