#include <stdio.h> 
char GetGlobal(); 
char Next(); 
char Last(); 
char Get(); 
char c = 'G';				// ����ȫ�ֱ���c
int main() 
{ 
	char c = 'L';			// ����ֲ�����c

	printf("Local c in main function is: %c\n", c);	// �ڵ�ǰ������ʹ�õı���c�Ǿֲ�����

	printf("Global c is: %c\n", GetGlobal());		// ��ȡȫ�ֱ���

	printf("Static c in file2 is: %c\n", Get());	// ��ȡ�ļ�2�еľ�̬����c
	// �����еľ�̬�����ᱣ��
	printf("Previous values of static c in file2 are: %c, %c, and %c\n", Last(), Last(), Last());	
	printf("Next values of static c in file2 are: %c, %c, and %c\n", Next(), Next(), Next());

	getchar();	// ������ͣ���ȴ��û����룬�Ա����û�����ǰ���������
	return 0;
} 