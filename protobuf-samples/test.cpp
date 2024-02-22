#include "pch.h"
#include "person.pb.h"

TEST(protobuf, set_get_optional_and_repeated)
{
	AddressBook address_book;

	Person* person = address_book.add_people();
	person->set_name("john doe");
	person->set_id(12345);
	person->set_email("john.doe@example.com");

	auto phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("123-456-7890");
	phoneNumber->set_type("HOME");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("987-654-3210");
	phoneNumber->set_type("OFFICE");

	person = address_book.add_people();
	person->set_name("david adamz");
	person->set_id(54321);
	person->set_email("david.adamz@example.com");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("357-654-3210");
	phoneNumber->set_type("PHONE");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("753-951-8520");
	phoneNumber->set_type("COMPANY");

	EXPECT_EQ(2, address_book.people().size());

	std::vector<int32_t> idTarget{ 12345, 54321 };
	std::vector<std::string> nameTarget{ "john doe", "david adamz" };
	std::vector<std::string> mailTarget{ "john.doe@example.com", "david.adamz@example.com" };
	std::vector<std::string> typeTarget{ "HOME", "OFFICE", "PHONE", "COMPANY"};
	std::vector<std::string> numberTarget{ "123-456-7890", "987-654-3210", "357-654-3210", "753-951-8520" };

	std::vector<int32_t> ids;
	std::vector<std::string> names;
	std::vector<std::string> mails;
	std::vector<std::string> types;
	std::vector<std::string> numbers;
	
	for (const auto& item : address_book.people())
	{
		ids.emplace_back(item.id());
		names.emplace_back(item.name());
		mails.emplace_back(item.email());

		for (const auto& phone : item.phone_numbers())
		{
			numbers.emplace_back(phone.number());
			types.emplace_back(phone.type());
		}
	}

	EXPECT_EQ(idTarget, ids);
	EXPECT_EQ(nameTarget, names);
	EXPECT_EQ(mailTarget, mails);
	EXPECT_EQ(numberTarget, numbers);
	EXPECT_EQ(typeTarget, types);
}

TEST(protobuf, debug_string)
{
	AddressBook address_book;

	Person* person = address_book.add_people();
	person->set_name("john doe");
	person->set_id(12345);
	person->set_email("john.doe@example.com");

	auto phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("123-456-7890");
	phoneNumber->set_type("HOME");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("987-654-3210");
	phoneNumber->set_type("OFFICE");

	person = address_book.add_people();
	person->set_name("david adamz");
	person->set_id(54321);
	person->set_email("david.adamz@example.com");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("357-654-3210");
	phoneNumber->set_type("PHONE");

	phoneNumber = person->add_phone_numbers();
	phoneNumber->set_number("753-951-8520");
	phoneNumber->set_type("COMPANY");

	std::stringstream msg;
	for (auto i{ 0 }; i < address_book.people().size(); i++)
	{
		msg << address_book.mutable_people(i)->DebugString();
	}

	auto debugTarget{ R"(name: "john doe"
id: 12345
email: "john.doe@example.com"
phone_numbers {
  number: "123-456-7890"
  type: "HOME"
}
phone_numbers {
  number: "987-654-3210"
  type: "OFFICE"
}
name: "david adamz"
id: 54321
email: "david.adamz@example.com"
phone_numbers {
  number: "357-654-3210"
  type: "PHONE"
}
phone_numbers {
  number: "753-951-8520"
  type: "COMPANY"
}
)" };

	EXPECT_EQ(debugTarget, msg.str());
}

TEST(protobuf, serialize_parse_str)
{
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

TEST(protobuf, serialize_parse_partial_array)
{
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