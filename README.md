# lcd-PIC-XC8

/* Victor Bonesi
 * 12/01/2016
 * FATEC São Bernardo do Campo
 * lcd.h
 * Biblioteca para LCD de caractere até 4 linhas para PIC (XC8)
 * 
 * Comandos:
 *   Lcd_Posicao(y, x) maximo de 4 linhas
 *   Lcd_Inicializa()
 *   Escreve_Char_Lcd(char a) Escreve apenas um caractere da tabela ASCII
 *   Escreve_String_Lcd(char *a) Escreve uma string com caracteres da tabela ACII
 *   Lcd_LD_Cursor (unsigned char config)
 *          -0 - Desliga o cursor.
 *          -1 - Liga o cursor.
 *          -2 - Liga o cursor piscando.
 *   Lcd_Shift_Direita()
 *   Lcd_Shift_Esquerda()
 *   Inicio_Lcd()  Volta para a posição de incio do LCD
 *
 * Em (lcd.h) pode ser adicionado até 64 caracteres especiais na rotina: const unsigned short charesp[] = {} 
 *
