#include "pch.h"
#include <google/protobuf/arena.h>
#include "person.pb.h"


TEST(arenaTest, simple)
{
	google::protobuf::Arena arena;
	auto message = google::protobuf::Arena::CreateMessage<AddressBook>(&arena);

	auto person = message->add_people();
	person->set_name("Jack");
	person = message->add_people();
	person->set_name("David");

	EXPECT_EQ(2, message->people().size());
	EXPECT_EQ("Jack", message->people()[0].name());
	EXPECT_EQ("David", message->people()[1].name());
}

TEST(arenaTest, SpaceAllocated_SpaceUsed)
{
	google::protobuf::Arena arena;
	std::vector<AddressBook*> data;
	data.reserve(1'000'000);

	for (auto i{ 0 }; i < 1'000'000; i++)
	{
		data.emplace_back(google::protobuf::Arena::CreateMessage<AddressBook>(&arena));
	}

	EXPECT_LT(sizeof(AddressBook) * 1'000'000, arena.SpaceAllocated());
	EXPECT_EQ(sizeof(AddressBook) * 1'000'000, arena.SpaceUsed());
}
