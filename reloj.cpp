#include <allegro.h>
#include <math.h>
#include <time.h>

/* Funciones utilizadas */
void Inicializar_Variables();
void Inicializar_Funciones();
int Inicializar_Graficos(int ancho, int alto);
void Dibujar_Reloj(int x, int y, int radio, int grados, int grados2, int grados3);
void Tiempo(int segundos, int minutos, int horas, int* grados, int* grados2, int* grados3);

/* Variables globales */

void Inicializar_Variables()
{
}

void Inicializar_Funciones()
{
	allegro_init();
	install_keyboard();
}

/* Devuelve 0 si no hay error al inicializar los graficos */
int Inicializar_Graficos(int ancho, int alto)
{
	if(set_gfx_mode(GFX_SAFE, ancho, alto, 0, 0) != 0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("No se ha logrado entrar a modo grafico\n%s\n", allegro_error);
		return 1;
	}
	return 0;
}

void Dibujar_Reloj(int x, int y, int radio, int grados, int grados2, int grados3)
{
	int h = radio - 20, h2 = radio - 40, h3 = radio - 55;
	int x2 = h*cos(grados*(M_PI/180)), y2 = h*sin(grados*(M_PI/180)); /* segundero */ 
	int x22 = h2*cos(grados2*(M_PI/180)), y22 = h2*sin(grados2*(M_PI/180)); /* minutero */
	int x222 = h3*cos(grados3*(M_PI/180)), y222 = h3*sin(grados3*(M_PI/180)); /* hora */ 
	
	clear_bitmap(screen); 
	text_mode(-1);
	circlefill(screen, x, y, radio, palette_color[5]);
	line(screen, x, y, x+x2, y+y2, palette_color[15]); 
	line(screen, x, y, x+x22, y+y22, palette_color[15]);
	line(screen, x, y, x+x222, y+y222, palette_color[15]); 
	textout(screen, font, "12", x-5, (y-radio)+5, palette_color[15]);
	textout(screen, font, "3", (x+radio)-10, y-2, palette_color[15]); 
	textout(screen, font, "6", x-2, (y+radio)-10, palette_color[15]); 
	textout(screen, font, "9", (x-radio)+10, y-2, palette_color[15]); 
}

void Tiempo(int segundos, int minutos, int horas, int* grados, int* grados2, int* grados3)
{
	int auxiliar; 
	
	auxiliar = (segundos-15)*6; 
	if(auxiliar <= 0)
	*grados = auxiliar+360;
	else
	*grados = auxiliar;
	
	auxiliar = (minutos-15)*6;
	if(auxiliar <= 0)
	*grados2 = auxiliar+360; 
	else
	*grados2 = auxiliar;
	
	auxiliar = (horas-15)*6;
	if(auxiliar <= 0)
	*grados3 = auxiliar+360; 
	else
	*grados3 = auxiliar; 
}

void Obtener_Hora(int *segundos, int *minutos, int *horas)
{
	time_t tSac = time(NULL); // instante actual
	
	struct tm* pt1 = localtime(&tSac);
	
	tm tm2 = *gmtime(&tSac); // deferencia y asignación 
	
	*segundos = tm2.tm_sec;
	*minutos = tm2.tm_min;
	*horas = ((tm2.tm_hour+1)-12)*5;
}

int main()
{
	int minutos = 0, segundos = 0, horas = 0, grados = 0, grados2 = 0, grados3 = 0;
	
	Inicializar_Variables();
	Inicializar_Funciones();
	Inicializar_Graficos(500, 500); 
	
	do
	{
		Obtener_Hora(&segundos, &minutos, &horas); 
		Tiempo(segundos, minutos, horas, &grados, &grados2, &grados3);
		Dibujar_Reloj(250, 250, 100, grados, grados2, grados3);
		rest(100); 
	}while(keypressed() == 0);
}
END_OF_MAIN();
