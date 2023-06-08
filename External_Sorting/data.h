#pragma once

struct stor_str
{
	char data;
	int key;
	stor_str(char data = '\0', int key = 0) :data(data), key(key) {}
};