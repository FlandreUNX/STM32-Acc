/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include <stdio.h>
#include <string.h>
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "TestSeries.h"
#include "DTW.h"
#include "LinkedList.h"
#include "serial.h"
#include "time.h"

void setup();
void testTimeOfDTW();
void recognizeGesture(LinkedList *signalX, LinkedList *signalY, LinkedList *signalZ, int size);
float variance(float *array, int begin, int end);

int main(void) {

	setup();

	int count = 0;

	// Signals
	LinkedList *signalX = newLinkedList();
	LinkedList *signalY = newLinkedList();
	LinkedList *signalZ = newLinkedList();

	// Struct for holding the accelerometer data
	TM_LIS302DL_LIS3DSH_t Axes_Data;

	float x, y, z;
	float ax[AVG_SIZE], ay[AVG_SIZE], az[AVG_SIZE];
	float ex[SIZE], ey[SIZE], ez[SIZE];
	float vx[SIZE], vy[SIZE], vz[SIZE];
	int moving = 0;

	float fx, fy, fz;
	float fvx, fvy, fvz;

	fvx = 1;
	fvy = 1;
	fvz = 1;

	int v = 0;

	// Getting values for the initial average
	for(int i = 0; i < AVG_SIZE; i++) {
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		ax[i] = (float) Axes_Data.X;
		ay[i] = (float) Axes_Data.Y;
		az[i] = (float) Axes_Data.Z;
		Delayms(SAMPLEPERIOD);
	}

	// Calculating the average
	fx = average(ax, 0, AVG_SIZE);
	fy = average(ay, 0, AVG_SIZE);
	fz = average(az, 0, AVG_SIZE);

	while(1) {

		// Getting accelerometer values
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);

		x = (float) Axes_Data.X;
		y = (float) Axes_Data.Y;
		z = (float) Axes_Data.Z;

		Delayms(SAMPLEPERIOD);

		// Calculating EWMA
		ex[v] = EWMA_ALPHA * x + (1.0 - EWMA_ALPHA) * fx;
		fx = ex[v];
		ey[v] = EWMA_ALPHA * y + (1.0 - EWMA_ALPHA) * fy;
		fy = ey[v];
		ez[v] = EWMA_ALPHA * z + (1.0 - EWMA_ALPHA) * fz;
		fz = ez[v];

		// Calculating variance
		vx[v] = variance(ex, 0, v + 1);
		vy[v] = variance(ey, 0, v + 1);
		vz[v] = variance(ez, 0, v + 1);

		// Calculating EWMA for variance
		vx[v] = EWMA_ALPHA * vx[v] + (1.0 - EWMA_ALPHA) * fvx;
		fvx = vx[v];
		vy[v] = EWMA_ALPHA * vy[v] + (1.0 - EWMA_ALPHA) * fvy;
		fvy = vy[v];
		vz[v] = EWMA_ALPHA * vz[v] + (1.0 - EWMA_ALPHA) * fvz;
		fvz = vz[v];

		// Filled up the arrays
		if((v + 1) < SIZE) {
			v++;
		} else {

			// Checking movement
			moving = (vx[v] > OFFSET) || (vy[v] > OFFSET) || (vz[v] > OFFSET);
			if(moving) {
				prependToLinkedList(signalX, ex[v] / ACCELEROMETER_DATA_DIVIDER);
				prependToLinkedList(signalY, ey[v] / ACCELEROMETER_DATA_DIVIDER);
				prependToLinkedList(signalZ, ez[v] / ACCELEROMETER_DATA_DIVIDER);
				count++;
				//				TM_DISCO_LedOn(LED_GREEN);
			} else {
				if(count >= MIN_SAMPLES && count <= MAX_SAMPLES) {
					recognizeGesture(signalX, signalY, signalZ, count);
				}
				if(count > 0) {
					freeLinkedList(signalX);
					freeLinkedList(signalY);
					freeLinkedList(signalZ);
					count = 0;
					//					TM_DISCO_LedOff(LED_GREEN);
				}
			}

			// Pushing guys left
			for(int i = 1; i < SIZE; i++) {
				ex[i - 1] = ex[i];
				ey[i - 1] = ey[i];
				ez[i - 1] = ez[i];
				vx[i - 1] = vx[i];
				vy[i - 1] = vy[i];
				vz[i - 1] = vz[i];
			}

		}

	}

}

void recognizeGesture(LinkedList *signalX, LinkedList *signalY, LinkedList *signalZ, int size) {

	// Allocating arrays for the smoothed signals
	float x[size], y[size], z[size];
	float dist;
	int klass;

	// Filling up the temporary raw signal arrays
	arrayFromLinkedList(signalX, x, size);
	arrayFromLinkedList(signalY, y, size);
	arrayFromLinkedList(signalZ, z, size);

	klass = knn(x, y, z, size, &dist);

	char str[10];
	sprintf(str, "%i", (int) dist);
	USART_puts(USART1, str);

	// Checking for NaN and long distances
	if(klass != klass) {
		return;
	}

	if(klass < 2 && dist > MAX_DISTANCE_DOOR) {
		return;
	} else if(klass >= 2 && dist > MAX_DISTANCE_LIGHT) {
		return;
	}

	if(klass == 0) { // Door Open
		TM_DISCO_LedOn(LED_RED);
		//			USART_puts(USART1, "0");
	} else if(klass == 1) { // Door Close
		TM_DISCO_LedOn(LED_GREEN);
		//			USART_puts(USART1, "1");
	} else if(klass == 2) { // Light Up
		TM_DISCO_LedOn(LED_ORANGE);
		//			USART_puts(USART1, "2");
	} else if(klass == 3) { // Light Down
		TM_DISCO_LedOn(LED_BLUE);
		//			USART_puts(USART1, "3");
	}

	Delayms(100);
	TM_DISCO_LedOff(LED_GREEN | LED_RED | LED_ORANGE | LED_BLUE);

}

float variance(float *array, int begin, int end) {
	float avg = average(array, begin, end);
	float sum = 0.0;
	for(int i = begin; i < end; i++) {
		sum += pow(array[i] - avg, 2.0);
	}
	return sum / ((end - begin)) ;
}

void setup() {
	SystemInit();
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_50Hz);
	TM_DISCO_ButtonInit();
	init_USART1(9600);
}

void testTimeOfDTW() {
	int ms[121];
	for(int l = 0; l <= 120; l++) {
		TM_DELAY_SetTime(0);
		//		dtwDistance(ts1, ts1, ts1, l+50, ts2, ts2, ts2, l+50, (l + 50) * DTW_WINDOW_RATIO);
		//		knn(ts1, ts2, ts3, l + 30);
		ms[l] = TM_DELAY_Time();
	}
	ms[0] += 0; // Just to avoid the unused warning
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	/* TODO, implement your code here */
	return -1;
}
