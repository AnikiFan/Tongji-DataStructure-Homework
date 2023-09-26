#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MAXN 20000
#define LENGTH 200
char code[MAXN][LENGTH], name[MAXN][LENGTH], opt[10], stu_name[LENGTH], stu_code[LENGTH];
int ind;
int n;
void check_name()
{
	for (int i = 0; i < n; i++) {
		if (!strcmp(opt, name[i])) {
			printf("%d %s %s\n", i+1, code[i], name[i]);
			return;
		}
	}
	printf("-1\n");
	return;
}
void check_no()
{
	for (int i = 0; i < n; i++) {
		if (!strcmp(opt, code[i])) {
			printf("%d %s %s\n", i+1, code[i], name[i]);
			return;
		}
	}
	printf("-1\n");

	return;
}
void insert()
{
	ind--;
	if (ind<0 || ind>n ) {
		printf("-1\n");
		return;
	}
	else {
		printf("0\n");
		for (int i = n - 1; i >= ind; i--) {
			strcpy(code[i + 1], code[i]);
			strcpy(name[i + 1], name[i]);
		}
		strcpy(code[ind], stu_code);
		strcpy(name[ind], stu_name);
	}
	n++;
	return;
}
void remove()
{
	ind--;
	if (ind<0 || ind>n-1) {
		printf("-1\n");
		return;
	}
	else {
		printf("0\n");
		for (int i = ind; i < n; i++) {
			strcpy(code[i], code[i + 1]);
			strcpy(name[i], name[i + 1]);
		}
	}
	n--;
	return;
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s%s", &code[i], &name[i]);
	}
	while (scanf("%s", opt) == 1 && strcmp(opt, "end")) {
		if (!strcmp(opt, "check")) {
			scanf("%s", &opt);
			if (!strcmp(opt, "name")) {
				scanf("%s", &opt);
				check_name();
			}
			else {
				scanf("%s", &opt);
				check_no();
			}
		}
		else {
			scanf("%d", &ind);
			if (!strcmp(opt, "insert")) {
				scanf("%s%s", &stu_code, &stu_name);
				insert();
			}
			else
				remove();
		}

	}
		printf("%d\n", n);
	return 0;
}
