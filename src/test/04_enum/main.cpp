#include <UDRefl/UDRefl.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::UDRefl;

enum class Color {
	Red,
	Green,
	Blue
};

int main() {
	Mngr.RegisterType<Color>();
	Mngr.AddField<Color::Red>("Red");
	Mngr.AddField<Color::Green>("Green");
	Mngr.AddField<Color::Blue>("Blue");


	for (const auto& [type, field, var] : Mngr.GetTypeFieldVars(Type_of<Color>)) {
		std::cout
			<< field.name.GetView()
			<< ": " << static_cast<int>(var.As<Color>())
			<< std::endl;
	}

	// enumerator -> name
	Color c = Color::Red;
	auto c_field = Mngr.FindField(Type_of<Color>, [c](FieldRef field) {
		return field.info.fieldptr.Var() == c;
	});

	std::cout << "name of " << static_cast<int>(c) << " : " << c_field.value().name.GetView() << std::endl;

	// name -> enumerator
	std::string_view name = "Green";
	auto name_field = Mngr.FindField(Type_of<Color>, [name](FieldRef field) {
		return field.name.GetView() == name;
	});

	std::cout << "value of " << name << " : " << static_cast<int>(name_field.value().info.fieldptr.Var().As<Color>()) << std::endl;
}
