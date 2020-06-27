#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>
using namespace std;

// 瞪籀葬 -----------------------------------------------------------------
#define MAX_GROUP_SIZE 100
#define MAX_TASK_SIZE_PER_GROUP 100
#define MAX_TASK_SIZE 1000

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 100
#define BACK_SPACE -10

// 掘褻羹 塽 贗楚蝶 -------------------------------------------------------

typedef struct date {
	int month;
	int day;
}date;

class SettingProperty {
private:
	char color[2];
public:
	SettingProperty(char _BGcolor, char _textColor) {
		color[0] = _BGcolor;
		color[1] = _textColor;
		char command[9] = "COLOR ";
		command[6] = color[0];
		command[7] = color[1];
		system(command);
	}
	SettingProperty() {
		SettingProperty(0, 15);
	}

	void refresh_color() {
		char command[9] = "COLOR ";
		command[6] = color[0] < 10 ? color[0] + '0' : color[0] + 'A' - 10;
		command[7] = color[1] < 10 ? color[1] + '0' : color[1] + 'A' - 10;
		system(command);
	}

	bool set_BGcolor(char _BGcolor) {
		if (color[1] == _BGcolor) {
			return false;
		}
		else {
			color[0] = _BGcolor;
			refresh_color();
			return true;
		}
	}
	bool set_textColor(char _textColor) {
		if (color[0] == _textColor) {
			return false;
		}
		else {
			color[1] = _textColor;
			refresh_color();
			return true;
		}
	}

	char get_BGcolor(void) {
		return color[0];
	}

	char get_textColor(void) {
		return color[1];
	}
};

class Task {
private:
	string name;
	date deadline;
public:
	Task(string _name, date _deadline) {
		set_name(_name);
		set_deadline(_deadline);
	}

	bool set_name(string _name) {
		this->name = _name;
		return true;
	}

	string get_name(void) {
		return this->name;
	}

	bool set_deadline(date _deadline) {
		this->deadline = _deadline;
		return true;
	}
};

class Group {
private:
	static int group_size;
	static Group* curPos;
	enum VisualMode {Vector, Queue, Stack, Heap};

	int index;
	string name;
	char color;
	Task* rootTask;
	VisualMode visualMode;

	bool reduplication_test(string str) {
		Group* iterPos = curPos;
		do {
			if (iterPos->name == str) {
				return true;
			}
			iterPos = iterPos->next;
		} while (iterPos != curPos);
		return false;
	}

public:
	Group* prev;
	Group* next;

	Group() {
		set_color(7);
		set_name("");
		index = group_size;
		group_size++;
		if (group_size == 1) {
			curPos = this;
			this->next = this;
			this->prev = this;
		}
		else {
			this->next;
		}
		rootTask = NULL;
	}

	bool set_color(int index) {
		this->color = index % 16;
		return true;
	}

	int get_color() {
		return this->color;
	}

	bool set_name(string _name) {
		bool isReduplicated = reduplication_test(_name);
		if (isReduplicated) {
			// 檜葷 醞犒 籀葬
			return false;
		}
		// 檜葷 瞳辨 籀葬
		this->name = _name;
		return true;
	}

	void set_visual_mode(int index) {
		this->visualMode = (VisualMode)index;
		return;
	}

	void add(string data, date deadline) {
		Task* newTask = (Task*)malloc(sizeof(Task));
		*newTask = Task(data, deadline);
	}
};

class GroupProperty {
private:
	int size;
	Group* head;
	Group* tail;
public:

	GroupProperty() {
		size = 0;
		head = NULL;
		tail = NULL;
	}

	void add(string name, int visualizer, int color) {
		Group* newGroup = (Group*)malloc(sizeof(Group));
		*newGroup = Group();
		newGroup->set_name(name);
		newGroup->set_visual_mode(visualizer);
		newGroup->set_color(color);

		if (tail != NULL) {
			tail->next = newGroup;
			newGroup->prev = tail;
		}
		tail = newGroup;
		if (size == 0) {
			head = tail;
		}
		size++;
	}

	Group* get_group_by_index(int index) {
		Group* iterPos = head;
		for (int i = 0; i < index; i++) {
			if (iterPos == tail->next) {
				return NULL;
			}
			iterPos = iterPos->next;
		}
		return iterPos;
	}

	void insert(int departure, int destination) {
		if (departure == destination || departure >= size || destination >= size) {
			return;
		}
		Group* before = get_group_by_index(departure);
		Group* after = get_group_by_index(destination);
		before->prev->next = before->next;
		before->next->prev = before->prev;

		before->next = after->next;
		before->prev = after;

		after->next = before;
		return;
	}

	void remove(int index) {
		Group* tmp = get_group_by_index(index);
		if (tmp == NULL) {
			return;
		}
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp);
	}

	void tour() {
		Group* iterPos = head;
		while (iterPos != NULL) {


			iterPos = iterPos->next;
		}
		return;
	}
};

class User {
private:
	string id;
	string pw;
public:
	SettingProperty mySetting;
	GroupProperty myGroups;

	User(string _id, string _pw) {
		id = _id;
		pw = _pw;
		mySetting = SettingProperty(0, 15);
		myGroups = GroupProperty();
	}

	User() {
		User("", "");
	}

	bool certify(string _id, string _pw) {
		return (id == _id) && (pw == _pw);
	}
};

class Stack {
private:
	static const int MAX_STACK_SIZE = 100;
	int top;
	int container[MAX_STACK_SIZE];
public:
	Stack(void) {
		top = -1;
		container[0] = 1;
	}

	bool isEmpty(void) {
		return top == -1;
	}

	bool isFull(void) {
		return (top == MAX_STACK_SIZE - 1);
	}

	void push(int item) {
		if (this->isFull()) {
			for (int i = 40; i < MAX_STACK_SIZE; i++) {
				container[i - 40] = container[i];
			}
		}
		else {
			container[++top] = item;
		}
		return;
	}

	int pop(void) {
		if (this->isEmpty()) {
			fprintf(stderr, "Stack Excess Error!\n");
			return 1;
		}
		else {
			return container[top--];
		}
	}

	int peek(void) {
		if (this->isEmpty()) {
			fprintf(stderr, "Stack Excess Error!\n");
			return 1;
		}
		else {
			return container[top];
		}
	}
};

// 罹晦睡攪 彌營⑽

typedef struct Node
{
	string Name;
	struct Node* next;
	struct Todo* Thead; //Todo ④萄 
	struct Todo* Ttail; //Todo 纔橾 
	int numOfTodo; //Todo 偃熱 
}Node;

typedef struct Todo {
	struct Todo* next;
	string Date;
	string Data;
}Todo;

class LinkedList // 渦嘐等檜攪 餌辨 翱唸葬蝶お 
{
private:
	Node* head;
	Node* tail;
	Node* cur;
	Node* before;
	int numOfList;//static戲煎 夥紱賊 縑楝陴 
	int selected;

public:
	LinkedList();
	void Insert(string name);
	void deleteList();
	void print();
	void editN(string name);
	void select(int n);
	void addTodo(string date, string data);
	void deleteTodo(int n);
	void deleteAllinList(Node* ln);
	void printTodo();
	void mergeList(int n);
	void sortTodo(Node* nd);
};


LinkedList::LinkedList() {
	tail = new Node;
	head = tail;
	tail->next = NULL;
	cur = NULL;
	before = NULL;
	numOfList = 0;
	selected = 0;
}

void LinkedList::Insert(string name) {
	Node* newNode = new Node;
	newNode->Name = name;
	newNode->next = NULL;

	newNode->Ttail = new Todo; //й 橾 蟾晦�� 
	newNode->Thead = newNode->Ttail;
	newNode->Ttail->next = NULL;
	newNode->numOfTodo = 0;

	tail->next = newNode;
	tail = newNode;
	numOfList++;
}

void LinkedList::deleteList() {//n廓簞 葬蝶お蒂 雖辦晦 
	if (selected < 1 || selected > numOfList) {//葬蝶お 摹鷗寰脾
		std::cout << "葬蝶お蒂 摹鷗п輿褊衛螃.\n";
		return;
	}
	Node* tmp = cur;
	before->next = before->next->next;
	if (selected == numOfList) tail = before; //裔 部 喻萄 餉薯塭賊 tail 偵褐 
	deleteAllinList(tmp);
	delete(tmp);
	--numOfList;
	cur = NULL;
	before = NULL;
	selected = 0;
}

void LinkedList::editN(string name)//n廓簞 葬蝶お曖 檜葷 熱薑 
{
	if (selected < 1 || selected > numOfList) {//葬蝶お 彰嬪 夤
		std::cout << "葬蝶お蒂 摹鷗п輿褊衛螃.\n";
		return;
	}
	cur->Name = name;
}

void LinkedList::print()
{
	Node* tmp = head->next;
	std::cout << "葬蝶お 跡煙: \n";
	if (tmp != NULL) { //п渡 喻萄陛 NULL檜 嬴棍陽 
		for (;;) {
			std::cout << tmp->Name;
			if (tmp->next == NULL) {
				printf("\n");
				break;
			}
			else cout << " -> ";
			tmp = tmp->next;
		}
	}
	else cout << "NO DATA";//NULL橾 陽 
}

void LinkedList::select(int n)
{
	if (n < 1 || n > numOfList) //葬蝶お 彰嬪 夤 
		std::cout << "п渡 嬪纂(" << n << ")縑 葬蝶お陛 襄營ж雖 彊蝗棲棻.\n";
	else {// 彰嬪 寰 
		before = head;
		int i = n;
		while (--i) before = before->next; //摹鷗й 喻萄 瞪梱雖 瓊嬴馬
		cur = before->next;
		selected = n;
	}
}

void LinkedList::addTodo(string date, string data)
{
	if (selected < 1 || selected > numOfList) {//葬蝶お 彰嬪 夤
		std::cout << "葬蝶お蒂 摹鷗п輿褊衛螃.\n";
		return;
	}
	Todo* newTodo = new Todo;
	newTodo->Date = date;
	newTodo->Data = data;
	newTodo->next = NULL;

	cur->Ttail->next = newTodo;
	cur->Ttail = newTodo;
	cur->numOfTodo++;
	sortTodo(cur);
}

void LinkedList::deleteAllinList(Node* ln)
{
	Todo* tmp = ln->Thead->next;
	Todo* s;
	if (tmp == NULL) return;
	while (tmp != ln->Ttail) {
		s = tmp;
		tmp = tmp->next;
		delete(s);
	}
	ln->Thead = ln->Ttail;
}

void LinkedList::deleteTodo(int n)
{
	if (n < 1 || n > cur->numOfTodo)//Todo 彰嬪 夤
		std::cout << "襄營ж雖 彊朝 Todo.\n";
	else {
		Todo* t;
		Todo* c = cur->Thead;
		int i = n;
		while (--i) c = c->next;

		t = c->next;
		c->next = c->next->next;
		if (n == cur->numOfTodo) cur->Ttail = c;

		free(t);
		--cur->numOfTodo;
	}
}

void LinkedList::printTodo()
{
	Todo* tmp = cur->Thead->next;
	cout << "斜瑜 " << cur->Name << "曖 Todo:\n";
	if (tmp != NULL) {
		for (;;) {
			cout << tmp->Date << ": " << tmp->Data << endl;
			if (tmp->next == NULL) break;
			tmp = tmp->next;
		}
	}
	else cout << "й 橾檜 橈蝗棲棻.\n";
}

void LinkedList::mergeList(int n)//摹鷗脹 葬蝶お蒂 n廓簞 葬蝶お縑 м藹
{
	if (selected < 1 || selected > numOfList) {//葬蝶お 彰嬪 夤
		cout << "葬蝶お蒂 摹鷗п輿褊衛螃.\n";
		return;
	}
	Node* tmp = head;
	Node* s = cur;
	int i = n;
	while (i--) tmp = tmp->next;
	if (s == tmp) {
		cout << "翕橾и 葬蝶お 摹鷗\n";
		return;
	}
	else {
		tmp->Ttail->next = s->Thead->next;
		tmp->Ttail = s->Ttail;
		tmp->numOfTodo += s->numOfTodo;
		before->next = before->next->next;
		if (cur->next == NULL) tail = before;
		delete(s);
		cur = NULL;
		before = NULL;
		selected = 0;
		numOfList--;
	}
	sortTodo(tmp);
}

void LinkedList::sortTodo(Node* nd) //摹鷗 薑溺 餌辨
{
	if (nd->numOfTodo == 1 || nd->numOfTodo == 0) return;//Todo陛 橈剪釭 ж釭夤縑 橈棻賊
	Todo* min_Todo = nd->Thead->next, * bf_min_Todo, * save_Todo = NULL, * count_Todo = nd->Thead->next, * bf_count_Todo = nd->Thead->next, * compare_Todo = NULL;
	compare_Todo = nd->Thead->next;
	for (int i = 0; i < nd->numOfTodo; i++) {
		for (int j = 0; j < nd->numOfTodo; j++) {
			if (compare_Todo->next == NULL) break;
			compare_Todo = compare_Todo->next;
			if (min_Todo->Date.compare(compare_Todo->Date) > 0) min_Todo = compare_Todo;
		}
		compare_Todo = min_Todo;
		if (min_Todo != count_Todo) {
			bf_min_Todo = nd->Thead->next;
			while (1) {
				if (bf_min_Todo->next == min_Todo) break;
				else bf_min_Todo = bf_min_Todo->next;
			}
			if (count_Todo == bf_min_Todo) {
				save_Todo = min_Todo->next;
				bf_count_Todo = nd->Thead->next;
				for (int k = 0; k < i - 1; k++) bf_count_Todo = bf_count_Todo->next;
				bf_count_Todo->next = min_Todo;
				min_Todo->next = count_Todo;
				count_Todo->next = save_Todo;
			}
			else {
				save_Todo = count_Todo->next;
				bf_min_Todo->next = count_Todo;
				min_Todo->next = save_Todo;
				if (count_Todo == nd->Thead->next) nd->Thead->next = min_Todo;
				else {
					bf_count_Todo = nd->Thead->next;
					for (int k = 0; k < i - 1; k++) bf_count_Todo = bf_count_Todo->next;
					bf_count_Todo->next = min_Todo;
				}
			}
			count_Todo = min_Todo->next;
			compare_Todo = count_Todo;
			min_Todo = count_Todo;
		}
	}

	int i = nd->numOfTodo;
	Todo* tmp = nd->Thead->next;
	while (--i)
		tmp = tmp->next;
	nd->Ttail = tmp;
	nd->Ttail->next = NULL;//Todo tail夥紱晦

	min_Todo = nd->Thead->next;
	bf_count_Todo = nd->Thead->next;
	count_Todo = nd->Thead->next;
	bf_min_Todo = nd->Thead->next;
	compare_Todo = NULL;
	save_Todo = NULL;
}

/*
int main(int argc, char** argv) {

	LinkedList list;
	int a, b;
	string ww, ee;

	list.Insert("濠猿掘褻");
	list.Insert("啞衛掘");
	list.Insert("摹渠熱");
	list.print();

	while (1) {
		cout << "葬蝶お 摹鷗: ";
		cin >> a;
		list.select(a);
		cout << "1. й 橾 蹺陛 2. 摹鷗и 葬蝶お м煽 3. 摹鷗и 葬蝶お 餉薯 4. 檜葷夥紱晦 5. й 橾 爾晦 -1. 謙猿\n";
		cin >> b;
		switch (b)
		{
		case 1:
			cout << "陳瞼 殮溘(YYYY-MM-DD): ";
			cin >> ww;
			cout << "й 橾 殮溘: ";
			cin >> ee;
			list.addTodo(ww, ee);
			break;
		case 2:
			cout << "м煽й 葬蝶お 殮溘: ";
			cin >> a;
			list.mergeList(a);
			list.print();
			break;
		case 3:
			list.deleteList();
			list.print();
			break;
		case 4:
			cout << "夥羚 檜葷 殮溘: ";
			cin >> ww;
			list.editN(ww);
			break;
		case 5:
			list.printTodo();
			break;
		case -1:
			return 0;
		}
	}

	return 0;
}
*/

// 瞪羲 滲熱 --------------------------------------------------------------
typedef pair<int, int> pii;
pii curSelect = { 0, 0 };
time_t trashTime;
bool isEnd = false;
User user = User();


// л熱 摹樹 --------------------------------------------------------------
void cursor_Draw(int x, int y, int sceneIndex, bool mode);
int input(int row, int col, int type);
void timePrint(void);
void sys_init(void);
void textOperator(int len, char text[], pii pos, bool hidden);

// Scene Func
int log_in(void);
int home(void);
int calender(void);
int group_task(void);
int setting(void);
int merge_user(void);
int FTM(void);
int group_management(void);
int current_group_task(void);
int set_group_property(void);
void try_initialize();

int(*scene[10])(void) = { log_in, home, calender, group_task, group_management, FTM, merge_user, setting, current_group_task, set_group_property };

// Design Func
void design_Default(void);

void design_log_in(void);
void design_home(void);
void design_calender(void);
void design_group_task(void);
void design_setting(void);
void additional_design_setting(void);
void design_merge_user(void);
void design_fast_task_manager(void);
void design_group_manager(void);
void design_current_group_task(void);
void design_set_group_property(void);

// л熱 薑曖 --------------------------------------------------------------

void hideCursor(bool show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//x高擊 2x煎 滲唳, 謝ル高縑 夥煎 僥濠翮擊 殮溘й 熱 氈紫煙 printfл熱 鳶殮
void pgotoxy(int x, int y, char* s) { 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

void pgotoxy(int x, int y, string s) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("%s", s);
}

int main(void) {
	Stack sceneHistory = Stack();
	sceneHistory.push(0);
	int nextSceneIndex = 0;
	bool isLogIn = false;
	sys_init();
	sceneHistory.push(log_in());
	do {
		gotoxy(0, 0);
		nextSceneIndex = scene[sceneHistory.peek()]();
		if (nextSceneIndex == BACK_SPACE) {
			sceneHistory.pop();
			nextSceneIndex = sceneHistory.peek();
		}
		else {
			sceneHistory.push(nextSceneIndex);
		}
	} while (nextSceneIndex != -1);
	return 0;
}

void sys_init(void) {
	system("Title Task Manager");
	system("color 0f");
	hideCursor(true);
	system("cls");
}

int log_in(void) {
	enum Status { ID, PW };
	Status status = ID;
	design_log_in();
	char id[13] = "            ";
	char pw[13] = "            ";
	switch (status) {
	case ID:
		textOperator(12, id, { 56, 16 }, false);
	case PW:
		textOperator(12, pw, { 56, 18 }, true);
		break;
	}
	user = User(id, pw);
	system("cls");
	return 1;
}


int home(void) {
	design_home();
	isEnd = false;
	thread paintT(timePrint);
	int direction = 0;
	do {
		cursor_Draw(curSelect.first, 0, 0, 1);
	    direction = input(5, 1, 0);
		cursor_Draw(curSelect.first, 0, 0, 0);
		Sleep(5);
		
		switch (direction) {
		case 'T': case 't':
			isEnd = true;
			paintT.join();
			system("cls");
			return 2;
		case 'G': case 'g':
			isEnd = true;
			paintT.join();
			system("cls");
			return 3;
		case 1: case -1:
			curSelect.first += direction;
			break;
		case ENTER:
			isEnd = true;
			paintT.join();
			system("cls");
			if (curSelect.first == 4) {
				return -1;
			}
			return 4 + curSelect.first;
		case BACK_SPACE:
			isEnd = true;
			paintT.join();
			system("cls");
			return BACK_SPACE;
		}
	} while (true);
}

void timePrint(void) {
	struct tm* curTime;
	while (!isEnd) {
		time_t curT = time(&trashTime);
		curTime = localtime(&curT);
		gotoxy(12, 2);
		printf("%02d:%02d:%02d", curTime->tm_hour, curTime->tm_min, curTime->tm_sec);
		Sleep(500);
	}
}

int calender(void) {
	int term;
	do {
		gotoxy(0, 0);
		design_calender();
		term = _getch();
	} while (term != 8);
	system("cls");
	return 1;
}

int group_task(void) {
	int term;
	do {
		gotoxy(0, 0);
		design_group_task();
		term = _getch();
	} while (term != 8);
	system("cls");
	return 1;
}

int setting(void) {
	design_setting();
	additional_design_setting();

	int direction = 0;
	int selected = -1;
	do {
		switch (selected) {
		case 0:
			user.mySetting.set_BGcolor(curSelect.first + (curSelect.second * 2));
			break;
		case 1:
			user.mySetting.set_textColor(curSelect.first + (curSelect.second * 2));
			break;
		}

		if (-1 < selected && selected < 3) {
			cursor_Draw(curSelect.first + (curSelect.second * 2), selected, 1, 1);
		}
		direction = input(2, 8, 0);
		if (-1 < selected && selected < 3) {
			cursor_Draw(curSelect.first + (curSelect.second * 2), selected, 1, 0);
		}
		Sleep(5);
		switch (direction) {
		case 'G': case 'g':
			curSelect = { 0, 0 };
			selected = 0;
			break;
		case 'T': case 't':
			curSelect = { 0, 0 };
			selected = 1;
			break;
		case 'I': case 'i':
			if (selected == 2) {
				user.mySetting.set_BGcolor(0);
				user.mySetting.set_textColor(15);
			}
			curSelect = { 0, 0 };
			selected = 2;
			break;
		case 'D': case 'd':
			try_initialize();
			gotoxy(0, 0);
			design_setting();
			additional_design_setting();
			curSelect = { 0, 0 };
			selected = 3;
			break;
		case 'B': case 'b':
			curSelect = { 0, 0 };
			system("cls");
			return 1;
		case 1: case -1:
			if (-1 < selected && selected < 2) {
				curSelect.first += direction;
			}
			break;
		case 2: case -2:
			if (-1 < selected && selected < 2) {
				curSelect.second += direction / 2;
			}
			break;
		}
	} while (true);
}

void additional_design_setting(void) {
	gotoxy(17, 6);
	printf("≒");
	gotoxy(25, 6);
	for (int i = 0; i < 16; i++) {
		if (i == 8) {
			gotoxy(25, 8);
		}
		printf("≒  ");
	}
	gotoxy(17, 11);
	printf("≒");
	gotoxy(25, 11);
	for (int i = 0; i < 16; i++) {
		if (i == 8) {
			gotoxy(25, 13);
		}
		printf("≒  ");
	}
}

void try_initialize() {
	enum Status { ID, PW };
	Status status = ID;
	char id[13] = "            ";
	char pw[13] = "            ";
	switch (status) {
	case ID:
		textOperator(12, id, { 27, 23 }, false);
	case PW:
		textOperator(12, pw, { 27, 25 }, true);
		break;
	}
	if (user.certify(id, pw)) {
		// 蟾晦��
		user.mySetting.set_BGcolor(0);
		user.mySetting.set_textColor(15);
	}
	return;
}

int merge_user(void) {
	int a;
	design_merge_user();
	scanf("%d", &a);
	system("cls");
	return 1;
}

int FTM(void) {
	design_fast_task_manager();

	int direction = 0;
	int selected = -1;
	do {

		if (-1 < selected && selected < 3) {
			cursor_Draw(curSelect.first + (curSelect.second * 3), 0, 2, 1);
		}
		direction = input(3, 8, 0);
		if (-1 < selected && selected < 3) {
			cursor_Draw(curSelect.first + (curSelect.second * 3), 0, 2, 0);
		}
		Sleep(5);
		switch (direction) {
		case 'A': case 'a':
			curSelect = { 0, 0 };
			selected = 0;
			break;
		case 'D': case 'd':
			curSelect = { 0, 0 };
			selected = 1;
			break;
		case 'M': case 'm':
			curSelect = { 0, 0 };
			selected = 2;
			break;
		case 'B': case 'b':
			curSelect = { 0, 0 };
			system("cls");
			return 1;
		// 鼻ж 檜翕
		case 1: case -1:
			if (-1 < selected && selected < 2) {
				curSelect.first += direction;
			}
			break;
		// む檜雖 檜翕
		case 2: case -2:
			if (-1 < selected && selected < 2) {
				curSelect.second += direction / 2;
			}
			break;
		}
	} while (true);
}

int group_management(void) {
	int a;
	design_group_manager();

	cin.ignore();
	scanf("%d", &a);
	system("cls");
	return 1;
}

int current_group_task(void) {
	int a;
	design_current_group_task();
	scanf("%d", &a);
	system("cls");
	return 1;
}

int set_group_property(void) {
	int a;
	design_set_group_property();
	scanf("%d", &a);
	system("cls");
	return 1;
}

void cursor_Draw(int x, int y, int sceneIndex, bool mode) {
	int row, col;
	int rowStart;
	int rowGap;
	int colStart;
	int colGap;
	switch (sceneIndex) {
	case 0:
		rowStart = 3;
		rowGap = 5;
		colStart = 87;
		colGap = 29;
		row = rowStart + x * 5;
		col = colStart;
		gotoxy(col, row);
		if (mode) printf("旨"); else printf(" ");
		gotoxy(col, row + rowGap);
		if (mode) printf("戌"); else printf(" ");
		gotoxy(col + colGap, row);
		if (mode) printf("忖"); else printf(" ");
		gotoxy(col + colGap, row + rowGap);
		if (mode) printf("戎"); else printf(" ");
		break;
	case 1:
		rowStart = 6;
		colStart = 23;
		colGap = 4;
		row = rowStart + (y * 5) + ((x % 2) * 2);
		col = colStart + ((x / 2) * 4);
		gotoxy(col, row);
		if (mode) printf("Ⅱ"); else printf(" ");
		gotoxy(col + colGap, row);
		if (mode) printf("９"); else printf(" ");
		break;
	}
}

void textOperator(int len, char text[], pii pos, bool hidden) {
	int curLen = 0;
	char term = 65;
	while (term != 13) {
		gotoxy(pos.first, pos.second);
		for (int i = 0; i < len; i++) {
			printf("%c", (i < curLen ? (hidden ? '*' : text[i]) : '_'));
		}
		term = _getch();
		if (term == 8 && curLen > 0) {
			text[curLen--] = ' ';
		}
		else if (curLen != len && 32 <= term && term <= 126) {
			text[curLen++] = term;
		}
	}
	return;
}

int input(int row, int column, int sceneNumber) // 褻濛晦棟擊 陛霞 л熱. 勒菟雖 葆衛螃.
{
	while (true)
	{
		int userSelect = _getch();
		if (userSelect == 0xE0 || userSelect == 0)
		{
			userSelect = _getch();
			if (userSelect == UP && curSelect.first > 0) // 嬪
			{
				return -1;
			}
			else if (userSelect == DOWN && curSelect.first < row - 1) // 嬴楚
			{
				return 1;
			}
			else if (userSelect == LEFT && column >= 2 && curSelect.second > 0) // 豭薹
			{
				return -row;
			}
			else if (userSelect == RIGHT && column >= 2 && curSelect.second < 7) // 螃艇薹
			{
				return row;
			}
		}
		else if (userSelect == 13 && sceneNumber != -1) // 縛攪酈
		{
			return ENTER;
		}
		else if (userSelect == 8 && (sceneNumber >= 1 || sceneNumber == -1)) // 寥蝶む檜蝶
		{
			return BACK_SPACE;
		}
		else if (userSelect == 9) // 龔 -> 顫檜ぎ
		{
			return 1234;
		}
		else {
			return userSelect;
		}
	}
}

void design_Default(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Default                                                                                                           早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_log_in(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Log In                                                                                                            早\n");
	printf("早 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                       Task Manager                                                  早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                       ____________                                                  早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                       ____________                                                  早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_home(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早旨收收收收收收收收收收收收收收收收收收收收收收收收旬旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬早\n");
	printf("早早 Calender          ( C )早早 Today                                              ( T )早早             MENU             早早\n");
	printf("早早                        早早                                                         早早                              早早\n");
	printf("早早                        早早                                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                        早早                                                         早早 早         斜瑜 婦葬        早 早早\n");
	printf("早早                        早早                                                         早早 早                          早 早早\n");
	printf("早早                        早早                                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                        早早                                                         早早                              早早\n");
	printf("早早                        早早                                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                        早早                                                         早早 早   Fast Task Management   早 早早\n");
	printf("早曲收收收收收收收收收收收收收收收收收收收收收收收收旭曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭早 早                          早 早早\n");
	printf("早旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早 Group Task                                                                   ( G )早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早         嶸盪 煽м        早 早早\n");
	printf("早早                                                                                   早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早          setting         早 早早\n");
	printf("早早                                                                                   早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早          log out         早 早早\n");
	printf("早早                                                                                   早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_setting(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬早\n");
	printf("早早   撲薑                                                                            早早             MENU             早早\n");
	printf("早早 收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收 早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早     ( G ) 寡唳 鏽楝      早 早早\n");
	printf("早早  寡唳 鏽楝   仃   Ⅱ    仃 仃                                                     早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早   ( T ) 臢蝶お 鏽楝      早 早早\n");
	printf("早早  臢蝶お 鏽楝 仃   Ⅱ    仃 仃                                                     早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早   ( I ) 撲薑 蟾晦��      早 早早\n");
	printf("早早  撲薑 蟾晦��      Ⅱ  ii                                                          早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早   ( D ) 等檜攪 蟾晦��    早 早早\n");
	printf("早早  等檜攪 蟾晦��   旨收收收收收收收收收收收收收收收收收收收收收收收收旬                                       早早 早                          早 早早\n");
	printf("早早                  早                        早                                       早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                  早  ID  仃                早                                       早早                              早早\n");
	printf("早早                  早                        早                                       早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                  早  PW  仃                早                                       早早 早      ( G ) 菴煎 陛晦     早 早早\n");
	printf("早早                  早                        早                                       早早 早                          早 早早\n");
	printf("早早                  曲收收收收收收收收收收收收收收收收收收收收收收收收旭                                       早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
// 13 6 / 13 11 / 13 16 / 13 21 -> 寡唳 鏽楝 臢蝶お 鏽楝 撲薑 蟾晦�� 等檜攪 蟾晦��
// 22 7 -> 24 7 ... 2噶 棺橫陴 謝ル (寡唳鏽楝 1)
// 5蘊噶 頂溥骨棲棻..
// ID PW 睡碟擎 23 / 11 , 25 / 11
// 仃朝 賦喱 謝ル 嬪纂 ル衛и剪歜 雖辦堅 ж撬

void design_calender(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Calender                                                                                                          早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_group_task(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Group Task                                                                                                        早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_merge_user(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Merge User                                                                                                        早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

void design_fast_task_manager(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早旨收收收收收收收收收收收收收收收收收收收收收收收收--收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬早\n");
	printf("早早                                         早                Result      <(1 / 2)>    早早             MENU             早早\n");
	printf("早早              Search / Add               早                                         早早                              早早\n");
	printf("早早                                         早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早  早 仃                                早  早早 早        ( A ) 蹺陛        早 早早\n");
	printf("早早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早早 早                          早 早早\n");
	printf("早早  早 仃                                早  早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早  早                                   早  早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早早                              早早\n");
	printf("早早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早  早 仃                                早  早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早早 早        ( D ) 餉薯        早 早早\n");
	printf("早早                                         早                                         早早 早                          早 早早\n");
	printf("早早                                         早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早  早 仃                                早  早早                              早早\n");
	printf("早早                                         早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早收收收收收收收收收收收收收收收收收收收收收收收收--收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收早早 早        ( M ) 熱薑        早 早早\n");
	printf("早早                                                                                   早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                                                                   早早 早       ( B ) 菴煎 陛晦    早 早早\n");
	printf("早早                                                                                   早早 早                          早 早早\n");
	printf("早早                                                                                   早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早早                                                                                   早早                              早早\n");
	printf("早曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

// search -> 7, 7
// result -> 49 ,5 縑憮 4蘊噶 頂溥馬
// �香嚂� -> 75, 3 檜剪 瞪羹陛 120檜賊 85

void design_group_manager(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早旨收收收收收收收收收收收收收收收收收收收收收收收收--收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬早\n");
	printf("早早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早早             MENU             早早\n");
	printf("早早  早  1. 仃                         仃 早  早  早  9. 仃                         仃 早  早早                              早早\n");
	printf("早早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早  旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬  早                                         早早 早 ( D ) ⑷營斜瑜 嬪纂滲唳  早 早早\n");
	printf("早早  早  2. 仃                         仃 早  早                                         早早 早                          早 早早\n");
	printf("早早  曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭  早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早                                         早早                              早早\n");
	printf("早早                                         早                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早                                         早早 早  ( T ) ⑷營斜瑜 鷓蝶觼   早 早早\n");
	printf("早早                                         早                                         早早 早                          早 早早\n");
	printf("早早                                         早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早                                         早早                              早早\n");
	printf("早早                                         早                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早                                         早早 早     ( M ) 斜瑜 煽м      早 早早\n");
	printf("早早                                         早                                         早早 早                          早 早早\n");
	printf("早早                                         早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早                                         早早                              早早\n");
	printf("早早                                         早                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早                                         早早 早   ( P ) 斜瑜 Щ煎ぷじ    早 早早\n");
	printf("早早                                         早                                         早早 早                          早 早早\n");
	printf("早早                                         早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早                                         早早                              早早\n");
	printf("早早                                         早                                         早早 旨收收收收收收收收收收收收收收收收收收收收收收收收收收旬 早早\n");
	printf("早早                                         早                                         早早 早     ( B ) 菴煎 陛晦      早 早早\n");
	printf("早早                                         早                                         早早 早                          早 早早\n");
	printf("早早                                         早                                         早早 曲收收收收收收收收收收收收收收收收收收收收收收收收收收旭 早早\n");
	printf("早早                                         早                                         早早                              早早\n");
	printf("早曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}

// 1 -> 11, 3, 37, 3
// 2 -> 11, 7, 37, 7
// 9 -> 51, 3, 77, 3

void design_current_group_task(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Current Group Task                                                                                                早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void design_set_group_property(void) {
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬\n");
	printf("早   Set Group Property                                                                                                早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("早                                                                                                                     早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}