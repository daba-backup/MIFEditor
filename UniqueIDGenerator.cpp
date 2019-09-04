#include"UniqueIDGenerator.h"

int daxie::tool::UniqueIDGenerator::count = 0;

int daxie::tool::UniqueIDGenerator::GetNextID() {
	int id = count;
	count++;

	return id;
}