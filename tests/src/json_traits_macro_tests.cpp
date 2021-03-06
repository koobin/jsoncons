// Copyright 2013 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif
#include <jsoncons/json.hpp>
#include <jsoncons/json_encoder.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>
#include <cstdint>

using namespace jsoncons;

namespace json_type_traits_macro_tests
{

    template <typename T1, typename T2>
    struct TemplatedStruct
    {
          T1 aT1;
          T2 aT2;
    };

    template <typename T1>
    struct MyStruct
    {
          T1 typeContent;
          std::string someString;
    };

    template <typename T1>
    struct MyStruct2
    {
          T1 typeContent;
          std::string someString;
    };

    template <typename T1>
    struct MyStruct3
    {
        T1 typeContent_;
        std::string someString_;
    public:
        MyStruct3(T1 typeContent, const std::string& someString)
            : typeContent_(typeContent), someString_(someString)
        {
        }

        const T1& typeContent() const {return typeContent_;}
        const std::string& someString() const {return someString_;}
    };

    struct book1a
    {
        std::string author;
        std::string title;
        double price;

        friend std::ostream& operator<<(std::ostream& os, const book1a& b)
        {
            std::cout << "author: " << b.author << ", title: " << b.title << ", price: " << b.price << "\n";
            return os;
        }
    };
    struct book1b
    {
        std::string author;
        std::string title;
        double price;
        std::string isbn;
    };
    struct book1c
    {
        std::string author;
        std::string title;
        double price;
        jsoncons::optional<std::string> isbn;
    };

    class book2a
    {
        std::string author_;
        std::string title_;
        double price_;
    public:
        book2a(const std::string& author,
              const std::string& title,
              double price)
            : author_(author), title_(title), price_(price)
        {
        }

        book2a(const book2a&) = default;
        book2a(book2a&&) = default;
        book2a& operator=(const book2a&) = default;
        book2a& operator=(book2a&&) = default;

        const std::string& author() const
        {
            return author_;
        }

        const std::string& title() const
        {
            return title_;
        }

        double price() const
        {
            return price_;
        }
    };

    class book2b
    {
        std::string author_;
        std::string title_;
        double price_;
        std::string isbn_;
    public:
        book2b(const std::string& author,
              const std::string& title,
              double price,
              const std::string& isbn)
            : author_(author), title_(title), price_(price), isbn_(isbn)
        {
        }

        book2b(const book2b&) = default;
        book2b(book2b&&) = default;
        book2b& operator=(const book2b&) = default;
        book2b& operator=(book2b&&) = default;

        const std::string& author() const
        {
            return author_;
        }

        const std::string& title() const
        {
            return title_;
        }

        double price() const
        {
            return price_;
        }

        const std::string& isbn() const
        {
            return isbn_;
        }
    };

    class book3a
    {
        std::string author_;
        std::string title_;
        double price_;
    public:
        book3a()
            : author_(), title_(), price_()
        {
        }

        book3a(const book3a&) = default;
        book3a(book3a&&) = default;
        book3a& operator=(const book3a&) = default;
        book3a& operator=(book3a&&) = default;

        const std::string& getAuthor() const
        {
            return author_;
        }

        void setAuthor(const std::string& value)
        {
            author_ = value;
        }

        const std::string& getTitle() const
        {
            return title_;
        }

        void setTitle(const std::string& value)
        {
            title_ = value;
        }

        double getPrice() const
        {
            return price_;
        }

        void setPrice(double value)
        {
            price_ = value;
        }
    };

    class book3b
    {
        std::string author_;
        std::string title_;
        double price_;
        std::string isbn_;
    public:
        book3b()
            : author_(), title_(), price_(), isbn_()
        {
        }

        book3b(const book3b&) = default;
        book3b(book3b&&) = default;
        book3b& operator=(const book3b&) = default;
        book3b& operator=(book3b&&) = default;

        const std::string& getAuthor() const
        {
            return author_;
        }

        void setAuthor(const std::string& value)
        {
            author_ = value;
        }

        const std::string& getTitle() const
        {
            return title_;
        }

        void setTitle(const std::string& value)
        {
            title_ = value;
        }

        double getPrice() const
        {
            return price_;
        }

        void setPrice(double value)
        {
            price_ = value;
        }

        const std::string& getIsbn() const
        {
            return isbn_;
        }

        void setIsbn(const std::string& value)
        {
            isbn_ = value;
        }
    };

    class book3c
    {
        std::string author_;
        std::string title_;
        double price_;
        jsoncons::optional<std::string> isbn_;
    public:
        book3c()
            : author_(), title_(), price_(), isbn_()
        {
        }

        book3c(const book3c&) = default;
        book3c(book3c&&) = default;
        book3c& operator=(const book3c&) = default;
        book3c& operator=(book3c&&) = default;

        const std::string& getAuthor() const
        {
            return author_;
        }

        void setAuthor(const std::string& value)
        {
            author_ = value;
        }

        const std::string& getTitle() const
        {
            return title_;
        }

        void setTitle(const std::string& value)
        {
            title_ = value;
        }

        double getPrice() const
        {
            return price_;
        }

        void setPrice(double value)
        {
            price_ = value;
        }

        const jsoncons::optional<std::string>& getIsbn() const
        {
            return isbn_;
        }

        void setIsbn(const jsoncons::optional<std::string>& value)
        {
            isbn_ = value;
        }
    };

    enum class float_format {scientific = 1,fixed = 2,hex = 4,general = fixed | scientific};

    class Employee
    {
        std::string firstName_;
        std::string lastName_;
    public:
        Employee(const std::string& firstName, const std::string& lastName)
            : firstName_(firstName), lastName_(lastName)
        {
        }
        virtual ~Employee() = default;

        virtual double calculatePay() const = 0;

        const std::string& firstName() const {return firstName_;}
        const std::string& lastName() const {return lastName_;}
    };

    class HourlyEmployee : public Employee
    {
        double wage_;
        unsigned hours_;
    public:
        HourlyEmployee(const std::string& firstName, const std::string& lastName, 
                       double wage, unsigned hours)
            : Employee(firstName, lastName), 
              wage_(wage), hours_(hours)
        {
        }
        HourlyEmployee(const HourlyEmployee&) = default;
        HourlyEmployee(HourlyEmployee&&) = default;
        HourlyEmployee& operator=(const HourlyEmployee&) = default;
        HourlyEmployee& operator=(HourlyEmployee&&) = default;

        double wage() const {return wage_;}

        unsigned hours() const {return hours_;}

        double calculatePay() const override
        {
            return wage_*hours_;
        }
    };

    class CommissionedEmployee : public Employee
    {
        double baseSalary_;
        double commission_;
        unsigned sales_;
    public:
        CommissionedEmployee(const std::string& firstName, const std::string& lastName, 
                             double baseSalary, double commission, unsigned sales)
            : Employee(firstName, lastName), 
              baseSalary_(baseSalary), commission_(commission), sales_(sales)
        {
        }
        CommissionedEmployee(const CommissionedEmployee&) = default;
        CommissionedEmployee(CommissionedEmployee&&) = default;
        CommissionedEmployee& operator=(const CommissionedEmployee&) = default;
        CommissionedEmployee& operator=(CommissionedEmployee&&) = default;

        double baseSalary() const
        {
            return baseSalary_;
        }

        double commission() const
        {
            return commission_;
        }

        unsigned sales() const
        {
            return sales_;
        }

        double calculatePay() const override
        {
            return baseSalary_ + commission_*sales_;
        }
    };

    enum class hiking_experience {beginner,intermediate,advanced};

    struct hiking_reputon
    {
        std::string rater;
        hiking_experience assertion;
        std::string rated;
        double rating;

        friend bool operator==(const hiking_reputon& lhs, const hiking_reputon& rhs)
        {
            return lhs.rater == rhs.rater && lhs.assertion == rhs.assertion && 
                   lhs.rated == rhs.rated && lhs.rating == rhs.rating;
        }

        friend bool operator!=(const hiking_reputon& lhs, const hiking_reputon& rhs)
        {
            return !(lhs == rhs);
        };
    };

    class hiking_reputation
    {
        std::string application;
        std::vector<hiking_reputon> reputons;

        // Make json_type_traits specializations friends to give accesses to private members
        JSONCONS_TYPE_TRAITS_FRIEND

        hiking_reputation()
        {
        }
    public:
        hiking_reputation(const std::string& application, const std::vector<hiking_reputon>& reputons)
            : application(application), reputons(reputons)
        {}

        friend bool operator==(const hiking_reputation& lhs, const hiking_reputation& rhs)
        {
            return (lhs.application == rhs.application) && (lhs.reputons == rhs.reputons);
        }

        friend bool operator!=(const hiking_reputation& lhs, const hiking_reputation& rhs)
        {
            return !(lhs == rhs);
        };
    };
} // namespace json_type_traits_macro_tests
 
namespace ns = json_type_traits_macro_tests;

JSONCONS_ENUM_TRAITS(ns::float_format, scientific, fixed, hex, general)
JSONCONS_ALL_MEMBER_TRAITS(ns::book1a,author,title,price)
JSONCONS_N_MEMBER_TRAITS(ns::book1b,3,author,title,price,isbn)
JSONCONS_N_MEMBER_TRAITS(ns::book1c,3,author,title,price,isbn)

JSONCONS_ALL_GETTER_CTOR_TRAITS(ns::book2a, author, title, price)
JSONCONS_N_GETTER_CTOR_TRAITS(ns::book2b, 2, author, title, price, isbn)
JSONCONS_TPL_ALL_MEMBER_TRAITS(1,ns::MyStruct,typeContent,someString)
JSONCONS_TPL_ALL_MEMBER_TRAITS(1,ns::MyStruct2,typeContent,someString)
JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS(1,ns::MyStruct3,typeContent,someString)
JSONCONS_TPL_ALL_MEMBER_TRAITS(2,ns::TemplatedStruct,aT1,aT2)

JSONCONS_ALL_GETTER_CTOR_TRAITS(ns::HourlyEmployee, firstName, lastName, wage, hours)
JSONCONS_ALL_GETTER_CTOR_TRAITS(ns::CommissionedEmployee, firstName, lastName, baseSalary, commission, sales)
JSONCONS_POLYMORPHIC_TRAITS(ns::Employee, ns::HourlyEmployee, ns::CommissionedEmployee)

JSONCONS_ALL_GETTER_SETTER_TRAITS(ns::book3a, get, set, Author, Title, Price)
JSONCONS_N_GETTER_SETTER_TRAITS(ns::book3b, get, set, 2, Author, Title, Price, Isbn)
JSONCONS_N_GETTER_SETTER_TRAITS(ns::book3c, get, set, 2, Author, Title, Price, Isbn)

JSONCONS_ENUM_TRAITS(ns::hiking_experience, beginner, intermediate, advanced)
JSONCONS_ALL_MEMBER_TRAITS(ns::hiking_reputon, rater, assertion, rated, rating)
JSONCONS_ALL_MEMBER_TRAITS(ns::hiking_reputation, application, reputons)

void test_is_json_type_traits_declared(std::true_type)
{
}

TEST_CASE("JSONCONS_ALL_MEMBER_TRAITS tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;

    ns::book1a book{an_author, a_title, a_price};

    CHECK(jsoncons::is_json_type_traits_declared<ns::book1a>::value);
    test_is_json_type_traits_declared(jsoncons::is_json_type_traits_declared<ns::book1a>());

    SECTION("book1a")
    {
        std::string s;

        encode_json(book, s);

        json j = decode_json<json>(s);

        REQUIRE(j.is<ns::book1a>() == true);
        REQUIRE(j.is<ns::book1b>() == true); // isbn is optional

        CHECK(j["author"].as<std::string>() == an_author);
        CHECK(j["title"].as<std::string>() == a_title);
        CHECK(j["price"].as<double>() == Approx(a_price).epsilon(0.001));

        json j2(book);

        CHECK(j == j2);

        ns::book1a val = j.as<ns::book1a>();

        CHECK(val.author == book.author);
        CHECK(val.title == book.title);
        CHECK(val.price == Approx(book.price).epsilon(0.001));
    }
}

TEST_CASE("JSONCONS_N_MEMBER_TRAITS with optional tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;
    std::string an_isbn = "1400079276";

    SECTION("book1c no isbn")
    {
        ns::book1c book{an_author, a_title, a_price, jsoncons::optional<std::string>{}};

        CHECK(jsoncons::is_json_type_traits_declared<ns::book1c>::value);
        std::string s;

        encode_json(book, s);

        json j = decode_json<json>(s);

        REQUIRE(j.is<ns::book1a>() == true);
        REQUIRE(j.is<ns::book1b>() == true); // isbn is optional

        CHECK(j["author"].as<std::string>() == an_author);
        CHECK(j["title"].as<std::string>() == a_title);
        CHECK(j["price"].as<double>() == Approx(a_price).epsilon(0.001));
        CHECK_FALSE(j.contains("isbn"));

        json j2(book);

        CHECK(j == j2);

        auto val = j.as<ns::book1c>();

        CHECK(val.author == book.author);
        CHECK(val.title == book.title);
        CHECK(val.price == Approx(book.price).epsilon(0.001));
        CHECK_FALSE(val.isbn.has_value());
    }

    SECTION("book1c has isbn")
    {
        ns::book1c book{an_author, a_title, a_price, an_isbn};

        CHECK(jsoncons::is_json_type_traits_declared<ns::book1c>::value);
        std::string s;

        encode_json(book, s);

        json j = decode_json<json>(s);

        REQUIRE(j.is<ns::book1a>() == true);
        REQUIRE(j.is<ns::book1b>() == true); 

        CHECK(j["author"].as<std::string>() == an_author);
        CHECK(j["title"].as<std::string>() == a_title);
        CHECK(j["price"].as<double>() == Approx(a_price).epsilon(0.001));
        REQUIRE(j.contains("isbn"));
        CHECK(j["isbn"].as<std::string>() == an_isbn);

        json j2(book);

        CHECK(j == j2);

        auto val = j.as<ns::book1c>();

        CHECK(val.author == book.author);
        CHECK(val.title == book.title);
        CHECK(val.price == Approx(book.price).epsilon(0.00001));
        CHECK(val.isbn.has_value());
        CHECK(val.isbn == an_isbn);
    }
}

TEST_CASE("JSONCONS_ALL_GETTER_CTOR_TRAITS tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;

    SECTION("is")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;
        j["price"] = a_price;

        bool val = j.is<ns::book2a>();
        CHECK(val == true);
    }
    SECTION("to_json")
    {
        ns::book2a book(an_author,a_title,a_price);

        json j(book);

        CHECK(j["author"].as<std::string>() == an_author);
        CHECK(j["title"].as<std::string>() == a_title);
        CHECK(j["price"].as<double>() == Approx(a_price).epsilon(0.001));
    }

    SECTION("as")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;
        j["price"] = a_price;

        ns::book2a book = j.as<ns::book2a>();

        CHECK(book.author() == an_author);
        CHECK(book.title() == a_title);
        CHECK(book.price() == Approx(a_price).epsilon(0.001));
    }
}

TEST_CASE("JSONCONS_N_GETTER_CTOR_TRAITS tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;
    std::string an_isbn = "1400079276";

    SECTION("is")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;

        CHECK(j.is<ns::book2b>() == true);
        CHECK(j.is<ns::book2a>() == false); // has author, title, but not price

        j["price"] = a_price;
        CHECK(j.is<ns::book2a>() == true); // has author, title, price
    }

    SECTION("to_json")
    {
        ns::book2b book(an_author,a_title,a_price,an_isbn);

        json j(book);

        CHECK(j["author"].as<std::string>() == an_author);
        CHECK(j["title"].as<std::string>() == a_title);
        CHECK(j["price"].as<double>() == Approx(a_price).epsilon(0.001));
        CHECK(j["isbn"].as<std::string>() == an_isbn);
    }

    SECTION("as")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;
        j["price"] = a_price;

        ns::book2b book = j.as<ns::book2b>();

        CHECK(book.author() == an_author);
        CHECK(book.title() == a_title);
        CHECK(book.price() == Approx(a_price).epsilon(0.001));
    }
    SECTION("decode")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;

        std::string buffer;
        j.dump(buffer);
        auto book = decode_json<ns::book2b>(buffer);
        CHECK(book.author() == an_author);
        CHECK(book.title() == a_title);
        CHECK(book.price() == double());
        CHECK(book.isbn() == std::string());
    }
}

TEST_CASE("JSONCONS_TPL_ALL_MEMBER_TRAITS tests")
{
    SECTION("MyStruct<std::pair<int,int>>")
    {
        typedef ns::MyStruct<std::pair<int, int>> value_type;

        value_type val;
        val.typeContent = std::make_pair(1,2);
        val.someString = "A string";

        std::string s;
        encode_json(val, s, indenting::indent);

        auto val2 = decode_json<value_type>(s);

        CHECK(val2.typeContent.first == val.typeContent.first);
        CHECK(val2.typeContent.second == val.typeContent.second);
        CHECK(val2.someString == val.someString);

        //std::cout << val.typeContent.first << ", " << val.typeContent.second << ", " << val.someString << "\n";
    }
    SECTION("TemplatedStruct<int,double>")
    {
        typedef ns::TemplatedStruct<int,double> value_type;

        value_type val;
        val.aT1 = 1;
        val.aT2 = 2;

        std::string s;
        encode_json(val, s, indenting::indent);

        auto val2 = decode_json<value_type>(s);

        CHECK(val2.aT1 == val.aT1);
        CHECK(val2.aT2 == val.aT2);

        //std::cout << val.typeContent.first << ", " << val.typeContent.second << ", " << val.someString << "\n";
    }
    SECTION("TemplatedStruct<int,wstring>")
    {
        typedef ns::TemplatedStruct<int,std::wstring> value_type;

        value_type val;
        val.aT1 = 1;
        val.aT2 = L"sss";

        std::wstring s;
        encode_json(val, s, indenting::indent);

        auto val2 = decode_json<value_type>(s);

        CHECK(val2.aT1 == val.aT1);
        CHECK(val2.aT2 == val.aT2);

        //std::cout << val.typeContent.first << ", " << val.typeContent.second << ", " << val.someString << "\n";
    }
}

TEST_CASE("JSONCONS_TPL_ALL_GETTER_CTOR_TRAITS tests")
{
    SECTION("MyStruct<std::pair<int,int>>")
    {
        typedef ns::MyStruct3<std::pair<int, int>> value_type;

        value_type val(std::make_pair(1,2), "A string");

        std::string s;
        encode_json(val, s, indenting::indent);

        auto val2 = decode_json<value_type>(s);

        CHECK(val2.typeContent().first == val.typeContent().first);
        CHECK(val2.typeContent().second == val.typeContent().second);
        CHECK(val2.someString() == val.someString());

        //std::cout << val.typeContent.first << ", " << val.typeContent.second << ", " << val.someString << "\n";
    }
}

TEST_CASE("JSONCONS_ENUM_TRAITS tests")
{
    SECTION("float_format default")
    {
        ns::float_format val{ns::float_format::hex};

        std::string s;
        encode_json(val,s);

        auto val2 = decode_json<ns::float_format>(s);
        CHECK(val2 == val);
    }
    SECTION("float_format hex")
    {
        ns::float_format val{ns::float_format()};

        std::string s;
        encode_json(val,s);

        auto val2 = decode_json<ns::float_format>(s);
        CHECK(val2 == val);
    }
    SECTION("float_format default L")
    {
        ns::float_format val{ns::float_format::hex};

        std::wstring s;
        encode_json(val,s);

        auto val2 = decode_json<ns::float_format>(s);
        CHECK(val2 == val);
    }
    SECTION("float_format hex L")
    {
        ns::float_format val{ns::float_format::hex};

        std::wstring s;
        encode_json(val,s);

        auto val2 = decode_json<ns::float_format>(s);
        CHECK(val2 == val);
    }
}

TEST_CASE("JSONCONS_POLYMORPHIC_TRAITS tests")
{
    std::string input = R"(
[
    {
        "firstName": "John",
        "hours": 1000,
        "lastName": "Smith",
        "wage": 40.0
    },
    {
        "baseSalary": 30000.0,
        "commission": 0.25,
        "firstName": "Jane",
        "lastName": "Doe",
        "sales": 1000
    }
]
    )"; 

    const std::string firstName0 = "John";
    const std::string lastName0 = "Smith";
    const double pay0 = 40000;
    const std::string firstName1 = "Jane";
    const std::string lastName1 = "Doe";
    const double pay1 = 30250;

    SECTION("decode vector of shared_ptr test")
    {
        auto v = jsoncons::decode_json<std::vector<std::shared_ptr<ns::Employee>>>(input);
        REQUIRE(v.size() == 2);
        CHECK(v[0]->firstName() == firstName0);
        CHECK(v[0]->lastName() == lastName0);
        CHECK(v[0]->calculatePay() == pay0);
        CHECK(v[1]->firstName() == firstName1);
        CHECK(v[1]->lastName() == lastName1);
        CHECK(v[1]->calculatePay() == pay1);
    }

    SECTION("decode vector of unique_ptr test")
    {

        auto v = jsoncons::decode_json<std::vector<std::unique_ptr<ns::Employee>>>(input);
        REQUIRE(v.size() == 2);
        CHECK(v[0]->firstName() == firstName0);
        CHECK(v[0]->lastName() == lastName0);
        CHECK(v[0]->calculatePay() == pay0);
        CHECK(v[1]->firstName() == firstName1);
        CHECK(v[1]->lastName() == lastName1);
        CHECK(v[1]->calculatePay() == pay1);
    }
    SECTION("encode vector of shared_ptr test")
    {
        std::vector<std::shared_ptr<ns::Employee>> v;

        v.push_back(std::make_shared<ns::HourlyEmployee>("John", "Smith", 40.0, 1000));
        v.push_back(std::make_shared<ns::CommissionedEmployee>("Jane", "Doe", 30000, 0.25, 1000));

        jsoncons::json j(v);

        json expected = json::parse(input);
        CHECK(j == expected);
    }
    SECTION("encode vector of unique_ptr test")
    {
        std::vector<std::unique_ptr<ns::Employee>> v;

        v.emplace_back(new ns::HourlyEmployee("John", "Smith", 40.0, 1000));
        v.emplace_back(new ns::CommissionedEmployee("Jane", "Doe", 30000, 0.25, 1000));

        jsoncons::json j(v);

        json expected = json::parse(input);
        CHECK(j == expected);
    }
}

TEST_CASE("JSONCONS_N_GETTER_SETTER_TRAITS tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;

    SECTION("is")
    {
        json j;
        j["Author"] = an_author;
        j["Title"] = a_title;
        j["Price"] = a_price;

        bool val = j.is<ns::book3a>();
        CHECK(val == true);
    }
    SECTION("to_json")
    {
        ns::book3a book;
        book.setAuthor(an_author);
        book.setTitle(a_title);
        book.setPrice(a_price);

        json j(book);

        CHECK(j["Author"].as<std::string>() == an_author);
        CHECK(j["Title"].as<std::string>() == a_title);
        CHECK(j["Price"].as<double>() == Approx(a_price).epsilon(0.001));
    }

    SECTION("as")
    {
        json j;
        j["Author"] = an_author;
        j["Title"] = a_title;
        j["Price"] = a_price;

        ns::book3a book = j.as<ns::book3a>();

        CHECK(book.getAuthor() == an_author);
        CHECK(book.getTitle() == a_title);
        CHECK(book.getPrice() == Approx(a_price).epsilon(0.001));
    }
    SECTION("decode")
    {
        json j;
        j["author"] = an_author;
        j["title"] = a_title;
        j["price"] = a_price;

        std::string buffer;
        j.dump(buffer);
        auto book = decode_json<ns::book2b>(buffer);
        CHECK(book.author() == an_author);
        CHECK(book.title() == a_title);
        CHECK(book.price() == a_price);
    }
}

TEST_CASE("JSONCONS_ALL_GETTER_SETTER_TRAITS tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;
    std::string an_isbn = "1400079276";

    SECTION("is")
    {
        json j;
        j["Author"] = an_author;
        j["Title"] = a_title;

        CHECK(j.is<ns::book3b>() == true);
        CHECK(j.is<ns::book3a>() == false);

        j["Price"] = a_price;

        CHECK(j.is<ns::book3b>() == true);
        CHECK(j.is<ns::book3a>() == true);
    }
    SECTION("to_json")
    {
        ns::book3b book;
        book.setAuthor(an_author);
        book.setTitle(a_title);
        book.setPrice(a_price);
        book.setIsbn(an_isbn);

        json j(book);

        CHECK(j["Author"].as<std::string>() == an_author);
        CHECK(j["Title"].as<std::string>() == a_title);
        CHECK(j["Price"].as<double>() == Approx(a_price).epsilon(0.001));
        CHECK(j["Isbn"].as<std::string>() == an_isbn);
    }

    SECTION("as")
    {
        json j;
        j["Author"] = an_author;
        j["Title"] = a_title;
        j["Price"] = a_price;

        auto book = j.as<ns::book3b>();

        CHECK(book.getAuthor() == an_author);
        CHECK(book.getTitle() == a_title);
        CHECK(book.getPrice() == Approx(a_price).epsilon(0.001));
    }
    SECTION("decode")
    {
        json j;
        j["Author"] = an_author;
        j["Title"] = a_title;

        std::string buffer;
        j.dump(buffer);
        auto book = decode_json<ns::book3b>(buffer);
        CHECK(book.getAuthor() == an_author);
        CHECK(book.getTitle() == a_title);
        CHECK(book.getPrice() == double());
        CHECK(book.getIsbn() == std::string());
    }
}

TEST_CASE("JSONCONS_ALL_GETTER_SETTER_TRAITS optional tests")
{
    std::string an_author = "Haruki Murakami"; 
    std::string a_title = "Kafka on the Shore";
    double a_price = 25.17;
    std::string an_isbn = "1400079276";

    SECTION("book3c no isbn")
    {
        ns::book3c book;
        book.setAuthor(an_author);
        book.setTitle(a_title);
        book.setPrice(a_price);

        std::string input;
        encode_json(book,input);
        
        auto b1 = decode_json<ns::book3c>(input);
        CHECK(b1.getAuthor() == an_author);
        CHECK(b1.getTitle() == a_title);
        CHECK(b1.getPrice() == a_price);
        CHECK_FALSE(b1.getIsbn().has_value());
    }

    SECTION("book3c has isbn")
    {
        ns::book3c book;
        book.setAuthor(an_author);
        book.setTitle(a_title);
        book.setPrice(a_price);
        book.setIsbn(an_isbn);

        std::string input;
        encode_json(book,input);

        auto b1 = decode_json<ns::book3c>(input);
        CHECK(b1.getAuthor() == an_author);
        CHECK(b1.getTitle() == a_title);
        CHECK(b1.getPrice() == Approx(a_price).epsilon(0.00001));
        CHECK(b1.getIsbn() == an_isbn);
    }
}

TEST_CASE("hiking_reputation")
{
    ns::hiking_reputation val("hiking", { ns::hiking_reputon{"HikingAsylum",ns::hiking_experience::advanced,"Marilyn C",0.9} });

    SECTION("1")
    {
        std::string s;
        encode_json(val, s);
        auto val2 = decode_json<ns::hiking_reputation>(s);
        CHECK(val2 == val);
    }

    SECTION("2")
    {
        std::string s;
        encode_json(val, s, indenting::indent);
        auto val2 = decode_json<ns::hiking_reputation>(s);
        CHECK(val2 == val);
    }

    SECTION("3")
    {
        std::string s;
        json_options options;
        encode_json(val, s, options, indenting::indent);
        auto val2 = decode_json<ns::hiking_reputation>(s, options);
        CHECK(val2 == val);
    }

    SECTION("4")
    {
        std::string s;
        encode_json(val, s, json_options(), indenting::no_indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(s, json_options(), ojson());
        CHECK(val2 == val);
    }

    SECTION("5")
    {
        std::string s;
        encode_json(val, s, json_options(), indenting::indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(s, json_options(), ojson());
        CHECK(val2 == val);
    }

    SECTION("6")
    {
        std::string s;
        json_options options;
        encode_json(val, s, options, indenting::indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(s, options, ojson());
        CHECK(val2 == val);
    }

    SECTION("os 1")
    {
        std::stringstream os;
        encode_json(val, os);
        auto val2 = decode_json<ns::hiking_reputation>(os);
        CHECK(val2 == val);
    }

    SECTION("os 2")
    {
        std::stringstream os;
        encode_json(val, os, indenting::indent);
        auto val2 = decode_json<ns::hiking_reputation>(os);
        CHECK(val2 == val);
    }

    SECTION("os 3")
    {
        std::stringstream os;
        json_options options;
        encode_json(val, os, options, indenting::indent);
        auto val2 = decode_json<ns::hiking_reputation>(os, options);
        CHECK(val2 == val);
    }

    SECTION("os 4")
    {
        std::stringstream os;
        encode_json(val, os, json_options(), indenting::no_indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(os, json_options(), ojson());
        CHECK(val2 == val);
    }

    SECTION("os 5")
    {
        std::stringstream os;
        encode_json(val, os, json_options(), indenting::indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(os, json_options(), ojson());
        CHECK(val2 == val);
    }

    SECTION("os 6")
    {
        std::stringstream os;
        json_options options;
        encode_json(val, os, options, indenting::indent, ojson());
        auto val2 = decode_json<ns::hiking_reputation>(os, options, ojson());
        CHECK(val2 == val);
    }
}

