#include"defaultHeader.h"
#include"RingBuffer.h"

struct Test {
	int age = 0;
	char name[30]{};
	int id = 0;
};
int main()
{
	RingBuffer ringBuffer;

	while (1) {
		switch (rand()%3)
		{
		case 0: {
			Test t;

			for (int i = 0; i < rand() % 30; i++)
				t.name[i] = 'a' + rand() % 26;
			t.age = rand() % 100;
			t.id = rand();

			int ret = ringBuffer.Enqueue((char*)&t, sizeof(t));

			if (ret > 0) {
				cout << "Enqueue ";

				for (int i = 0; i < 30; ++i)
					cout << t.name[i];
				cout<< "\t" << t.id << "\t" << t.age;
				cout << endl;
				//cout << "Enqueue: " << str << endl;
			}
			else if(ret == 0)
				cout << "Enqueue zero data" << endl;
			else if(ret == -1)
				cout << "Enqueue err: overflow" << endl;

			break;
		}
		case 1: {
			//int str = 124;
			Test t;
			int ret = ringBuffer.Dequeue((char*)&t,sizeof(t));

			if (ret > 0) {
				cout << "Dequeue ";


				for (int i = 0; i < 30; ++i)
					cout << t.name[i];
				cout << "\t" << t.id << "\t" << t.age;
				cout << endl;
				//cout << "Dequeue: " << str << endl;
			}
			else if (ret == 0)
				cout << "Dequeue zero data" << endl;
			else if (ret == -1)
				cout << "Dequeue err: empty" << endl;
			else if (ret == -2)
				cout << "Dequeue err: underflow" << endl;

			break;
		}
		case 2: {
			Test t;

			int ret = ringBuffer.Peek((char*)&t, sizeof(t));

			if (ret > 0) {
				cout << "Peek: ";
				for (int i = 0; i < 30; ++i)
					cout << t.name[i];
				cout << "\t" << t.id << "\t" << t.age << endl;
			}
			else if (ret == 0)
				cout << "Peek zero data" << endl;
			else if (ret == -1)
				cout << "Peek err: empty" << endl;
			else if (ret == -2)
				cout << "Peek err: Peek over" << endl;
			break;
		}
		default:
			break;
		}
	}
}