/* Victor Bonesi
 * 12/01/2017
 * FATEC São Bernardo do Campo
 * lcd.h
 * Biblioteca para LCD de caractere até 4 linhas para PIC (XC8)
 * 
 * Comandos:
 * *Lcd_Posicao(y, x)
 * *Lcd_Inicializa()
 * *Escreve_Char_Lcd(char a) Escreve apenas um caractere da tabela ASCII ou Caracter Especial:
 *			-('1') Caractere da tabela ASCII "1"
			-  (1) Caractere especial da rotina charesp[] numeo #1
 * *Escreve_String_Lcd(char *a) Escreve uma string com caracteres da tabela ACII
 * *Lcd_LD_Cursor (unsigned char config)
 *         -0 - Desliga o cursor.
 *         -1 - Liga o cursor.
 *         -2 - Liga o cursor piscando.
 * *Lcd_Shift_Direita()
 * *Lcd_Shift_Esquerda()
 * *Inicio_Lcd()  Volta para a posição de incio do LCD 
 */

/*////////////////////////////////////////////////////////////////////////
/*Rotina para criar caracteres especiais
 * Maximo de 64 caracteres
 * Matriz 5*8
 ///////////////////////////////////////////////////////////////////////*/
const unsigned short charesp[] = {
  0x00, 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, //Caractere #0
  0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00, //Caractere #1
  0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00, //Caractere #2
  0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00, //Caractere #3
  0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, //Caractere #4
  0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, //Caractere #5
  0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00, //Caractere #6
  0x00, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x1B, 0x00  //Caractere #7
};
/*//////////////////////////////////////////////////////////////////////*/

//Rotina de Tempo
void Atraso_ms(unsigned char g)
{   
    volatile unsigned int h;
    for(h=0;h<g;h++)
    {
      __delay_ms(1);  
    }
}

//Configuração dos bits
void Lcd_Port(unsigned char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}

//Escreve um caractere
void Escreve_Char_Lcd(unsigned char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;            
   Lcd_Port(y>>4);     //Trasnfere dados
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

//Rotina de comando
void Comando_Lcd(unsigned char a)
{
	RS = 0;           
	Lcd_Port(a);
	EN  = 1;         
    __delay_ms(4);
    EN  = 0;
}

//Grava os Caracteres especiais
void CustomChar()
{
  char v;
  Comando_Lcd(0x04);   //seleciona o endereço da CGRAM
  Comando_Lcd(0x00);   //seleciona o endereço da CGRAM
  for (v = 0; v <= 63 ; v++)
    Escreve_Char_Lcd(charesp[v]);
  Comando_Lcd(0x00);      //Volta para posição Home
  Comando_Lcd(0x02);      //Volta para posição Home
}

//Limpa Display
void Limpa_Lcd()
{
	Comando_Lcd(0x00);
	Comando_Lcd(0x01);
}

//Seta cursor em uma posição (y,x) do display
void Lcd_Posicao(char y, char x)
{
	char temp,z,w;
	if(y == 1)
	{
        temp = 0x80 + x - 1;
        z = temp>>4;
        w = temp & 0x0F;
        Comando_Lcd(z);
        Comando_Lcd(w);
	}
	else if(y == 2)
	{
		temp = 0xC0 + x - 1;
		z = temp>>4;
		w = temp & 0x0F;
		Comando_Lcd(z);
		Comando_Lcd(w);
	}
		if(y == 3)
	{
        temp = 0x94 + x - 1;
        z = temp>>4;
        w = temp & 0x0F;
        Comando_Lcd(z);
        Comando_Lcd(w);
	}
	else if(y == 4)
	{
		temp = 0xD4 + x - 1;
		z = temp>>4;
		w = temp & 0x0F;
		Comando_Lcd(z);
		Comando_Lcd(w);
	}
}

//inicializa o display
void Lcd_Inicializa()
{
  Lcd_Port(0x00);
  Atraso_ms(20);
  Comando_Lcd(0x03);
  Atraso_ms(5);
  Comando_Lcd(0x03);
  Atraso_ms(11);
  Comando_Lcd(0x03);

  Comando_Lcd(0x02);
  Comando_Lcd(0x02);
  Comando_Lcd(0x08);
  Comando_Lcd(0x00);
  Comando_Lcd(0x0C);
  Comando_Lcd(0x00);
  Comando_Lcd(0x06);
  Atraso_ms(10);
  CustomChar();
}

//Escreve uma string
void Escreve_String_Lcd(unsigned char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Escreve_Char_Lcd(a[i]);
}

//Pula um caratere para direita
void Lcd_Shift_Direita()
{
	Comando_Lcd(0x01);
	Comando_Lcd(0x0C);
}

//Pula um caractere para esquerda
void Lcd_Shift_Esquerda()
{
	Comando_Lcd(0x01);
	Comando_Lcd(0x08);
}

//Liga/Desliga o cursor/display.
void Lcd_LD_Cursor (unsigned char config)
{
/*
0 - Desliga o cursor.
1 - Liga o display e o cursor.
2 - Liga o display e o cursor piscante.
*/
unsigned char cursor [3] = {0x0C, 0x0E, 0x0D}; 
   Comando_Lcd(0);
   Comando_Lcd(cursor[config]);
}

//Psição 1 do display
void Inicio_Lcd()
{
	Lcd_Posicao(1,1);
}

