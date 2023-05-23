#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>
#include <condition_variable>

using TInfo = std::pair<int, int>;

class ThreadSafeQueue
{
private:
	// мьютекс для обеспечения эксклюзивного доступа
	// к элементам контейнера
	std::mutex mutex;
	std::queue<TInfo> queue;
public:
	void push(TInfo elem, int ID)
	{
		std::lock_guard<std::mutex> locker(mutex);
		queue.push(elem);
		std::cout << 'P' << ID << " -> " << elem.first << ' ' << elem.second << '\n';
	}
	bool try_pop(TInfo& elem, int ID)
	{
		bool result = false;
		std::lock_guard<std::mutex> locker(mutex);
		if (!queue.empty())
		{
			result = true;
			elem = queue.front();
			queue.pop();
			std::cout << 'C' << ID << " <- " << elem.first << ' ' << elem.second << '\n';
		}
		else
			std::cout << 'C' << ID << " sleep\n";
		return result;
	}
	bool empty()
	{
		return queue.empty();
	}
};
ThreadSafeQueue TSQ;
// мьютекс для метода wait()
std::mutex mut;
std::condition_variable cv;
const int N = 12;
volatile long volume_work_producer = N - 1;
volatile long volume_work_consumer = N - 1;
volatile long sorted = 1;

void task_producer(int* a, int start_index, int count, int ID)
{
	int i = start_index;
	// пока есть работа у потока-производителя
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0 && sorted)//&& i < N / 2 - 1)
	{
		// формируется элемент для последующей обработки
		// потоком-потребителем
		TInfo elem = TInfo(a[i], a[i + 1]);
		i += 2;
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		TSQ.push(elem, ID);
		// поток-производитель передает сигнал,
		// что в контейнере появился элемент для обработки
		cv.notify_all();
	}
}
void task_consumer(int ID)
{
	// пока есть работа у потока-потребителя
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0 && sorted)
	{
		TInfo elem;
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5),
			[]() {return !TSQ.empty(); });
		if (TSQ.try_pop(elem, ID))
		{
			// если элемент извлечен из контейнера,
			//то он обрабатывается потоком-потребителем
			long flag = 1;
			if (elem.first > elem.second)
				flag = 0;
			while (_InterlockedAnd(&sorted, flag) <= 0 && sorted)
				Sleep(0);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else
		{
			// работа не выполнена, объем работы потребителя
			// возвращается в исходное состояние
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

void init_array(int* arr, bool random = true)
{
	if (random)
	{
		for (size_t i = 0; i < N; i++)
			arr[i] = rand() % 100;
	}
	else
	{
		for (size_t i = 0; i < N; i++)
			std::cin >> arr[i];
	}
}

void print_array(int* a, int count)
{
	for (size_t i = 0; i < count; i++)
		std::cout << a[i] << ' ';
	std::cout << '\n';
}

int main()
{
	srand(GetTickCount());

	int* a = new int[N];

	init_array(a);
	//std::sort(a, a + N);
	print_array(a, N);

	std::thread worker[5];
	for (int i = 0; i < 2; i++)
		worker[i] = std::thread(task_producer, a, i, 2, i);

	for (int i = 2; i < 5; i++)
		worker[i] = std::thread(task_consumer, i);

	for (int i = 0; i < 5; i++)
		worker[i].join();

	std::cout << sorted << '\n';
	std::cin.get();
	return 0;
}