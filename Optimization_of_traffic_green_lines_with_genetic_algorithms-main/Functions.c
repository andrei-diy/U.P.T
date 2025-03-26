#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G_NUMBER_OF_NODES 12
#define G_NUMBER_OF_SOLUTIONS 1000
#define G_NUMBER_OF_PARENTS 1

int g_startDelay_ms     =   2000;
int g_debounceDelay_ms  =   1000;
int g_CarLength		    =   5;
int g_LaneObjOffset		=   5;
int g_cruiseSpeed_kh    =   50;          // 50kh ----- 13.8ms -> a = 1.9ms2
int g_cruiseHyst_ms     =   7000;
int g_timeToCross		=	3000;
typedef struct {
    int nodeA;
    int nodeB;
    int distance;
    int lanes;
    int offset_ms;
    int additionalDelay_ms;
	int greenLightTimeout;
}NodeS;
NodeS Template[G_NUMBER_OF_NODES];
NodeS Table[G_NUMBER_OF_SOLUTIONS][G_NUMBER_OF_NODES];
NodeS Parents[G_NUMBER_OF_PARENTS][G_NUMBER_OF_NODES];
//  A ---> B
//  a = v / t
//  v = v_ + a*t
//	x = x_ + v_*t + (a*t^2)/2
//	x = x_ + v*dt
//  v^2 = v_^2 + 2a*dx

int random_generator(int start_value, int stop_value) 
{ 
    int interval = (stop_value - start_value) + 1; 
    return start_value + (rand() % interval);
} 
int compare(const void* a, const void* b)
{
    return (*(int*)b - *(int*)a);
}
void copy_solution(NodeS src[G_NUMBER_OF_SOLUTIONS][G_NUMBER_OF_NODES], NodeS dst[G_NUMBER_OF_NODES], int idx)
{
	for (int i = 0; i < G_NUMBER_OF_NODES; i++)
	{
		dst[i]=src[idx][i];
	}
}
int fitnessNode(NodeS individ)
{	
	float NrOfCars, UtilTime;

	NrOfCars = individ.lanes * g_LaneObjOffset;
	UtilTime = individ.greenLightTimeout*1000 - g_startDelay_ms - (g_debounceDelay_ms * g_LaneObjOffset) - g_cruiseHyst_ms + individ.additionalDelay_ms;
	return NrOfCars + ((UtilTime / g_timeToCross) * individ.lanes);
}
int fitnessSolution(NodeS solutie[G_NUMBER_OF_NODES])
{	
	int minFit=9999;
	for(int i=0;i<G_NUMBER_OF_NODES;i++)
	{
		if(fitnessNode(solutie[i]) < minFit) 
		{
			minFit = fitnessNode(solutie[i]);
		}
	}
	return minFit;
}
int delay_Nodes_ms(NodeS ab)
 {
	int tCruise, tConstCruise_ms, tLaneClear_ms, dCruise;
	float cruiseAcc_MS2, cruiseSpeed_MS,tDistance_ms;
	float tLastCarClear = 0;
	
	tCruise = g_cruiseHyst_ms / 1000;
	//printf("tCruise = %d\n",tCruise);
	cruiseSpeed_MS = g_cruiseSpeed_kh /3.6;
	//printf("CruiseSpeed = %f\n",cruiseSpeed_MS);
	cruiseAcc_MS2 = cruiseSpeed_MS / tCruise;
	//printf("cruiseAcc_MS2 = %f\sn",cruiseAcc_MS2);
	dCruise = (cruiseSpeed_MS * tCruise) / 2;
	//printf(" cruise distance %d\n",dCruise); 
	if(ab.distance >= dCruise)
	{
		tConstCruise_ms = ((ab.distance - dCruise) / cruiseSpeed_MS) * 1000;
		//printf("tConstCruise_ms = %d\n",tConstCruise_ms);
		if( dCruise < (g_LaneObjOffset * g_CarLength) )
			{	
				tLastCarClear = (((g_LaneObjOffset  * g_CarLength) - dCruise)/(cruiseSpeed_MS));
				tLastCarClear += tCruise;
				//printf(" cruise < distance => tLastCarClear = %f\n",tLastCarClear);
			}else
			{
				tLastCarClear = tCruise - ((dCruise - (g_LaneObjOffset * g_CarLength)) / cruiseSpeed_MS);
				//printf(" cruise > distance => tLastCarClear = %f\n",tLastCarClear);
			}
		tLaneClear_ms = g_startDelay_ms + (g_LaneObjOffset * g_debounceDelay_ms) + (tLastCarClear * 1000);
		//printf("(g_LaneObjOffset * g_CarLength) = %d\n",(g_LaneObjOffset * g_CarLength));
		//printf("LaneCarClear = %d\n",tLaneClear_ms);
		return g_cruiseHyst_ms + tConstCruise_ms - tLaneClear_ms;
	}else
	{
		tDistance_ms = sqrt((2*ab.distance / cruiseAcc_MS2)) * 1000;
		//printf("tLaneDistance = %f\n",tDistance_ms);
		tLaneClear_ms = g_startDelay_ms + (g_LaneObjOffset * g_debounceDelay_ms) + (tCruise * 1000);
		//printf("LaneCarClear = %d\n",tLaneClear_ms);
		return tDistance_ms - tLaneClear_ms;
	}
}
void init_nodes(NodeS *individ)
{
	for(int i=0; i<G_NUMBER_OF_NODES; i++)
	{
		individ[i].offset_ms = delay_Nodes_ms(individ[i]);
	}
}
void generate_solutions()
{
	for(int i=0;i<G_NUMBER_OF_SOLUTIONS;i++)
	{
		for(int j=0;j<G_NUMBER_OF_NODES;j++)
		{
			Table[i][j].nodeA = Template[j].nodeA;
			Table[i][j].nodeB = Template[j].nodeB;
			Table[i][j].distance = Template[j].distance;
			Table[i][j].lanes = Template[j].lanes;
			Table[i][j].offset_ms = delay_Nodes_ms(Template[j]);
			Table[i][j].additionalDelay_ms = random_generator(0,5000);
			Table[i][j].greenLightTimeout = Template[j].greenLightTimeout;
		}
	}
}
void evaluate_solutions(NodeS table[G_NUMBER_OF_SOLUTIONS][G_NUMBER_OF_NODES], int fit[G_NUMBER_OF_NODES])
{
	//printf("%d %d %d %d %d %d %d %d %d\n",fit[0],fit[1],fit[2],fit[3],fit[4],fit[5],fit[6],fit[7],fit[8]);
	for(int i=0; i<G_NUMBER_OF_SOLUTIONS; i++)
	{
		//printf("i=%d\n",i);
		NodeS buff[G_NUMBER_OF_NODES];
		copy_solution(table,buff,i);
		fit[i] = fitnessSolution(buff);
		//printf("a %d %d %d\n",buff[0].nodeB,buff[0].distance,buff[0].lanes);
		//printf("b %d %d \n",fit[i],fitnessSolution(buff));
		//printf("i=%d\n",i);
	}
	qsort(fit,G_NUMBER_OF_SOLUTIONS, sizeof(int), compare);
	//printf("%d %d %d %d %d %d %d %d %d\n",fit[0],fit[1],fit[2],fit[3],fit[4],fit[5],fit[6],fit[7],fit[8]);
	for(int i=0;i<G_NUMBER_OF_SOLUTIONS;i++)
	{
		for(int j=0;j<G_NUMBER_OF_PARENTS;j++)
		{
			if(fitnessSolution(table[i])==fit[j])
			{
				copy_solution(table,Parents[j],j);
				//printf("save: [node_%d] [delay_%d]\n",Parents[j][1].nodeB,Parents[j][1].additionalDelay_ms);
			}
		}
	}
}
void init_data(int v[12][2])
{	
	NodeS buffer;
	for(int i=0; i<=11; i++)
	{
		buffer.nodeA = i;
		buffer.nodeB = i+1;
		buffer.distance = v[i][0];
		buffer.lanes = v[i][1];
		buffer.offset_ms = 0;
		buffer.additionalDelay_ms = 0;
		buffer.greenLightTimeout = 45;
		Template[i] = buffer;
		//printf("%d %d %d\n",Template[i].nodeB,Template[i].distance,Template[i].lanes);
	}
}
int main()
{	
	int fitTable[G_NUMBER_OF_SOLUTIONS];
	int v[12][2] ={{145,3},{100,3},{235,2},{ 77,2},
				   { 77,3},{337,3},{239,4},{157,4},
				   {190,4},{273,3},{125,3},{220,3}};
	init_data(v);

	//generare populatie / solutii de tip candidat
	//printf("enter\n");
	generate_solutions(Table);
	//printf("%d %d %d\n",Table[0][0].nodeB,Table[0][0].offset_ms,Table[0][0].additionalDelay_ms);
	//printf("%d %d %d\n",Table[1][0].nodeB,Table[1][0].offset_ms,Table[1][0].additionalDelay_ms);
	//printf("%d %d %d\n",Table[2][0].nodeB,Table[2][0].offset_ms,Table[2][0].additionalDelay_ms);

	//fitnes solutii min
	evaluate_solutions(Table,fitTable);
	//Afisare solutie optima rezultata
	for(int i =0; i<G_NUMBER_OF_PARENTS; i++)
	{
		printf("< Parent_%d >\n",i);
		for(int j=0;j<G_NUMBER_OF_NODES;j++)
		 {
			printf("\t...node_%d\t distance_%d\t lanes_%d\t aditionaldelay_%d\t offset_%d\t OUTPUT__%d\n", Parents[i][j].nodeB, Parents[i][j].distance, Parents[i][j].lanes, Parents[i][j].additionalDelay_ms,Parents[i][j].offset_ms,fitnessNode(Parents[i][j]));
		 }
	}
	return 0;
}


