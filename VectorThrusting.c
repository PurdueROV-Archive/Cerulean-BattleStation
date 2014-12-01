//This is a proof of concept for converting vectors into motor powers
// It's wirten and C and will need to be converted for C++/Qt
// Remove when finished

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	float X = 0, Y = 0, Z = 0, Pitch = 0, Yaw = 0, Roll = 0; // values from controler
	float A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0; // thruster power (-50 to 50)
	float Max = 0;
	float Scale = 1;
	
	while(1)
	{
		printf("Enter X, Y, Z, Pitch, Yaw, Roll\n");
		scanf("%f%f%f%f%f%f",&X,&Y,&Z,&Pitch,&Yaw,&Roll); // replace this with controller inputs
		A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, Max = 0; // Resets vectors and max for new computation
		
		// Calculates thruster power from input vectors (no max power limit)
		E += X;
		H += X;
		F += -X;
		G += -X;
		A += Y;
		B += Y;
		C += Y;
		D += Y;
		H += Z;
		G += Z;
		E += -Z;
		F += -Z;
		A += Roll;
		B += Roll;
		C += -Roll;
		D += -Roll;
		E += -Yaw;
		F += Yaw;
		G += -Yaw;
		H += Yaw;
		A += -Pitch;
		B += Pitch;
		C += Pitch;
		D += -Pitch;
		
		printf("Before scale:\n");	
		printf("A = %.1f, B = %.1f, C = %.1f, D = %.1f\n",A,B,C,D);
		printf("E = %.1f, F = %.1f, G = %.1f, H = %.1f\n",E,F,G,H);
		
		// Determines maximum thruster value
		if (abs(A) > Max)
			Max = A;
		if (abs(B) > Max)
			Max = B;
		if (abs(C) > Max)
			Max = C;
		if (abs(D) > Max)
			Max = D;
		if (abs(E) > Max)
			Max = E;
		if (abs(F) > Max)
			Max = F;
		if (abs(G) > Max)
			Max = G;
		if (abs(H) > Max)
			Max = H;
		
		// Scales maximum thruster value to 50
		if (Max > 50) 
		{
			Scale = 50 / Max;
			A*=Scale;
			B*=Scale;
			C*=Scale;
			D*=Scale;
			E*=Scale;
			F*=Scale;
			G*=Scale;
			H*=Scale;
		}
	
		printf("\nAfter scale:\n");	
		printf("A = %.1f, B = %.1f, C = %.1f, D = %.1f\n",A,B,C,D);
		printf("E = %.1f, F = %.1f, G = %.1f, H = %.1f\n",E,F,G,H);
		
	}
	return EXIT_SUCCESS;
}


