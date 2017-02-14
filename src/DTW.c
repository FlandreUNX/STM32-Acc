/*
 * DTW.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "DTW.h"

// Door Open
//float doorOpenX[35] = {8.30749989, 8.3352499, 8.35167503, 8.29717255, 8.04602051, 7.56121445, 6.89785004, 6.31349516, 5.70644665, 5.56651258, 5.56755877, 5.09729099, 4.54610348, 4.83827257, 4.9767909, 4.22775364, 2.99842763, 3.29289937, 3.64002943, 3.47202063, 2.8684144, 3.02789021, 3.36152315, 3.10306621, 2.52914643, 2.24140263, 2.12098193, 2.00368738, 1.80158114, 1.48910677, 1.06337476, 0.927362323, 1.20115364, 1.29680753, 1.06076527};
//float doorOpenY[35] = {-1.08783329, -1.25948334, -1.18463838, -1.09324682, -0.954272747, -0.871990919, -0.769393623, -0.481575549, -0.0551028848, 0.303427964, 0.707399547, 0.852179706, 0.884525776, 0.874168038, 0.875917614, 0.76914233, 0.871399641, 1.24597967, 1.19618583, 0.834330082, 0.734031081, 1.34782171, 1.28547525, 0.662832677, 0.30198288, 0.175388023, -0.0242283866, -0.313959867, -0.648771882, -0.856140316, -1.07629824, -1.13140881, -1.10698617, -1.23089027, -1.56062317};
//float doorOpenZ[35] = {5.64699984, 5.71089983, 5.61162996, 5.61414099, 5.78389883, 6.21472931, 7.09231043, 8.099617, 8.71773148, 8.84441185, 8.89408875, 9.6368618, 10.0968037, 9.73776245, 9.2584343, 9.66090393, 11.6586323, 12.1360426, 10.9882298, 9.68076134, 10.0825329, 10.9547729, 11.1843414, 10.2620392, 10.030427, 10.6512985, 11.1099091, 10.8189363, 10.2432556, 10.2002792, 10.6261959, 11.1043377, 10.950036, 10.6530256, 10.7481184};
//
//// Door Close
//float doorCloseX[35] = {1.35099995, 1.26370001, 1.54759002, 2.10631299, 2.53341913, 2.10939336, 1.79457533, 2.18320274, 2.81524181, 3.00566936, 2.75496864, 2.65747809, 2.76923466, 2.79946423, 2.57162499, 2.14513755, 2.05359626, 2.32551742, 2.83986211, 3.31990337, 4.03993225, 4.81995249, 5.42596674, 6.10817671, 6.84372377, 7.46360683, 7.56452465, 7.26616716, 6.77831697, 6.71282196, 7.46797514, 8.30858231, 8.70200729, 8.80640507, 8.90348339};
//float doorCloseY[35] = {0.714333296, 0.665033281, 1.0355233, 1.41786623, 1.60750639, 1.40125453, 1.27187824, 1.42731476, 1.84512031, 1.92458415, 2.0372088, 2.12504625, 2.11753225, 2.25927258, 2.23249078, 1.9287436, 1.77312052, 1.66418433, 1.69592905, 1.97315025, 2.17020512, 2.12814355, 1.85270047, 1.69589031, 1.68812323, 1.5956862, 1.42298031, 1.50308621, 1.48716033, 1.47001219, 1.42200851, 1.48440599, 1.45308423, 1.29015899, 1.11311126};
//float doorCloseZ[35] = {11.0828342, 10.9469843, 11.2628889, 11.4120226, 11.6874161, 11.9281912, 11.8717337, 11.3882141, 10.62675, 10.708725, 11.3361073, 11.3222752, 10.2625923, 9.86581421, 10.4280701, 10.7526493, 10.5628548, 10.0249987, 9.66349888, 10.2294493, 11.0756149, 10.8909302, 9.8196516, 8.44575596, 7.40602922, 7.05322027, 7.17525434, 8.10667801, 8.85167503, 8.46717262, 7.22002077, 6.32301474, 6.0281105, 6.09767723, 5.81337404};

float doorOpenX[36] = {-1.62216663, -1.3335166, -1.38046157, -1.82432306, -2.30902624, -2.8883183, -3.53382277, -4.01567602, -4.42797327, -4.59658146, -4.6666069, -4.44262505, -4.02183771, -3.67928648, -3.59550047, -3.52485037, -3.51439524, -3.31807661, -3.04265356, -2.81985736, -2.44190025, -1.67333019, -0.409331143, 0.55946815, 1.2136277, 1.75853944, 2.40397763, 2.93978429, 3.14984894, 3.20089412, 3.21262598, 3.09783816, 2.77148676, 2.33904076, 1.94032848, 1.57122993};
float doorOpenY[36] = {-1.22850013, -1.15995014, -1.20496511, -1.34447551, -1.38813281, -1.5146929, -1.54028499, -1.60019946, -1.55213964, -1.2964977, -1.09954834, -0.901683807, -0.736178637, -0.626325071, -0.549427569, -0.474599302, -0.404219508, -0.240953654, -0.243667558, -0.224567294, -0.166197106, -0.0473379716, 0.338863432, 0.429204404, 0.231443077, 0.0810101479, -0.0812928975, -0.23990503, -0.461933523, -0.704353452, -1.00004745, -1.15003324, -1.42602324, -1.63421619, -1.83095133, -1.9086659};
float doorOpenZ[36] = {10.2961674, 10.291317, 10.3899221, 10.3779459, 10.3095617, 10.3546934, 10.0892859, 9.97249985, 9.91174984, 9.86922455, 9.92045689, 10.0193195, 10.1605234, 10.2443666, 10.2460566, 10.4002399, 10.1691685, 9.95341778, 9.97939205, 9.98857498, 9.89000225, 9.64700127, 9.5999012, 9.61193085, 9.78535175, 10.2157459, 10.5230217, 10.6871147, 10.8709803, 11.1616859, 11.3171806, 11.213026, 11.0951185, 10.9975834, 10.8123083, 10.7156162};

float doorCloseX[36] = {1.71616673, 1.57631671, 1.36742175, 1.48819518, 2.31373644, 3.29061556, 4.04643106, 4.38050175, 4.50935125, 4.14654589, 3.66158199, 3.42110729, 3.1027751, 2.48094249, 1.82365978, 0.96456188, 0.23419331, -0.988064647, -2.32064509, -3.19045162, -3.56231618, -4.08062124, -4.68643475, -5.22450447, -5.12415314, -4.74790716, -4.40053511, -4.13337469, -3.99136233, -3.9249537, -4.33446741, -4.63612747, -4.43928909, -3.59950233, -2.60065174, -1.88345623};
float doorCloseY[36] = {-1.13750005, -1.43525004, -1.46667504, -1.3536725, -0.731570721, 0.0999004841, 0.67293036, 0.993051231, 1.07613587, 0.954295099, 0.860006571, 0.860004604, 0.716003239, 0.525202274, 0.481641591, 0.313149124, 0.162204385, -0.129456937, -0.474619836, -0.719233871, -0.818463683, -0.845924556, -0.925147176, -1.05560303, -1.25192213, -1.28134549, -1.16694188, -1.13785934, -1.09950149, -1.0996511, -1.35475576, -1.515329, -1.36073029, -1.10251117, -0.948757827, -0.88013047};
float doorCloseZ[36] = {10.5958328, 10.4140825, 10.4698582, 10.5629005, 10.9250307, 11.5055218, 12.0288649, 12.1762056, 12.0543442, 12.0800409, 11.8520288, 11.1434202, 10.3263941, 10.0844765, 9.97213364, 9.53949356, 9.30864525, 8.9460516, 9.10923576, 9.3794651, 9.25662613, 9.02063847, 9.32344723, 9.80241299, 10.0266895, 9.9706831, 10.0664778, 10.3345346, 10.5191746, 10.7354221, 10.7397957, 10.4608574, 10.2656002, 10.1589203, 10.1292439, 10.1144705};

// Light Up
float lightUpX[36] = {-0.0345000029, -0.114150003, -0.208905011, -0.200233504, -0.155163452, -0.123614416, 0.111469917, 0.444028944, 0.805820227, 1.32907414, 1.74035192, 1.67424631, 1.53497243, 1.15548074, 0.964836538, 0.900385559, 0.999269903, 1.04148889, 1.10104227, 1.04972959, 0.878810704, 0.687167466, 0.571017206, 0.399712056, 0.219798431, 0.141858906, 0.0723012313, -0.108389132, -0.207872391, -0.115510672, 0.0751425251, 0.184599772, 0.360219836, 0.354153872, 0.4399077, 0.391935378};
float lightUpY[36] = {-0.736833334, -0.740783334, -0.806548357, -0.813583851, -0.707508683, -0.50425607, -0.328979254, -0.233285472, -0.154299825, -0.0420098789, -0.227406919, -0.720184863, -1.10712945, -1.49199069, -1.96539342, -2.31477547, -2.71234274, -3.29063988, -3.78244781, -4.38171339, -5.06519938, -5.67563963, -6.17194748, -6.7233634, -7.25035429, -7.61624813, -7.98937368, -8.34956169, -8.66769314, -8.89038467, -9.01926899, -9.14248848, -9.27374172, -9.45861912, -9.53103352, -9.56372356};
float lightUpZ[36] = {11.8291674, 11.5564175, 11.5934925, 11.6494446, 12.4416113, 13.6831284, 14.7471895, 15.1020327, 15.2334232, 15.2713957, 14.8359766, 14.165184, 13.3356285, 12.54494, 11.7904577, 10.78232, 9.59962368, 8.04573631, 6.43001556, 4.65101099, 3.10570765, 2.30599546, 2.04919672, 1.56043768, 0.699306369, 0.00951445103, -0.449339867, -0.686537921, -0.864576519, -1.07320356, -1.00324249, -0.732269764, -0.548588812, -0.234012172, -0.0258085169, 0.347934037};

// Light Down
float lightDownX[39] = {1.49216676, 1.51851678, 1.5579617, 1.64857316, 1.57100117, 1.34270084, 1.20389056, 1.31372344, 1.60960639, 1.69372451, 1.50360715, 1.40052497, 1.91936755, 2.08155727, 2.14409018, 1.94486308, 1.28940415, 0.881582916, 1.1271081, 1.22097564, 1.2776829, 1.29637802, 0.991464615, 1.20402527, 1.50281775, 1.37897241, 1.31928062, 1.39449644, 1.83114743, 1.72280324, 1.77596223, 1.78317356, 1.86322153, 2.09625506, 2.29837847, 2.3948648, 2.29740524, 2.27718377, 2.28102875};
float lightDownY[39] = {-9.08133316, -9.17093277, -9.19765282, -9.16235733, -8.8916502, -8.50715542, -8.13300896, -7.63710642, -7.43097448, -7.38268232, -7.17487764, -7.03241444, -6.91469002, -6.74528313, -6.63269806, -6.31388855, -6.22272205, -6.11690521, -5.66783381, -5.53948355, -5.46463871, -5.14824724, -4.86077309, -4.53954124, -4.26067877, -3.97847509, -3.66393256, -3.4347527, -3.40032697, -3.12122893, -2.94386029, -2.69970226, -2.65779161, -2.65245414, -2.61271787, -2.55790257, -2.47153187, -2.53107238, -2.52175069};
float lightDownZ[39] = {2.65483332, 2.29338336, 2.30436826, 2.57005787, 2.93304062, 3.61912847, 4.52538967, 4.88377285, 4.72064114, 4.36944866, 3.94361401, 3.63952971, 2.71867085, 1.83106959, 0.198748738, -1.95787585, -4.001513, -5.21005917, -6.43104124, -7.71172905, -8.63220978, -9.38454723, -9.78518295, -10.6116276, -11.1781397, -11.0646982, -10.7902889, -11.1232023, -11.5812416, -11.6138687, -11.3877077, -11.2623959, -11.2286768, -11.2020741, -11.021452, -10.7450161, -10.5185108, -10.2909575, -10.16467};

float min(float a, float b) {
	return a < b ? a : b;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float minArray(float *array, int begin, int end) {
	float min = array[begin];
	for (int i = begin + 1; i < end; i++) {
		if(array[i] < min) { min = array[i]; }
	}
	return min;
}

float maxArray(float *array, int begin, int end) {
	double max = array[begin];
	for (int i = begin + 1; i < end; i++) {
		if(array[i] > max) { max = array[i]; }
	}
	return max;
}

float average(float *array, int begin, int end) {
	float sum = 0;
	int i;
	for(i = begin; i < end; i++) {
		sum += array[i];
	}
	return sum / (float) (end - begin);
}

void ewma(float *array, int size, float *result) {

	int s = size < 6 ? size : 6;
	float forecasted = average(array, 0, s);
	float smoothed = 0;

	int i;

	for (i = 1; i <= size; i++) {
		smoothed = EWMA_ALPHA * array[i - 1] + (1.0 - EWMA_ALPHA) * forecasted;
		forecasted = smoothed;
		result[i - 1] = smoothed;
	}

}

double dtwDistance1(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int window) {

	float acc[sb][sa];
	float dist;

	acc[0][0] = pow(ax[0] - bx[0], 2.0) + pow(ay[0] - by[0], 2.0) + pow(az[0] - bz[0], 2.0);

	// Accumulated distance - Row 0
	for (int i = 1; i < sa; i++) {
		dist = pow(ax[i] - bx[0], 2.0) + pow(ay[i] - by[0], 2.0) + pow(az[i] - bz[0], 2.0);
		acc[0][i] = acc[0][i - 1] + dist;
	}

	// Accumulated distance - Row 0
	for (int i = 1; i < sb; i++) {
		dist = pow(ax[0] - bx[i], 2.0) + pow(ay[0] - by[i], 2.0) + pow(az[0] - bz[i], 2.0);
		acc[i][0] = acc[i - 1][0] + dist;
	}

	// Accumlated distance - Remaining
	float m;
	for (int i = 1; i < sb; i++) {
		for (int j = 1; j < sa; j++) {
			dist = pow(ax[j] - bx[i], 2.0) + pow(ay[j] - by[i], 2.0) + pow(az[j] - bz[i], 2.0);
			m = min(min(acc[i - 1][j - 1],
					acc[i - 1][j]),
					acc[i][j - 1]);
			acc[i][j] = m + dist;
		}
	}

	return sqrt(acc[sb - 1][sa - 1]);

}

float dtwDistance(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int window) {

	float acc[sa][sb];
	float dist;
	int maxi, mini;
	window = max(window, abs(sa - sb));

	// Temp
	for (int i = 0; i < sa; i++) {
		for (int j = 0; j < sb; j++) {
			acc[i][j] = INFINITY;
		}
	}

	acc[0][0] = pow(ax[0] - bx[0], 2.0) + pow(ay[0] - by[0], 2.0) + pow(az[0] - bz[0], 2.0);

	// Row 0
	mini = min(window, sb);
	for (int i = 1; i < mini; i++) {
		dist = pow(ax[0] - bx[i], 2.0) + pow(ay[0] - by[i], 2.0) + pow(az[0] - bz[i], 2.0);
		acc[0][i] = acc[0][i - 1] + dist;
	}

	// Column 0
	mini = min(window, sa);
	for (int i = 1; i < mini + 1; i++) {
		dist = pow(ax[i] - bx[0], 2.0) + pow(ay[i] - by[0], 2.0) + pow(az[i] - bz[0], 2.0);
		acc[i][0] = acc[i - 1][0] + dist;
	}

	// Accumlated distance - Remaining
	float m;
	for (int i = 1; i < sa; i++) {
		mini = max(1, i - window);
		maxi = min(sb, i + window);
		for (int j = mini; j < maxi; j++) {
			dist = pow(ax[i] - bx[j], 2.0) + pow(ay[i] - by[j], 2.0) + pow(az[i] - bz[j], 2.0);
			m = min(
					min(acc[i - 1][j],
							acc[i][j - 1]),
							acc[i - 1][j - 1]);
			acc[i][j] = m + dist;
		}
	}

	return sqrt(acc[sa - 1][sb - 1]);

}

float LBKeogh(float *x, int sx, float *y, int sy, int r) {

	double sum = 0;
	int li, mi;
	double lowerBound, upperBound;

	for (int i = 0; i < sx; i++) {

		li = (i - r) >= 0 ? (i - r) : 0;
		mi = (i + r) <= sy ? (i + r) : sy;

		lowerBound = minArray(y, li, mi);
		upperBound = maxArray(y, li, mi);

		if(x[i] > upperBound) {
			sum += pow(x[i] - upperBound, 2);
		} else if(x[i] < lowerBound) {
			sum += pow(x[i] - lowerBound, 2);
		}

	}

	return sqrt(sum);
}

float LBKeogh3D(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int r) {
	float lx = LBKeogh(ax, sa, bx, sb, r);
	float ly = LBKeogh(ay, sa, by, sb, r);
	float lz = LBKeogh(az, sa, bz, sb, r);
	return lx + ly + lz;
}

int knn(float inputX[], float inputY[], float inputZ[], int size, float *dist) {

	int answer;
	float distance = INFINITY;
	float minDistance = INFINITY;
	int lbr = 30;

	float* pointersX[NUMBER_OF_GESTURES] = {doorOpenX, doorCloseX, lightUpX, lightDownX};
	float* pointersY[NUMBER_OF_GESTURES] = {doorOpenY, doorCloseY, lightUpY, lightDownY};
	float* pointersZ[NUMBER_OF_GESTURES] = {doorOpenZ, doorCloseZ, lightUpZ, lightDownZ};

	int sizes[NUMBER_OF_GESTURES] = {36, 36, 36, 39};
	int window = 4; // Does not matter for DTW1

	for(int i = 0; i < NUMBER_OF_GESTURES; i++) {
		if(LBKeogh3D(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], lbr) < minDistance) {
			distance = dtwDistance1(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], window);
			if(distance < minDistance) {
				minDistance = distance;
				answer = i;
			}
		}
	}

	*dist = minDistance;

	return answer;

}
