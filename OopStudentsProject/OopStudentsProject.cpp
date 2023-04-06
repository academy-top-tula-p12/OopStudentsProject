#include <iostream>
#include <string>

using namespace std;

class Student
{
    string name;
    int age;
public:
    Student() : Student("", 0) {};

    Student(string name, int age) 
        : name{ name }, age{ age } {};
    string ToString()
    {
        return "Name: " + name + ", age: " + to_string(age);
    }
    void SetName(string name) { this->name = name; }
    string GetName() { return name; }

    void SetAge(int age) { this->age = age; }
    int GetAge() { return age; }
};

class Group
{
    int size;
    Student* students;
public:
    Group() : size{ 0 }, students{ nullptr } {}
    
    void Add(Student student)
    {
        Student* newgroup = new Student[size + 1];
        for (int i = 0; i < size; i++)
            newgroup[i] = students[i];
        newgroup[size] = student;
        delete[] students;

        students = newgroup;
        size++;
    }

    void Remove(string name, int age)
    {
        int index = 0;
        while (students[index].GetName() != name 
                    && students[index].GetAge() != age)
            index++;
        Student* newgroup = new Student[size - 1];
        for (int i = 0; i < index; i++)
            newgroup[i] = students[i];
        for (int i = index; i < size; i++)
            newgroup[i] = students[i + 1];

        delete[] students;
        students = newgroup;
        size--;
    }

    void operator+=(Student student)
    {
        this->Add(student);
    }
};

int main()
{
    Group group;
    group.Add(*(new Student("Bob", 23)));

    group += *(new Student("Joe", 34));
}
