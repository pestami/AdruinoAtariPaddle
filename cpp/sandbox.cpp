#include <stdio.h>
#include <string> 
using namespace std;
 
 //=================================================================== 
 bool LoadCycle( int *LoopCounter,  int LoopCounterCieling, int Load) 
 {
	 bool bONOFF=0;
	 
    if ( *LoopCounter > LoopCounterCieling) 
    {
        printf("Reset Counter \n");
        *LoopCounter=0;
    }
    
    if ( *LoopCounter > LoopCounterCieling*Load/100) 
    {
        printf("000000000000000000\n");
        bONOFF=0;
    }
    if ( *LoopCounter < LoopCounterCieling*Load/100) 
    {
        printf("111111111111111111\n");
        bONOFF=1;
    }    
    //printf("Loop Counter: %i", *LoopCounter);   //"%d",
    //printf("\n");   //"%d",     
    return bONOFF;
}
//===================================================================  
int main( void )
{
	int nLoopCounter=0;	
	int iResult=0;
	int nLoad=80;			// 0-100 %
	int nPWM_period=10;  // length of on off pulses 
		
    printf("Begin Simulating Load Cycles v1701 \n");   
    
    for (int i = 0; i < 500; i++)
    {
       nLoopCounter++;    
		//printf("line 32,\n");     
		//printf("Hello,\n");          
		iResult=LoadCycle( &nLoopCounter,nPWM_period,nLoad);     
	}      
    //printf("line 45,\n");     
    return iResult;           
}
//=================================================================== 
