#include "stm32f0xx.h"
#include <stdio.h>


static char highscorestring[16];
static char currentscorestring[16];

void nano_wait(unsigned int n) {
    asm("        mov r0,%0\n"
        "repeat: sub r0,#83\n"
        "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

void init_spi1(void) {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER |= 0x80008800;     // Alternate function for PA5, PA7, PA15
    GPIOA->AFR[0] &= 0x0F0FFFFF;    // AF0 for PA5, PA7
    GPIOA->AFR[1] &= 0x0FFFFFFF;    // AF0 for PA15

    SPI1->CR1 &= ~SPI_CR1_SPE;
    SPI1->CR1 |= 0x0038; // Minimum baud rate
    SPI1->CR2 |= 0x0900; // 10-bit data size
    SPI1->CR2 &= ~0x0600;
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR2 |= SPI_CR2_SSOE | SPI_CR2_NSSP | SPI_CR2_TXDMAEN;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void spi_cmd(unsigned int data) {
    while ((SPI1->SR & SPI_SR_TXE) == 0) { }
    SPI1->DR = data;
}

void spi_data(unsigned int data) {
    spi_cmd(data | 0x200);
}

void spi1_init_oled(void) {
    nano_wait(1000000);
    spi_cmd(0x38);
    nano_wait(1000000);
    spi_cmd(0x08);
    nano_wait(1000000);
    spi_cmd(0x01);
    nano_wait(2000000);
    spi_cmd(0x06);
    nano_wait(1000000);
    spi_cmd(0x02);
    nano_wait(1000000);
    spi_cmd(0x0C);
    nano_wait(1000000);
}

void spi1_display1(const char *string) {
    spi_cmd(0x02);
    int i = 0;
    while (string[i] != '\0') {
        spi_data(string[i++]);
    }
}

void spi1_display2(const char *string) {
    spi_cmd(0xC0);
    int i = 0;
    while (string[i] != '\0') {
        spi_data(string[i++]);
    }
}

void init_display(void) {
    init_spi1();
    spi1_init_oled();
}

void update_score_display(uint16_t current, uint16_t high) {
    sprintf(highscorestring, "High Score:%d", high);
    spi1_display1(highscorestring);
    sprintf(currentscorestring, "Curr Score:%d", current);
    spi1_display2(currentscorestring);
}
