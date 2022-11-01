#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

class Student
{
private:
    std::string m_first = "first";
    std::string m_last  = "last";
    int         m_id    = 0; // default value
    float       m_avg   = 0;

public:
    Student() = default;
    Student(const std::string& first, const std::string& last, int id,
            float avg)
        : m_first(first), m_last(last), m_id(id), m_avg(avg)
    {
    }

    int getAvg() const
    {
        return m_avg;
    }

    int getId() const
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }

    void print() const
    {
        std::cout << getId() << std::endl;
        std::cout << getFirst() << std::endl;
        std::cout << getLast() << std::endl;
        std::cout << getAvg() << std::endl;
        std::cout << std::endl;
    }
};

class Course
{
    std::string          m_name = "Course";
    std::vector<Student> m_students;

public:
    Course(const std::string& name) : m_name(name)
    {
    }

    void addStudent(const Student& student)
    {
        this->m_students.push_back(student);
    }

    const std::vector<Student>& getStudents() const
    {
        return m_students;
    }

    void print() const
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        std::string   first, last;
        int           id;
        float         avg;

        while (fin >> first)
        {
            fin >> last >> id >> avg;
            m_students.push_back(Student(first, last, id, avg));
        }
    }
};

int main()
{
    Course c("COMP 4300");
    c.loadFromFile("students.txt");
    c.print();
}
