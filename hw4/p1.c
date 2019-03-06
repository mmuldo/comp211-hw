void f(char* A, char* B) {
	A[3] = 'q';
	B = malloc((sizeof(char) * 3));
	B[0] = 'x';
	B[1] = 'y';
	B[2] = 'z';
}

int main(void) {
	char A[] = {'a', 'b', 'c', 'm'};
	char B[] = {'d', 'e', 'f'};
	f(A,B);

	for (int i=0; i<4; i++) printf("%c", A[i]);
	printf("\n");
	for (int j=0; j<3; j++) printf("%c", B[j]);
	printf("\n");
	return 0;

}
