#include "pch.h"
#include "person.pb.h"

TEST(serialization, serialize_parse_str)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	AddressBook address_book;

	Person* person = address_book.add_people();
	person->set_name("john doe");
	person->set_id(12345);
	person->set_email("john.doe@example.com");

	person = address_book.add_people();
	person->set_name("david adamz");
	person->set_id(54321);
	person->set_email("david.adamz@example.com");

	auto serializeStr = address_book.SerializeAsString();

	AddressBook address_book2;
	address_book2.ParseFromString(serializeStr);

	auto main = address_book.DebugString();
	auto result = address_book2.DebugString();
	EXPECT_EQ(main, result);
}

TEST(serialization, serialize_parse_partial_array)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	AddressBook address_book;

	Person* person = address_book.add_people();
	person->set_name("john doe");
	person->set_id(12345);
	person->set_email("john.doe@example.com");

	person = address_book.add_people();
	person->set_name("david adamz");
	person->set_id(54321);
	person->set_email("david.adamz@example.com");


	std::vector<char> data(address_book.ByteSize(), ' ');
	auto res = address_book.SerializePartialToArray(data.data(), data.size());

	AddressBook address_book2;
	address_book2.ParsePartialFromArray(data.data(), data.size());

	auto main = address_book.DebugString();
	auto result = address_book2.DebugString();
	EXPECT_EQ(main, result);
}
