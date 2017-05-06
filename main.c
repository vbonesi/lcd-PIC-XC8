#define RS PORTDbits.RD1
#define EN PORTDbits.RD0
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

#include "config.h";
#include "lcd.h";

int main()
{
  unsigned int a;
  TRISD = 0x00;
  Lcd_Inicializa();
  while(1)
  {
    Limpa_Lcd();
    Inicio_Lcd();
    Escreve_String_Lcd(" AGTechnologies ");
    Lcd_Posicao(2,1);
    Escreve_String_Lcd("Displays de LCDs");
    Tempo_ms(2000);
    Limpa_Lcd();
    Inicio_Lcd();
    Escreve_String_Lcd("Desenvolvido por");
    Lcd_Posicao(2,1);
    Escreve_String_Lcd(" AGTechnologies ");
    Tempo_ms(2000);
    Limpa_Lcd();
    Inicio_Lcd();
    Escreve_String_Lcd("  www.agte.com.br");
    Lcd_Posicao(2,1);
    Escreve_String_Lcd("  projetos@agte.com.br");

    for(a=0;a<17;a++)
    {
        Tempo_ms(300);
        Lcd_Shift_Esquerda();
    }

    for(a=0;a<20;a++)
    {
        Tempo_ms(300);
        Lcd_Shift_Direita();
    }

    Limpa_Lcd();
    Inicio_Lcd();
    Lcd_LD_Cursor(1);
    Tempo_ms(2000);
    Lcd_LD_Cursor(2);
    Tempo_ms(2000);
    Lcd_LD_Cursor(0);
    Limpa_Lcd();
    Inicio_Lcd();
    Escreve_Char_Lcd('A');
    Escreve_Char_Lcd('G');
    Escreve_Char_Lcd('T');
    Lcd_Posicao(1,5);
    Escreve_Char_Lcd(0);
    Escreve_Char_Lcd(1);
    Escreve_Char_Lcd(2);
    Escreve_Char_Lcd(3);
    Escreve_Char_Lcd(4);
    Escreve_Char_Lcd(5);
    Escreve_Char_Lcd(6);
    Escreve_Char_Lcd(7);
    Tempo_ms(2000);
    
  }
  return 0;
}