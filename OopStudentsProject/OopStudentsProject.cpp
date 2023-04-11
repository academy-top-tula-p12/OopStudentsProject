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

    friend bool operator<(const Student& s1, const Student& s2);
};

bool operator<(const Student& s1, const Student& s2)
{
    return s1.name < s2.name;
}

class ComparerAge
{
public:
    bool operator()(Student s1, Student s2)
    {
        return s1.GetAge() < s2.GetAge();
    }
};

class Group
{
    int size;
    Student* students;
public:
    Group() : size{ 0 }, students{ nullptr } {}

    int Size() { return size; }
    
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

    void Sort()
    {
        for (int i = 0; i < size; i++)
        {
            for(int j = size - 1; j > i; j--)
                if (students[j] < students[j - 1])
                {
                    Student temp = students[j];
                    students[j] = students[j - 1];
                    students[j - 1] = temp;
                }
        }
    }

    void Sort(ComparerAge operation)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = size - 1; j > i; j--)
                if (operation(students[j], students[j - 1]))
                {
                    Student temp = students[j];
                    students[j] = students[j - 1];
                    students[j - 1] = temp;
                }
        }
    }

    Student& At(int index)
    {
        return students[index];
    }
};

class Accumulator
{
    int acc;
public:
    Accumulator() : Accumulator(0) {}
    Accumulator(int init) : acc{ init } {}
    int operator()(int number)
    {
        return acc += number;
    }
};

void GroupPrint(Group group)
{
    for (int i = 0; i < group.Size(); i++)
        cout << group.At(i).GetName() 
             << " " 
             << group.At(i).GetAge() << "\n";

    cout << "\n";
}

int main()
{
    /*Accumulator acc;
    cout << acc(10) << "\n";
    cout << acc(30) << "\n";*/

    Group group;
    group.Add(Student("Bob", 23));
    group += Student("Joe", 34);
    group += Student("Ben", 19);
    group += Student("Tom", 26);
    group += Student("Sam", 32);

    GroupPrint(group);

    group.Sort();

    GroupPrint(group);

    group.Sort(ComparerAge());

    GroupPrint(group);
}
