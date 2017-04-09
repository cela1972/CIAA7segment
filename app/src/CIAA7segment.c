/* Copyright (c) 2017, Carlos Eduardo López Aldana.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * =============================================================================
 *
 * Copyright (c) 2017, Carlos Eduardo López Aldana.
 * Todos los derechos reservados.
 * 
 * La redistribución y el uso en las formas de código fuente y binario, con o 
 * sin modificaciones, están permitidos siempre que se cumplan las siguientes 
 * condiciones:
 * 
 * 1. Las redistribuciones del código fuente deben conservar el aviso de
 *    copyright anterior, esta lista de condiciones y el siguiente descargo de
 *    responsabilidad.
 * 
 * 2. Las redistribuciones en formato binario deben reproducir el aviso de
 *    copyright anterior, esta lista de condiciones y el siguiente descargo de
 *    responsabilidad en la documentación y/u otros materiales suministrados 
 *    con la distribución.
 * 
 * 3. Ni el nombre de los titulares de derechos de autor ni los nombres de sus
 *    colaboradores pueden usarse para apoyar o promocionar productos 
 *    derivados de este software sin permiso específico previo y por escrito.
 * 
 * ESTE SOFTWARE SE SUMINISTRA POR LOS PROPIETARIOS DEL COPYRIGHT Y
 * COLABORADORES ''COMO ESTÁ'' Y CUALQUIER GARANTÍAS EXPRESA O IMPLÍCITA,
 * INCLUYENDO, PERO NO LIMITADO A, LAS GARANTÍAS IMPLÍCITAS DE COMERCIALIZACIÓN
 * Y APTITUD PARA UN PROPÓSITO PARTICULAR SON RECHAZADAS. EN NINGÚN CASO LOS
 * PROPIETARIOS DEL COPYRIGHT Y COLABORADORES SERÁN RESPONSABLES POR NINGÚN
 * DAÑO DIRECTO, INDIRECTO, INCIDENTAL, ESPECIAL, EJEMPLAR O COSECUENCIAL
 * (INCLUYENDO, PERO NO LIMITADO A, LA ADQUISICIÓN O SUSTITUCIÓN DE BIENES O
 * SERVICIOS; LA PÉRDIDA DE USO, DE DATOS O DE BENEFICIOS; O INTERRUPCIÓN DE LA
 * ACTIVIDAD EMPRESARIAL) O POR CUALQUIER TEORÍA DE RESPONSABILIDAD, YA SEA POR
 * CONTRATO, RESPONSABILIDAD ESTRICTA O AGRAVIO (INCLUYENDO NEGLIGENCIA O
 * CUALQUIER OTRA CAUSA) QUE SURJA DE CUALQUIER MANERA DEL USO DE ESTE SOFTWARE,
 * INCLUSO SI SE HA ADVERTIDO DE LA POSIBILIDAD DE TALES DAÑOS.
 *
 * =============================================================================
 * Fecha de creacion: 2017-04-09
 * =============================================================================
 */


/*==================[inclusiones]============================================*/

#include "CIAA7segment.h"   // <= su propio archivo de cabecera
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

// Define los pines de los segmentos del display.
#define segmento_a	GPIO0		// a
#define segmento_b	GPIO1           // b
#define segmento_c	GPIO2           // c
#define segmento_d	GPIO3           // d
#define segmento_e	GPIO4           // e
#define segmento_f	GPIO5           // f
#define segmento_g	GPIO6           // g
#define segmento_dp	GPIO7           // dp
// Define los pines que controlan cada dígito.
#define digito_u	LCD1
#define digito_d	LCD2
#define digito_c	LCD3
#define digito_um	LCD4



/*==================[definiciones de datos internos]=========================*/
uint8_t segmentosdisplayB[8] = {segmento_a, segmento_b, segmento_c, segmento_d, segmento_e, segmento_f, segmento_g, segmento_dp};

uint8_t quedisplayB[4] = {digito_u, digito_d, digito_c, digito_um};

uint8_t numeroadisplayB[10] = {
	0b11000000,	// 0
	0b11111001,	// 1
	0b10100100,	// 2
	0b10110000,	// 3
	0b10011001,	// 4
	0b10010010,	// 5
	0b10000010,	// 6
	0b11111000,	// 7
	0b10000000,	// 8
	0b10010000	// 9
};

uint8_t secuenciaB = 0;

uint16_t valorADch1W = 0;
uint8_t unidadesB = 0;
uint8_t decenasB = 0;
uint8_t centenasB = 0;
uint8_t unidadesmilB = 0;
uint8_t countproB = 0;


/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/






//*************************************************************************************************
//			Actualiza un dígito
//*************************************************************************************************
void SACANUMERO(uint8_t numero, uint8_t lcdx)
{
uint8_t i = 0;

gpioWrite (LCD1, 1);
gpioWrite (LCD2, 1);
gpioWrite (LCD3, 1);
gpioWrite (LCD4, 1);
gpioWrite (lcdx, 0);

for (i=0; i<=7; i++)
	gpioWrite (segmentosdisplayB[i], (numeroadisplayB[numero] & (1 << i)));
}
//*************************************************************************************************
//*************************************************************************************************



//*************************************************************************************************
//			Configura pines para los dígitos
//*************************************************************************************************
void CONFIGDISPLAY(void)
{

/*
uint8_t i = 0;

// Se setean los pines correspondientes a los segmentos como salida y en cero.
for (i=0; i<8; i++)
	{
	gpioConfig (segmentosdisplayB[i], GPIO_OUTPUT);
	gpioWrite (segmentosdisplayB[i], 1);
	}

// Se setean los pines correspondientes al control de los anodos común de los dígitos, en salida y cero.
for (i=0; i<4; i++)
	{
	gpioConfig (quedisplayB[i], GPIO_OUTPUT);
	gpioWrite (quedisplayB[i], 1);
	}
*/
	
gpioConfig (segmento_a, GPIO_OUTPUT);	
gpioConfig (segmento_b, GPIO_OUTPUT);	
gpioConfig (segmento_c, GPIO_OUTPUT);	
gpioConfig (segmento_d, GPIO_OUTPUT);	
gpioConfig (segmento_e, GPIO_OUTPUT);	
gpioConfig (segmento_f, GPIO_OUTPUT);	
gpioConfig (segmento_g, GPIO_OUTPUT);	
gpioConfig (segmento_dp, GPIO_OUTPUT);
gpioWrite (segmento_a, 1);	
gpioWrite (segmento_b, 1);	
gpioWrite (segmento_c, 1);	
gpioWrite (segmento_d, 1);	
gpioWrite (segmento_e, 1);	
gpioWrite (segmento_f, 1);	
gpioWrite (segmento_g, 1);	
gpioWrite (segmento_dp, 1);	

gpioConfig (digito_u, GPIO_OUTPUT);
gpioConfig (digito_d, GPIO_OUTPUT);
gpioConfig (digito_c, GPIO_OUTPUT);
gpioConfig (digito_um, GPIO_OUTPUT);
gpioWrite (digito_u, 1);
gpioWrite (digito_d, 1);
gpioWrite (digito_c, 1);
gpioWrite (digito_um, 1);
	
	
}
//*************************************************************************************************
//*************************************************************************************************


//*************************************************************************************************
//
//*************************************************************************************************
void CONVIERTEWORD(uint16_t X, uint8_t *p)
{   
if (X)
	{
	p[4] = X/10000;
	X = X%10000;
	
	p[3] = X/1000;
	X = X%1000;
	
	p[2] = X/100;
	X = X%100;
	
	p[1] = X/10;
	X = X%10;
	
	p[0] = X;
	}
else	{
	p[4] = 0;
	p[3] = 0;
	p[2] = 0;
	p[1] = 0;
	p[0] = 0;
	}
}
//*************************************************************************************************
//*************************************************************************************************



//*************************************************************************************************
//			Interrupción cada 5ms
//*************************************************************************************************
bool_t IntTimer (void *ptr)
{

uint8_t valores[5];











valorADch1W = valorADch1W + adcRead(CH1);
countproB++;
if (countproB == 64)
	{
	countproB = 0;
	valorADch1W = valorADch1W >> 6;
	CONVIERTEWORD (valorADch1W, valores);
	unidadesmilB = valores[3];
	centenasB = valores[2];
	decenasB = valores[1];
	unidadesB = valores[0];
	valorADch1W = 0;
	}







switch (secuenciaB){
	case 0:
		SACANUMERO (unidadesB, LCD1);
		secuenciaB++;
		break;
	case 1:
		SACANUMERO (decenasB, LCD2);
		secuenciaB++;
		break;
	case 2:
		SACANUMERO (centenasB, LCD3);
		secuenciaB++;
		break;
	case 3:
		SACANUMERO (unidadesmilB, LCD4);
	
	default:
		secuenciaB = 0;
		break;
	}
	

return 1;
}
//*************************************************************************************************
//*************************************************************************************************




/*==================[función principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

uint8_t i = 0;


// ---------- CONFIGURACIONES ------------------------------
// Inicializar y configurar la plataforma
boardConfig();   

// Interupcion cada 10ms.
tickConfig (5, IntTimer);

//Configura los pines que controlan los dígitos de 7 segmentos.
CONFIGDISPLAY();

//Inicializa AD.
adcConfig (ADC_ENABLE);



// ---------- REPETIR POR SIEMPRE --------------------------
while( TRUE )
{      






	
} 

// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
// directamenteno sobre un microcontroladore y no es llamado/ por ningún
// Sistema Operativo, como en el caso de un programa para PC.
return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/
