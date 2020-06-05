#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int IDC = 0;
int ID = 0;


// Clears Console
void clrscr(void)
{
	system("cls");
	fflush(stdin);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
//Usual list lol

typedef struct
{
	char info[20];
	struct NodeC* prev, * next;
} NodeC;

typedef struct
{
	int size;
	NodeC* head;
	NodeC* tail;
} ListC;

typedef struct
{
	int info;
	struct NodeI* prev, * next;
} NodeI;

typedef struct
{
	int size;
	NodeI* head;
	NodeI* tail;
} ListI;

ListC* createListC()
{
	ListC* tmp = (ListC*)malloc(sizeof(ListC));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

ListI* createListI()
{
	ListI* tmp = (ListI*)malloc(sizeof(ListI));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

void pushC(ListC* list, char* info)
{
	NodeC* tmp = (NodeC*)malloc(sizeof(NodeC));
	if (tmp == NULL)
	{
		exit(1);
	}
	strcpy(tmp->info, info);
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}
	list->head = tmp;
	if (list->tail == NULL)
	{
		list->tail = tmp;
	}
	list->size++;
}

void pushI(ListI* list, int info)
{
	NodeI* tmp = (NodeI*)malloc(sizeof(NodeI));
	if (tmp == NULL)
	{
		exit(1);
	}
	tmp->info = info;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}
	list->head = tmp;
	if (list->tail == NULL)
	{
		list->tail = tmp;
	}
	list->size++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------
//Flats

typedef struct
{
	char region[20];
	char adress[20];
	int house;
	int floor;
	int size;
	int cost;
	char type[20];
} FlatInfo;

//--------------------------------------------------------------------------------------------------------------------------------------------------
// Owners

typedef struct
{
	char name[20];
	char phoneNumber[14];
	FlatInfo flat;
	int Id;
} OwnerInfo;

typedef struct
{
	OwnerInfo info;
	struct Owner* prev, * next;
} Owner;

typedef struct
{
	int size;
	Owner* head;
	Owner* tail;
} Owners;

//--------------------------------------------------------------------------------------------------------------------------------------------------
//Customers

typedef struct
{
	char name[20];
	char phoneNumber[14];
	int minsum;
	int maxsum;
	int minsize;
	int maxsize;
	ListC Lregions;
	ListC Eregions;
	ListC Ltype;
	ListC Etype;
	ListC Ladress;
	ListC Eadress;
	ListI Lnumbers;
	ListI Enumbers;
	ListI Lfloors;
	ListI Efloors;
	int Id;
} CustomerInfo;

typedef struct
{
	CustomerInfo info;
	struct Customer* prev, * next;
} Customer;

typedef struct
{
	int size;
	Customer* head;
	Customer* tail;
}Customers;

//--------------------------------------------------------------------------------------------------------------------------------------------------
// Work with Customer Lists

Customers* createCustList()
{
	Customers* tmp = (Customers*)malloc(sizeof(Customers));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

void deleteCustLists(Customers** listCustomers)
{
	Customer* tmp = (*listCustomers)->head;
	Customers* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*listCustomers);
	(*listCustomers) = NULL;
}

Customer* getCustomer(Customers* list, int index)
{
	Customer* tmp = list->head;
	int i = 0;
	while (tmp && i < index) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

void pushCustomer(Customers* list, CustomerInfo info)
{
	Customer* tmp = (Customer*)malloc(sizeof(Customer));
	if (tmp == NULL) {
		exit(1);
	}
	tmp->info = info;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;
	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->size++;
}

CustomerInfo popBackCustomer(Customers* list) {
	Customer* next;
	CustomerInfo tmp;
	if (list->tail == NULL) {
		exit(4);
	}
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail) {
		list->tail->next = NULL;
	}
	if (next == list->head) {
		list->head = NULL;
	}
	tmp = next->info;
	free(next);
	list->size--;
	return tmp;
}

CustomerInfo popFrontCustomer(Customers* list) {
	Customer* prev;
	CustomerInfo tmp;
	if (list->head == NULL) {
		exit(2);
	}
	prev = list->head;
	list->head = list->head->next;
	if (list->head) {
		list->head->prev = NULL;
	}
	if (prev == list->tail) {
		list->tail = NULL;
	}
	tmp = prev->info;
	free(prev);
	list->size--;
	return tmp;
}

void AddCustomer(Customers* list)
{
	clrscr();
	CustomerInfo info;
	int x;
	printf("Input some facts\n");


	printf("Your name and surname :\n");
	fgets(info.name, 20, stdin);
	fflush(stdin);
	info.name[strcspn(info.name, "\n")] = '\0';

	printf("Your contacts (your phone number in +375********* format):\n");
	fgets(info.phoneNumber, 15, stdin);
	fflush(stdin);
	info.phoneNumber[strcspn(info.phoneNumber, "\n")] = '\0';

	printf("How many regions are on the list of acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	printf("The acceptable regions are (each on the new line):\n");
	int i;
	char h;
	h = getchar();

	ListC* tmp = (ListC*)malloc(sizeof(ListC));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	info.Lregions = *tmp;

	for (i = 0; i < x; i++)
	{
		char reg[20];
		fgets(reg, 20, stdin);
		fflush(stdin);
		reg[strcspn(reg, "\n")] = '\0';
		pushC(&info.Lregions, reg);
	}

	printf("How many regions are on the list of not acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListC* tmp1 = (ListC*)malloc(sizeof(ListC));
	tmp1->size = 0;
	tmp1->head = tmp1->tail = NULL;
	info.Eregions = *tmp1;

	h = getchar();
	printf("Not acceptable regions are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		char reg[20];
		fgets(reg, 20, stdin);
		fflush(stdin);
		reg[strcspn(reg, "\n")] = '\0';
		pushC(&info.Eregions, reg);
	}

	printf("How many streets are on the list of acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListC* tmp2 = (ListC*)malloc(sizeof(ListC));
	tmp2->size = 0;
	tmp2->head = tmp2->tail = NULL;
	info.Ladress = *tmp2;

	h = getchar();
	printf("The acceptable streets are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		char st[20];
		fgets(st, 20, stdin);
		fflush(stdin);
		st[strcspn(st, "\n")] = '\0';
		pushC(&info.Ladress, st);
	}

	printf("How many streets are on the list of not acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListC* tmp3 = (ListC*)malloc(sizeof(ListC));
	tmp3->size = 0;
	tmp3->head = tmp3->tail = NULL;
	info.Eadress = *tmp3;

	h = getchar();
	printf("Not acceptable streets are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		char st[20];
		fgets(st, 20, stdin);
		fflush(stdin);
		st[strcspn(st, "\n")] = '\0';
		pushC(&info.Eadress, st);
	}

	printf("How many numbers of houses are on the list of acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListI* tmp4 = (ListI*)malloc(sizeof(ListI));
	tmp4->size = 0;
	tmp4->head = tmp4->tail = NULL;
	info.Lnumbers = *tmp4;

	printf("The acceptable numbers of houses are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		int n;
		scanf_s("%d", &n);
		pushI(&info.Lnumbers, n);
	}

	printf("How many numbers of houses are on the list of not acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListI* tmp5 = (ListI*)malloc(sizeof(ListI));
	tmp5->size = 0;
	tmp5->head = tmp5->tail = NULL;
	info.Enumbers = *tmp5;

	printf("Not acceptable numbers of houses are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		int n;
		scanf_s("%d", &n);
		pushI(&info.Enumbers, n);
	}

	printf("How many numbers of floors are on the list of acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListI* tmp6 = (ListI*)malloc(sizeof(ListI));
	tmp6->size = 0;
	tmp6->head = tmp6->tail = NULL;
	info.Lfloors = *tmp6;

	printf("The acceptable numbers of floors are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		int n;
		scanf_s("%d", &n);
		pushI(&info.Lfloors, n);
	}

	printf("How many numbers of floors are on the list of not acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListI* tmp7 = (ListI*)malloc(sizeof(ListI));
	tmp7->size = 0;
	tmp7->head = tmp7->tail = NULL;
	info.Efloors = *tmp7;

	printf("Not acceptable numbers of floors are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		int n;
		scanf_s("%d", &n);
		pushI(&info.Efloors, n);
	}

	printf("How many types of apartment layout are on the list of acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListC* tmp8 = (ListC*)malloc(sizeof(ListC));
	tmp8->size = 0;
	tmp8->head = tmp8->tail = NULL;
	info.Ltype = *tmp8;

	h = getchar();
	printf("The acceptable types of apartment layout are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		char t[20];
		fgets(t, 20, stdin);
		fflush(stdin);
		t[strcspn(t, "\n")] = '\0';
		pushC(&info.Ltype, t);
	}

	printf("How many types of apartment layout are on the list of not acceptable for your desired apartment:\n");
	scanf_s("%d", &x);

	ListC* tmp9 = (ListC*)malloc(sizeof(ListC));
	tmp9->size = 0;
	tmp9->head = tmp9->tail = NULL;
	info.Etype = *tmp9;

	h = getchar();
	printf("Not acceptable types of apartment layout are (each on the new line):\n");
	for (i = 0; i < x; i++)
	{
		char t[20];
		fgets(t, 20, stdin);
		fflush(stdin);
		t[strcspn(t, "\n")] = '\0';
		pushC(&info.Etype, t);
	}

	printf("The minimum cost of your flat:\n");
	scanf_s("%d", &info.minsum);

	printf("The maximum cost of your flat:\n");
	scanf_s("%d", &info.maxsum);

	printf("The minimum size of your flat:\n");
	scanf_s("%d", &info.minsize);

	printf("The maximum size of your flat:\n");
	scanf_s("%d", &info.maxsize);

	IDC++;
	info.Id = IDC;

	fflush(stdin);
	pushCustomer(list, info);
}

void deleteCustomer(Customers* list, int index)
{
	if (index == 0)
	{
		CustomerInfo info = popFrontCustomer(list);
	}
	else if (index == list->size - 1 || index > list->size)
	{
		CustomerInfo info = popBackCustomer(list);
	}
	else if (index <= list->size / 2)
	{
		Customer* previous = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}
		Customer* toDelete = previous->next;
		previous->next = toDelete->next;
		Customer* next = toDelete->next;
		free(toDelete);
		next->prev = previous;
		list->size--;
	}
	else if (index > list->size / 2)
	{
		Customer* next = list->tail;
		for (int i = list->size - 1; i > index + 1; i--)
		{
			next = next->prev;
		}
		Customer* toDelete = next->prev;
		next->prev = toDelete->prev;
		Owner* previous = toDelete->prev;
		free(toDelete);
		previous->next = next;
		list->size--;
	}
}

void PrintCustomer(Customer* tmp)
{
	clrscr();
	int index = 0;
	NodeC* tmpx;
	NodeI* tmpy;
	printf("\n");
	printf("\nName - %s\n", tmp->info.name);
	printf("Phone Number - %s\n", tmp->info.phoneNumber);

	printf("Region of flat - ");
	tmpx = tmp->info.Lregions.head;
	while (tmpx) {
		printf("%s ", tmpx->info);
		tmpx = tmpx->next;
	}
	printf("\n");

	printf("Street of flat  - ");
	tmpx = tmp->info.Ladress.head;
	while (tmpx) {
		printf("%s ", tmpx->info);
		tmpx = tmpx->next;
	}
	printf("\n");

	printf("Number of house - ");
	tmpy = tmp->info.Lnumbers.head;
	while (tmpy) {
		printf("%d ", tmpy->info);
		tmpy = tmpy->next;
	}
	printf("\n");

	printf("Floor of flat - ");
	tmpy = tmp->info.Lfloors.head;
	while (tmpy) {
		printf("%d ", tmpy->info);
		tmpy = tmpy->next;
	}
	printf("\n");

	printf("Type of appartment layout - ");
	tmpx = tmp->info.Ltype.head;
	while (tmpx) {
		printf("%s ", tmpx->info);
		tmpx = tmpx->next;
	}
	printf("\n");

	printf("Size of flat - ");
	printf("Minimum size of flat - %d Maximum size of flat - %d\n", tmp->info.minsize, tmp->info.maxsize);
	printf("Cost of flat - ");
	printf("Minimum cost of flat - %d Maximum cost of flat - %d\n", tmp->info.minsum, tmp->info.maxsum);
	printf("ID - %d\n", tmp->info.Id);
}

void PrintAllCustomers(Customers* list) {
	clrscr();
	Customer* tmp = list->head;
	int index = 0;
	NodeC* tmpx;
	NodeI* tmpy;
	while (tmp) {
		printf("%d\nName - %s\n", index, tmp->info.name);
		printf("Phone Number - %s\n", tmp->info.phoneNumber);

		printf("Region of flat - ");
		tmpx = tmp->info.Lregions.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Not allowed Region of flat - ");
		tmpx = tmp->info.Eregions.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Street of flat  - ");
		tmpx = tmp->info.Ladress.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Not allowed Street of flat  - ");
		tmpx = tmp->info.Eadress.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Number of house - ");
		tmpy = tmp->info.Lnumbers.head;
		while (tmpy) {
			printf("%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		printf("\n");

		printf("Not allowed Number of house - ");
		tmpy = tmp->info.Enumbers.head;
		while (tmpy) {
			printf("%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		printf("\n");

		printf("Floor of flat - ");
		tmpy = tmp->info.Lfloors.head;
		while (tmpy) {
			printf("%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		printf("\n");

		printf("Not allowed Floor of flat - ");
		tmpy = tmp->info.Efloors.head;
		while (tmpy) {
			printf("%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		printf("\n");

		printf("Type of appartment layout - ");
		tmpx = tmp->info.Ltype.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Not allowed of appartment layout - ");
		tmpx = tmp->info.Etype.head;
		while (tmpx) {
			printf("%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		printf("\n");

		printf("Size of flat - ");
		printf("Minimum size of flat - %d Maximum size of flat - %d\n", tmp->info.minsize, tmp->info.maxsize);
		printf("Cost of flat - ");
		printf("Minimum cost of flat - %d Maximum cost of flat - %d\n", tmp->info.minsum, tmp->info.maxsum);
		printf("ID - %d\n", tmp->info.Id);
		tmp = tmp->next;
		index++;
	}
	printf("\n");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------
// Work with Owner Lists

Owners* createOwnList()
{
	Owners* tmp = (Owners*)malloc(sizeof(Owners));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteOwnLists(Owners** listOwners)
{
	Owner* temp = (*listOwners)->head;
	Owners* nex = NULL;
	while (temp) {
		nex = temp->next;
		free(temp);
		temp = nex;
	}
	free(*listOwners);
	(*listOwners) = NULL;
}

Owner* getOwner(Owners* list, int index)
{
	Owner* tmp = list->head;
	int i = 0;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return tmp;
}

void pushOwner(Owners* list, OwnerInfo info)
{
	Owner* tmp = (Owner*)malloc(sizeof(Owner));
	if (tmp == NULL)
	{
		exit(1);
	}
	tmp->info = info;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}
	list->head = tmp;
	if (list->tail == NULL)
	{
		list->tail = tmp;
	}
	list->size++;
}

OwnerInfo popFrontOwner(Owners* list)
{
	Owner* prev;
	OwnerInfo tmp;
	if (list->head == NULL)
	{
		exit(2);
	}
	prev = list->head;
	list->head = list->head->next;
	if (list->head)
	{
		list->head->prev = NULL;
	}
	if (prev == list->tail)
	{
		list->tail = NULL;
	}
	tmp = prev->info;
	free(prev);
	list->size--;
	return tmp;
}

OwnerInfo popBackOwner(Owners* list)
{
	Owner* next;
	OwnerInfo tmp;
	if (list->tail == NULL)
	{
		exit(4);
	}
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
	{
		list->tail->next = NULL;
	}
	if (next == list->head)
	{
		list->head = NULL;
	}
	tmp = next->info;
	free(next);
	list->size--;
	return tmp;
}

void AddOwner(Owners* list)
{
	OwnerInfo info;
	FlatInfo data;
	clrscr();
	printf("Input some facts\n");

	printf("Your name and surname :\n");
	fgets(info.name, 20, stdin);
	fflush(stdin);
	info.name[strcspn(info.name, "\n")] = '\0';

	printf("Your contacts (your phone number in +375********* format):\n");
	fgets(info.phoneNumber, 15, stdin);
	fflush(stdin);
	info.phoneNumber[strcspn(info.phoneNumber, "\n")] = '\0';

	printf("The region of your flat:\n");
	fgets(data.region, 20, stdin);
	fflush(stdin);
	data.region[strcspn(data.region, "\n")] = '\0';

	printf("The adress(street) of your flat :\n");
	fgets(data.adress, 20, stdin);
	fflush(stdin);
	data.adress[strcspn(data.adress, "\n")] = '\0';

	printf("The type of apartment layout:\n");
	fgets(data.type, 20, stdin);
	fflush(stdin);
	data.type[strcspn(data.type, "\n")] = '\0';

	printf("The number of house of your flat:\n");
	scanf_s("%d", &data.house);

	printf("The floor of your flat:\n");
	scanf_s("%d", &data.floor);

	printf("The cost of your flat:\n");
	scanf_s("%d", &data.cost);

	printf("The size of your flat:\n");
	scanf_s("%d", &data.size);

	info.flat = data;
	ID++;
	info.Id = ID;

	fflush(stdin);
	char h;
	h = getchar();
	pushOwner(list, info);
}

void deleteOwner(Owners* list, int index)
{
	if (index == 0)
	{
		OwnerInfo info = popFrontOwner(list);
	}
	else if (index == list->size - 1 || index > list->size)
	{
		OwnerInfo info = popBackOwner(list);
	}
	else if (index <= list->size / 2)
	{
		Owner* previous = list->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->next;
		}
		Owner* toDelete = previous->next;
		previous->next = toDelete->next;
		Owner* next = toDelete->next;
		free(toDelete);
		next->prev = previous;
		list->size--;
	}
	else if (index > list->size / 2)
	{
		Owner* next = list->tail;
		for (int i = list->size - 1; i > index + 1; i--)
		{
			next = next->prev;
		}
		Owner* toDelete = next->prev;
		next->prev = toDelete->prev;
		Owner* previous = toDelete->prev;
		free(toDelete);
		previous->next = next;
		list->size--;
	}
}

void PrintOwner(Owner* tmp)
{
	clrscr();
	FlatInfo x = tmp->info.flat;
	printf("Name - %s\n", tmp->info.name);
	printf("Phone Number - %s\n", tmp->info.phoneNumber);
	printf("Region of flat - %s\n", x.region);
	printf("Street of flat  - %s\n", x.adress);
	printf("Number of house - %d\n", x.house);
	printf("Size if flat - %d\n", x.size);
	printf("Floor of flat - %d\n", x.floor);
	printf("Type of appartment layout - %s\n", x.type);
	printf("Cost of flat - %d\n", x.cost);
	printf("ID - %d\n", tmp->info.Id);
}

void PrintAllOwners(Owners* list)
{
	clrscr();
	Owner* tmp = list->head;
	int index = 0;
	FlatInfo x;
	while (tmp) {
		x = tmp->info.flat;
		printf("%d\nName - %s\n", index, tmp->info.name);
		printf("Phone Number - %s\n", tmp->info.phoneNumber);
		printf("Region of flat - %s\n", x.region);
		printf("Street of flat  - %s\n", x.adress);
		printf("Number of house - %d\n", x.house);
		printf("Size if flat - %d\n", x.size);
		printf("Floor of flat - %d\n", x.floor);
		printf("Type of appartment layout - %s\n", x.type);
		printf("Cost of flat - %d\n", x.cost);
		printf("ID - %d\n", tmp->info.Id);
		tmp = tmp->next;
		index++;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------
//Owner Search

void OwnerNameSearch(Owners* list)
{
	clrscr();
	printf("Input name :\n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Owner* tmp = list->head;
	while (tmp)
	{
		if (strcmp(tmp->info.name, string) == 0)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerRegionSearch(Owners* list)
{
	clrscr();
	printf("Input region: \n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Owner* tmp = list->head;
	while (tmp)
	{
		if (strcmp(tmp->info.flat.region, string) == 0)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerStreetSearch(Owners* list)
{
	clrscr();
	printf("Input street: \n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Owner* tmp = list->head;
	while (tmp)
	{
		if (strcmp(tmp->info.flat.adress, string) == 0)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerHouseSearch(Owners* list) {

	clrscr();
	printf("Input number of house : \n");
	int string = 0;
	scanf_s("%d", &string);
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.flat.house == string)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerTypeSearch(Owners* list)
{
	clrscr();
	printf("Input type of appartment layout: ");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Owner* tmp = list->head;
	while (tmp)
	{
		if (strcmp(tmp->info.flat.type, string) == 0)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerSizeSearch(Owners* list)
{
	clrscr();
	printf("Input size of flat: \n");
	int string = 0;
	scanf_s("%d", &string);
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.flat.size == string)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerFloorSearch(Owners* list)
{
	clrscr();
	printf("Input floor of flat: \n");
	int string = 0;
	scanf_s("%d", &string);
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.flat.floor == string)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerCostSearch(Owners* list)
{
	clrscr();
	printf("Input cost of flat: \n");
	int string = 0;
	scanf_s("%d", &string);
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.flat.cost == string)
		{
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
}

void OwnerSearchChoice(Owners* list)
{
	clrscr();
	printf("Search by\n1 - Name\n2 - Region\n3 - Street\n4 - Number of house\n5 - Floor\n6 - Type of appartment layout\n7 - Size\n8 - Cost\n9 - Back\n");
	switch (getch())
	{
	case '1': OwnerNameSearch(list); break;
	case '2': OwnerRegionSearch(list); break;
	case '3': OwnerStreetSearch(list); break;
	case '4': OwnerHouseSearch(list); break;
	case '5': OwnerFloorSearch(list); break;
	case '6': OwnerTypeSearch(list); break;
	case '7': OwnerSizeSearch(list); break;
	case '8': OwnerCostSearch(list); break;
	default: return;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------
//Customer Search

void CustomerNameSearch(Customers* list)
{
	clrscr();
	printf("Input name : ");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Customer* tmp = list->head;
	while (tmp)
	{
		if (strcmp(tmp->info.name, string) == 0)
		{
			PrintCustomer(tmp);
		}
		tmp = tmp->next;
	}
}

void CustomerRegionSearch(Customers* list)
{
	clrscr();
	printf("Input region: \n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Customer* tmp = list->head;
	while (tmp)
	{
		NodeC* tmpC = tmp->info.Lregions.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, string) == 0)
			{
				PrintCustomer(tmp);
			}
			tmpC = tmpC->next;
		}
		tmp = tmp->next;
	}
}

void CustomerStreetSearch(Customers* list)
{
	clrscr();
	printf("Input street: \n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Customer* tmp = list->head;
	while (tmp)
	{
		NodeC* tmpC = tmp->info.Ladress.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, string) == 0)
			{
				PrintCustomer(tmp);
			}
			tmpC = tmpC->next;
		}
		tmp = tmp->next;
	}
}

void CustomerTypeSearch(Customers* list)
{
	clrscr();
	printf("Input type of appartment layout: \n");
	char string[20];
	fgets(string, 20, stdin);
	fflush(stdin);
	string[strcspn(string, "\n")] = '\0';
	Customer* tmp = list->head;
	while (tmp)
	{
		NodeC* tmpC = tmp->info.Ltype.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, string) == 0)
			{
				PrintCustomer(tmp);
			}
			tmpC = tmpC->next;
		}
		tmp = tmp->next;
	}
}

void CustomerFloorSearch(Customers* list)
{
	clrscr();
	printf("Input floor: \n");
	int string = 0;
	scanf_s("%d", &string);
	Customer* tmp = list->head;
	while (tmp)
	{
		NodeI* tmpI = tmp->info.Lfloors.head;
		while (tmpI)
		{
			if (tmpI->info == string)
			{
				PrintCustomer(tmp);
			}
			tmpI = tmpI->next;
		}
		tmp = tmp->next;
	}
}

void CustomerHouseSearch(Customers* list)
{
	clrscr();
	printf("Input number of house: \n");
	int string = 0;
	scanf_s("%d", &string);
	Customer* tmp = list->head;
	while (tmp)
	{
		NodeI* tmpI = tmp->info.Lnumbers.head;
		while (tmpI)
		{
			if (tmpI->info == string)
			{
				PrintCustomer(tmp);
			}
			tmpI = tmpI->next;
		}
		tmp = tmp->next;
	}
}

void CustomerSizeSearch(Customers* list)
{
	clrscr();
	printf("Input size of flat: \n");
	int string = 0;
	scanf_s("%d", &string);
	Customer* tmp = list->head;
	while (tmp)
	{
		if ((tmp->info.minsize <= string) && (tmp->info.maxsize >= string))
		{
			PrintCustomer(tmp);
		}
		tmp = tmp->next;
	}
}

void CustomerCostSearch(Customers* list)
{
	clrscr();
	printf("Input cost of flat: \n");
	int string = 0;
	scanf_s("%d", &string);
	Customer* tmp = list->head;
	while (tmp)
	{
		if ((tmp->info.minsum <= string) && (tmp->info.maxsum >= string))
		{
			PrintCustomer(tmp);
		}
		tmp = tmp->next;
	}
}

void CustomerSearchChoice(Customers* list)
{
	clrscr();
	printf("Search by\n1 - Name\n2 - Region\n3 - Street\n4 - Number of house\n5 - Floor\n6 - Type of appartment layout\n7 - Size\n8 - Cost\n9 - Back\n");
	switch (getch())
	{
	case '1': CustomerNameSearch(list); break;
	case '2': CustomerRegionSearch(list); break;
	case '3': CustomerStreetSearch(list); break;
	case '4': CustomerHouseSearch(list); break;
	case '5': CustomerFloorSearch(list); break;
	case '6': CustomerTypeSearch(list); break;
	case '7': CustomerSizeSearch(list); break;
	case '8': CustomerCostSearch(list); break;
	default: return;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
//Work with Lists

void ChooseAdd(Owners* own, Customers* cust)
{
	while (1)
	{
		clrscr();
		printf("1 - Add Owner\n2 - Add Customer\n3 - Back\n");
		switch (getch())
		{
		case '1': clrscr(); fflush(stdin); AddOwner(own); return;
		case '2': clrscr(); fflush(stdin); AddCustomer(cust); return;
		case '3': return;
		}
	}

}


void Remove(Owners* own, Customers* cust)
{
	printf("Delete\n1 - Owner\n2 - Customer\n");
	int key;
	switch (getch())
	{
	case '1':
		clrscr();
		PrintAllOwners(own);
		printf("Choose index \n");
		key = 0;
		scanf_s("%d", &key);
		deleteOwner(own, key);
		break;
	case '2':
		clrscr();
		PrintAllCustomers(cust);
		printf("Choose index \n");
		key = 0;
		scanf_s("%d", &key);
		deleteCustomer(cust, key);
		break;
	}
}

void ChoosePrint(Owners* own, Customers* cust)
{
	while (1)
	{
		clrscr();
		printf("1 - Print Owners\n2 - Print Customers\n3 - Back\n");
		switch (getch())
		{
		case '1': clrscr(); PrintAllOwners(own); return;
		case '2': clrscr(); PrintAllCustomers(cust); return;
		case'3': return;
		}
	}

}

void SearchFor(Owners* own, Customers* cust)
{
	printf("Search for\n1 - Owner\n2 - Customer\n3 - Back\n");
	switch (getch())
	{
	case '1': OwnerSearchChoice(own); break;
	case '2': CustomerSearchChoice(cust); break;
	default: return;
	}
}


void Help()
{
	printf("This is the database selling flats.\n");
	printf("Add - Allows to add an owner's information or a customer's inquiry.\nRemove - Just removes an owner or a customer\nView - Prints lists of owners and customers\n");
}

int FindDefinitionOwner(Owner* own, Customers* cust)
{
	Customer* tmp = cust->head;
	NodeC* tmpC; NodeI* tmpI;
	int ans = 0;
	int kol = 0;
	while (tmp)
	{
		tmpC = tmp->info.Lregions.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, own->info.flat.region) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpC = tmp->info.Ladress.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, own->info.flat.adress) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpC = tmp->info.Ltype.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, own->info.flat.type) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpI = tmp->info.Lnumbers.head;
		while (tmpI)
		{
			if (tmpI->info == own->info.flat.house)
			{
				kol++;
			}
			tmpI = tmpI->next;
		}
		tmpI = tmp->info.Lfloors.head;
		while (tmpI)
		{
			if (tmpI->info == own->info.flat.floor)
			{
				kol++;
			}
			tmpI = tmpI->next;
		}
		if ((tmp->info.minsize <= own->info.flat.size) && (tmp->info.maxsize >= own->info.flat.size))
		{
			kol++;
		}
		if ((tmp->info.minsum <= own->info.flat.cost) && (tmp->info.maxsum >= own->info.flat.cost))
		{
			kol++;
		}
		if (kol >= 7)
		{
			ans++;
			PrintCustomer(tmp);
		}
		tmp = tmp->next;
	}
	return ans;
}

int FindDefinitionCustomer(Owners* own, Customer* cust)
{
	Owner* tmp = own->head;
	NodeC* tmpC;
	NodeI* tmpI;
	int kol = 0;
	int ans = 0;
	while (tmp)
	{
		tmpC = cust->info.Lregions.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, tmp->info.flat.region) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpC = cust->info.Ladress.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, tmp->info.flat.adress) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpC = cust->info.Ltype.head;
		while (tmpC)
		{
			if (strcmp(tmpC->info, tmp->info.flat.type) == 0)
			{
				kol++;
			}
			tmpC = tmpC->next;
		}
		tmpI = cust->info.Lnumbers.head;
		while (tmpI)
		{
			if (tmpI->info == tmp->info.flat.house)
			{
				kol++;
			}
			tmpI = tmpI->next;
		}
		tmpI = cust->info.Lfloors.head;
		while (tmpI)
		{
			if (tmpI->info == tmp->info.flat.floor)
			{
				kol++;
			}
			tmpI = tmpI->next;
		}
		if ((cust->info.minsize <= tmp->info.flat.size) && (cust->info.maxsize >= tmp->info.flat.size))
		{
			kol++;
		}
		if ((cust->info.minsum <= tmp->info.flat.cost) && (cust->info.maxsum >= tmp->info.flat.cost))
		{
			kol++;
		}
		if (kol >= 7)
		{
			ans++;
			PrintOwner(tmp);
		}
		tmp = tmp->next;
	}
	return ans;
}

void ChoosePartnerForOwner(Owners* list, Owner* own, Customers* cust)
{
	clrscr();
	int x = FindDefinitionOwner(own, cust);
	if (x != 0) printf("Select the index of your future partner:\n");
	int key = 0;
	scanf_s("%d", &key);
	deleteCustomer(cust, SearchIndexCust(cust, key));
	deleteOwner(list, SearchIndexOwn(list, own->info.Id));
}

void ChoosePartnerForCustomer(Customers* list, Customer* cust, Owners* own)
{
	clrscr();
	int x = FindDefinitionCustomer(own, cust);
	if (x != 0) printf("Select the id of your future partner:\n");
	int key = 0;
	scanf_s("%d", &key);
	deleteOwner(own, SearchIndexOwn(own, key));
	deleteCustomer(list, SearchIndexCust(list, cust->info.Id));
}

int SearchIndexCust(Customers* list, int id)
{
	int x = 0;
	Customer* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.Id == id)
		{
			return x;
		}
		tmp = tmp->next;
		x++;
	}
}

int SearchIndexOwn(Owners* list, int id)
{
	int x = 0;
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.Id == id)
		{
			return x;
		}
		tmp = tmp->next;
		x++;
	}
}

Owner* SearchOwn(Owners* list, int id)
{
	int x = 0;
	Owner* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.Id == id)
		{
			return tmp;
		}
		tmp = tmp->next;
		x++;
	}
}

Customer* SearchCust(Customers* list, int id)
{
	int x = 0;
	Customer* tmp = list->head;
	while (tmp)
	{
		if (tmp->info.Id == id)
		{
			return tmp;
		}
		tmp = tmp->next;
		x++;
	}
}

void DealOwner(Owners* own, Customers* cust)
{
	clrscr();
	int x;
	printf("Choose the owners Id\n");
	scanf("%d", &x);
	Owner* target = SearchOwn(own, x);
	ChoosePartnerForOwner(own, target, cust);
}

void DealCustomer(Owners* own, Customers* cust)
{
	clrscr();
	int x;
	printf("Choose the customers Id\n");
	scanf("%d", &x);
	Customer* target = SearchCust(cust, x);
	ChoosePartnerForCustomer(cust, target, own);
}


void Deal(Owners* own, Customers* cust)
{
	clrscr();
	printf("Deal for\n1 - Owner\n2 - Customer\n3 - Back\n");
	switch (getch())
	{
	case '1': DealOwner(own, cust); break;
	case '2': DealCustomer(own, cust); break;
	default: return;
	}
}

int atoi(char s[])
{
	int i, n;
	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0');
	return n;
}

OwnerInfo* StrOwner(char* str)
{
	OwnerInfo* tmp = (OwnerInfo*)malloc(sizeof(OwnerInfo));
	char sep[10] = " | ";
	char x[10];
	char* istr; int i = 0;
	istr = strtok(str, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->name[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->phoneNumber[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->flat.region[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->flat.adress[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->flat.type[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	tmp->flat.house = atoi(x);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	tmp->flat.floor = atoi(x);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	tmp->flat.size = atoi(x);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	tmp->flat.cost = atoi(x);
	tmp->Id = ID;
	ID++;
	return tmp;
}

CustomerInfo* StrCust(char* str)
{
	CustomerInfo* tmp = (CustomerInfo*)malloc(sizeof(CustomerInfo));
	char sep[10] = " | ";
	char x[10]; int kol; int kol1;
	char* istr; int i = 0;
	istr = strtok(str, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->name[i] = *(istr + i);
	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		tmp->phoneNumber[i] = *(istr + i);

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	ListC* q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Lregions = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Lregions, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Eregions = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Eregions, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Ladress = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Ladress, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Eadress = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Eadress, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Ltype = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Ltype, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	q = (ListC*)malloc(sizeof(ListC));
	q->size = 0;
	q->head = q->tail = NULL;
	tmp->Etype = *q;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		pushC(&tmp->Etype, x);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	ListI* w = (ListI*)malloc(sizeof(ListI));
	w->size = 0;
	w->head = w->tail = NULL;
	tmp->Lnumbers = *w;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		kol1 = atoi(x);
		pushC(&tmp->Lnumbers, kol);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	w = (ListI*)malloc(sizeof(ListI));
	w->size = 0;
	w->head = w->tail = NULL;
	tmp->Enumbers = *w;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		kol1 = atoi(x);
		pushC(&tmp->Enumbers, kol);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	w = (ListI*)malloc(sizeof(ListI));
	w->size = 0;
	w->head = w->tail = NULL;
	tmp->Lfloors = *w;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		kol1 = atoi(x);
		pushC(&tmp->Lfloors, kol);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	w = (ListI*)malloc(sizeof(ListI));
	w->size = 0;
	w->head = w->tail = NULL;
	tmp->Efloors = *w;
	for (i = 0; i < kol; i++)
	{
		istr = strtok(NULL, sep);
		for (; i < min1(20, strlen(istr)); i++)
			x[i] = *(istr + i);
		kol1 = atoi(x);
		pushC(&tmp->Efloors, kol);
	}

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	tmp->minsize = kol;

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	tmp->maxsize = kol;

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	tmp->minsum = kol;

	istr = strtok(NULL, sep);
	for (; i < min1(20, strlen(istr)); i++)
		x[i] = *(istr + i);
	kol = atoi(x);
	tmp->maxsum = kol;
	tmp->Id = IDC;
	IDC++;
	return tmp;
}

int min1(int a, int b) {
	if (a < b) return a;
	else return b;
}


void FPrintAllCustomers(Customers* list) {
	FILE* fp2 = fopen("CustomersOutput.txt", "w+");
	Customer* tmp = list->head;
	int index = 0;
	NodeC* tmpx;
	NodeI* tmpy;
	while (tmp) {
		fprintf(fp2, "%d\nName - %s\n", index, tmp->info.name);
		fprintf(fp2, "Phone Number - %s\n", tmp->info.phoneNumber);

		fprintf(fp2, "Region of flat - ");
		tmpx = tmp->info.Lregions.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Not allowed Region of flat - ");
		tmpx = tmp->info.Eregions.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Street of flat  - ");
		tmpx = tmp->info.Ladress.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Not allowed Street of flat  - ");
		tmpx = tmp->info.Eadress.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Number of house - ");
		tmpy = tmp->info.Lnumbers.head;
		while (tmpy) {
			fprintf(fp2, "%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Not allowed Number of house - ");
		tmpy = tmp->info.Enumbers.head;
		while (tmpy) {
			fprintf(fp2, "%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Floor of flat - ");
		tmpy = tmp->info.Lfloors.head;
		while (tmpy) {
			fprintf(fp2, "%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Not allowed Floor of flat - ");
		tmpy = tmp->info.Efloors.head;
		while (tmpy) {
			fprintf(fp2, "%d ", tmpy->info);
			tmpy = tmpy->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Type of appartment layout - ");
		tmpx = tmp->info.Ltype.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Not allowed of appartment layout - ");
		tmpx = tmp->info.Etype.head;
		while (tmpx) {
			fprintf(fp2, "%s ", tmpx->info);
			tmpx = tmpx->next;
		}
		fprintf(fp2, "\n");

		fprintf(fp2, "Size of flat - ");
		fprintf(fp2, "Minimum size of flat - %d Maximum size of flat - %d\n", tmp->info.minsize, tmp->info.maxsize);
		fprintf(fp2, "Cost of flat - ");
		fprintf(fp2, "Minimum cost of flat - %d Maximum cost of flat - %d\n", tmp->info.minsum, tmp->info.maxsum);
		fprintf(fp2, "ID - %d\n", tmp->info.Id);
		tmp = tmp->next;
		index++;
	}
	fprintf(fp2, "\n");
	fclose(fp2);
}

void FPrintAllOwners(Owners* list)
{
	FILE* fp3 = fopen("OwnersOutput.txt", "w+");
	Owner* tmp = list->head;
	int index = 0;
	FlatInfo x;
	while (tmp) {
		x = tmp->info.flat;
		fprintf(fp3, "%d\nName - %s\n", index, tmp->info.name);
		fprintf(fp3, "Phone Number - %s\n", tmp->info.phoneNumber);
		fprintf(fp3, "Region of flat - %s\n", x.region);
		fprintf(fp3, "Street of flat  - %s\n", x.adress);
		fprintf(fp3, "Number of house - %d\n", x.house);
		fprintf(fp3, "Size if flat - %d\n", x.size);
		fprintf(fp3, "Floor of flat - %d\n", x.floor);
		fprintf(fp3, "Type of appartment layout - %s\n", x.type);
		fprintf(fp3, "Cost of flat - %d\n", x.cost);
		fprintf(fp3, "ID - %d\n", tmp->info.Id);
		tmp = tmp->next;
		index++;
	}
	fclose(fp3);
}

void OpenOwn(Owners* own)
{
	FILE* fp4 = fopen("Owners.txt", "r");
	int i = 0;
	while (1) {
		char* str = (char*)malloc(sizeof(char) * 1000);
		fgets(str, sizeof(str), fp4);
		if (str == "") {
			break;
		}
		pushOwner(own, *StrOwner(str));
	}
	fclose(fp4);
}

void OpenCust(Customers* cust)
{
	FILE* fp5 = fopen("Customers.txt", "r");
	int i = 0;
	while (1) {
		char* str = (char*)malloc(sizeof(char) * 1000);
		fgets(str, sizeof(str), fp5);
		if (str == "") {
			break;
		}
		pushCustomer(cust, *StrCust(str));
	}
	fclose(fp5);
}



void main()
{
	Owners* own = createOwnList();
	Customers* cust = createCustList();

	//OpenOwn(own);
	//OpenCust(cust);


	while (1)
	{
		clrscr();

		printf("Find your owner or customer\n1 - Help\n2 - Add\n3 - Remove\n4 - View\n5 - Search\n6 - Deal\n7 - Exit\n");
		switch (getch())
		{
		case '1': clrscr(); Help(); getch(); break;
		case '2': clrscr(); ChooseAdd(own, cust); getch(); break;
		case '3': clrscr(); Remove(own, cust); break;
		case '4': clrscr(); ChoosePrint(own, cust); getch(); break;
		case '5': clrscr(); SearchFor(own, cust); getch(); break;
		case '6': clrscr(); Deal(own, cust); getch(); break;
		case '7': FPrintAllOwners(own); FPrintAllCustomers(cust); return;
		}

	}
}