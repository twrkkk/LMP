#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using std::cin;
using std::cout;

using TInfo = int;

void bucketSort(std::vector<TInfo>& arr, bool ascending = true)
{
	TInfo minVal = arr[0], maxVal = arr[0];
	for (TInfo val : arr) {
		minVal = std::min(minVal, val);
		maxVal = std::max(maxVal, val);
	}

	int numBuckets = arr.size();
	std::vector<std::vector<TInfo>> buckets(numBuckets);

	for (TInfo val : arr)
	{
		int bucketIndex = (val - minVal) * (numBuckets - 1) / (maxVal - minVal);
		buckets[bucketIndex].push_back(val);
	}

	for (std::vector<TInfo>& bucket : buckets)
		std::sort(bucket.begin(), bucket.end());

	int index = ascending ? 0 : arr.size() - 1;
	for (std::vector<TInfo>& bucket : buckets) {
		for (TInfo val : bucket) {
			arr[ascending ? index++ : index--] = val;
		}
	}
}

int main() {
	cout << "Enter array size\n";
	int size;
	cin >> size;
	std::vector<TInfo> arr(size);
	TInfo min, max;
	cout << "Enter min value\n";
	cin >> min;
	cout << "Enter max value\n";
	cin >> max;
	srand(time(NULL));

	for (int i = 0; i < size; i++)
		arr[i] = min + rand() % (max - min + 1);

	for (TInfo val : arr)
		cout << val << " ";
	cout << '\n';
	bucketSort(arr, true);
	for (TInfo val : arr)
		cout << val << " ";
	cout << '\n';
}