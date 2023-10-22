#include <iostream>
using namespace std;

class DateTime
{
    int day;
    int month;
    int year;

public:
    void SetDay(int day)
    {
        if (day > 0 && day <= 31) // TO DO: february 28-29, april june 30
        {
            this->day = day;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    int GetDay() const
    {
        return day;
    }

    void SetMonth(int month)
    {
        if (month >= 1 && month <= 12)
        {
            this->month = month;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    int GetMonth() const
    {
        return month;
    }

    void SetYear(int year)
    {
        this->year = year;
    }

    int GetYear() const
    {
        return year;
    }

    DateTime() {
        //cout << "DateTime c-tor without parameters\n";
        SetDay(11);
        SetMonth(10);
        SetYear(2023);
    }

    DateTime(int day, int month) {
        //cout << "DateTime c-tor with 2 parameters\n";
        SetDay(day);
        SetMonth(month);
        SetYear(2023);
    }

    DateTime(int day, int month, int year)
    {
        //cout << "DateTime main c-tor with 3 parameters\n";
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    DateTime(const DateTime& original)
    {
        //cout << "DateTime copy constructor\n";
        this->day = original.day;
        this->month = original.month;
        this->year = original.year;
    }

    ~DateTime() {
        //cout << "DateTime destructor\n";
    }

    void Print() const
    {
        cout << "Date: " << day << "." << month << "." << year << endl;
    }
};

class Student
{
    string name;
    string surname;
    DateTime birthday;
    DateTime study_start;

    int* hometask_rates = nullptr; // ПОЛЕ-ПОКАЖЧИК
    int hometask_rates_count = 0;

public:
    Student()
    {
        cout << "student constructor withour parameters\n";
        SetName("Oleksandr");
        SetSurname("Zahoruiko");
        SetBirthday({ 10, 10, 1989 });
        SetStudyStart({ 1, 9, 2022 });
    }

    // тiло КК для класу, яке створюе компiлятор за замовчуванням
    // поверхневе копiювання
    /* Student(const Student& original)
    {
        this->name = original.name;
        this->surname = original.surname;
        this->birthday = original.birthday;
        this->study_start = original.study_start;
        this->hometask_rates = original.hometask_rates; // проблема виникае саме тут - при копiюваннi адреси :500 з оригiналу до копii
        this->hometask_rates_count = original.hometask_rates_count;
    }*/

    // якщо в складi класу е поле-покажчик,
    // то потрiбно ОБОВ'ЯЗКОВО зробити ЯВНИЙ конструктор копiювання
    // в якому пiд усi поля-покажчики буде видiлена ОКРЕМА НОВА ДIЛЯНКА ПАМ'ЯТI
    Student(const Student& original)
    {
        cout << "student copy constructor\n";

        this->name = original.name;
        this->surname = original.surname;
        this->birthday = original.birthday;
        this->study_start = original.study_start;

        // приклад ГЛИБОКОГО КОПIЮВАННЯ
        this->hometask_rates_count = original.hometask_rates_count;

        // для полiв-покажчикiв буде окремий код, який видiляе нову пам'ять!!!!
        this->hometask_rates = new int[this->hometask_rates_count];
        // мало видiлити пам'ть, ii потрiбно ще й проiнiцiалiзувати!!!
        for (int i = 0; i < this->hometask_rates_count; i++)
        {
            this->hometask_rates[i] = original.hometask_rates[i];
        }
    }

    ~Student()
    {
        cout << "student destructor\n";
        if (hometask_rates != nullptr)
        {
            delete[] hometask_rates;
            hometask_rates = nullptr;
        }
    }

    void SetName(string name)
    {
        this->name = name;
    }

    string GetName() const
    {
        return name;
    }

private:
    void SetBirthday(const DateTime& birthday)
    {
        this->birthday = birthday;
    }

public:
    DateTime GetBirthday() const
    {
        return birthday;
    }

    void SetStudyStart(const DateTime& study_start)
    {
        this->study_start = study_start;
    }

    DateTime GetStudyStart() const
    {
        return study_start;
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    string GetSurname() const
    {
        return surname;
    }

    void AddHometaskRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (hometask_rates_count == 0)
        {
            hometask_rates = new int[1];
            hometask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[hometask_rates_count + 1];
            for (int i = 0; i < hometask_rates_count; i++)
                temp[i] = hometask_rates[i];
            temp[hometask_rates_count] = rate;
            delete[] hometask_rates;
            hometask_rates = temp;
        }
        hometask_rates_count++;
    }

    void PrintHometaskRates() const
    {
        cout << "Hometasks rates: ";
        for (int i = 0; i < hometask_rates_count; i++)
        {
            cout << hometask_rates[i] << ", ";
        }
        cout << "\n";
    }

    int GetHometaskRateByIndex(unsigned int index)
    {
        if (index >= hometask_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return hometask_rates[index];
    }

    int GetHometasksRatesCount() const
    {
        return hometask_rates_count;
    }
};

class Group
{
    Student* group;

public:
    void AddStudent(Student new_student)
    {
        // ...
    }

    Student GetStudentById(int id)
    {
        Student s;
        return s; // третiй приклад копiювання
    }
};

int main()
{
    Student original;

    original.AddHometaskRate(10);
    original.AddHometaskRate(11);
    original.AddHometaskRate(12);

    original.PrintHometaskRates();

    Student copy = original; // перший приклад копiювання

    copy.PrintHometaskRates();

    Group g;
    g.AddStudent(original); // другий приклад копiювання

    g.GetStudentById(5);
}