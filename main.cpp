#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace nlohmann::literals;

namespace ns
{
    struct person
    {
        std::string name = "John Doe";
        std::string address = "123 Fake St";
        int age = -1;

        person() = default;
        person(std::string name_, std::string address_, int age_)
            : name(std::move(name_)), address(std::move(address_)), age(age_)
        {}
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(person, name, address, age)
}

// Function to save a person object to a JSON file
void save_to_file(const ns::person& p, const std::string& filename)
{
    json j = p;
    std::ofstream file(filename);
    file << j.dump(4); // 4 spaces for indentation
    file.close();
}

// Function to load a person object from a JSON file
ns::person load_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    json j;
    file >> j;
    return j.get<ns::person>();
}

int main()
{
    // Create a person object and serialize it to JSON
    ns::person p = {"Ned Flanders", "744 Evergreen Terrace", 60};
    save_to_file(p, "person.json");
    std::cout << "Saved Ned Flanders to file." << std::endl;

    // Load Homer Simpson from a JSON file and deserialize it
    ns::person loaded_person = load_from_file("homer_simpson.json");
    std::cout << "Loaded person from file: " << loaded_person.name << ", " 
              << loaded_person.address << ", " << loaded_person.age << std::endl;

    return 0;
}
