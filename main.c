// Compilar gcc -std=c99 -Wall ppp.c qqq.c -o xxx

#include "lista.c"

int main(){
	
	Graph H;
	 vertex v, w, A, V;

	//printf("Qtd de Vertices: ");
	//scanf("%d", &V);
	H = GRAPHrand(64, 32);

	//0-1 1-2 1-3 2-3
	//0-1 0-3 0-4 1-2 1-4 2-3 2-4 3-4 
	GRAPHinsertArc(H, 0, 1);
	GRAPHinsertArc(H, 0, 3);
	GRAPHinsertArc(H, 0, 4);
	GRAPHinsertArc(H, 1, 2);
	GRAPHinsertArc(H, 1, 4);
	GRAPHinsertArc(H, 2, 3);
	GRAPHinsertArc(H, 2, 4);
	GRAPHinsertArc(H, 3, 4);
	//GRAPHinsertArc(H, 2, 3);
  
	bool value = UGRAPHcircuit0(H);

	printf("%d\n", value);
  //GRAPHshow(H);

  
	/* printf("qual vertice ");
	int v;
	scanf("%d", &v);

	printf("%d\n", GRAPHoutdeg(H, v));
	printf("%d\n", GRAPHindeg(H, v));
 */


	return 0;
}
