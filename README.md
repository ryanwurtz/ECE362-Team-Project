Project Description: Project Description: We want to recreate a game called 1010! which consists of a 10 by 10 grid where randomly generated blocks, similar to Tetris, are inserted into the grid. When the blocks span a row or column, the line is cleared. The game ends when there are no more valid places to place a block.

Ryan: An ability to use SPI to display the 10x10 game grid and the (random) next pieces to choose from on the TFT display in our kit.
Karthik: An ability to use SPI to display the high score and current game score on the OLED LCD display in our kit.
Evan: An ability to use timer 7 and its ISR to read buttons from the keypad (interfacing with GPIO port C) in our kit. Different buttons will be able to: move the selected block on the grid similar to arrow keys, confirm block placement, and pick between the three presented block choices.
Nathanael: An ability to use the STM32 DAC to emit a sound (buzz, ding, etc.) when a line is completed through the TRRS jack in our kit and a pair of headphones.


Main Features: Main Features:
OLED and TFT displays, TRRS Jack, Keypad, Timer 7, several GPIO ports, SPI


External Interfaces: undefined


Internal Peripherals: undefined


Timeline: February 28th: Develop the game logic for 1010! in C March 17th: The OLED screen should be able to display high score and current score and be able to overwrite the high score if a new one is reached.
March 31st: Have the random block generator and three buttons to select between them functioning.
April 14th: Have the TFT display properly displaying the 10x10 grid and the three blocks to be selected from.
April 21st: Have the “arrow key” buttons and the placement confirmation button functioning. The game should be fully playable at this point.
April 28th: Be able to play the sound when a row/column is eliminated and hear it from the TRRS jack.
April 30: Be able to deliver the project fully.


Related Projects: Similar Project: (playing a game with the keypad buttons, shown on the TFT display.
https://nam04.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DzaHAUm3c9b4%26t%3D3s&data=05%7C02%7Crwurtz%40purdue.edu%7Cb3b6c054464f45e5d28908dd55e9f587%7C4130bd397c53419cb1e58758d6d63f21%7C0%7C0%7C638761185546047796%7CUnknown%7CTWFpbGZsb3d8eyJFbXB0eU1hcGkiOnRydWUsIlYiOiIwLjAuMDAwMCIsIlAiOiJXaW4zMiIsIkFOIjoiTWFpbCIsIldUIjoyfQ%3D%3D%7C0%7C%7C%7C&sdata=kwfdFfqLIjWqdowosuuuV2naAB%2BRt1S7AtEyWj7wn7E%3D&reserved=0.

1010! Gameplay:
https://nam04.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3D4ZUrKsAWrHo%26ab_channel%3Dhotcyder&data=05%7C02%7Crwurtz%40purdue.edu%7Cb3b6c054464f45e5d28908dd55e9f587%7C4130bd397c53419cb1e58758d6d63f21%7C0%7C0%7C638761185546080019%7CUnknown%7CTWFpbGZsb3d8eyJFbXB0eU1hcGkiOnRydWUsIlYiOiIwLjAuMDAwMCIsIlAiOiJXaW4zMiIsIkFOIjoiTWFpbCIsIldUIjoyfQ%3D%3D%7C0%7C%7C%7C&sdata=Q1gvlCqNXOkpv191axm%2FTp%2B6ZNpqhmoNDASurL4vWW0%3D&reserved=0

I would say that we are making a combination of the battleship project mentioned above and the online version of 1010!; we aren't "improving" the game per se but instead remaking it in a different medium.
