#include <iostream>
#include <limits>

#include <cstdio>
#include <cassert>

int main(int argc, char* argv[])
{
    // See: http://www.cplusplus.com/reference/std/limits/numeric_limits/

    {
        // from:
        //     http://msdn.microsoft.com/en-us/library/6hthw3cb%28v=vs.80%29.aspx
        // slightly modified
        std::cout << std::numeric_limits<float>::has_infinity << std::endl;
        std::cout << std::numeric_limits<double>::has_infinity << std::endl;
        std::cout << std::numeric_limits<long double>::has_infinity << std::endl;
        std::cout << std::numeric_limits<int>::has_infinity << std::endl;
        std::cout << std::numeric_limits<long long int>::has_infinity << std::endl;
     
        std::cout << "The representation of infinity for type float is: "
                  << std::numeric_limits<float>::infinity( ) << std::endl;
        std::cout << "The representation of infinity for type double is: "
                  << std::numeric_limits<double>::infinity( ) << std::endl;
        std::cout << "The representation of infinity for type long double is: "
                  << std::numeric_limits<long double>::infinity( ) << std::endl;
    }

    {
        std::cout << std::string(80, '-');

        const float INFTY   = std::numeric_limits<float>::infinity();
        const float epsilon = std::numeric_limits<float>::epsilon();
        const float max     = std::numeric_limits<float>::max();
        const float min     = std::numeric_limits<float>::min();
 
        std::cout << "\n∞:\n";
        std::cout << "std::cout  " << INFTY << "\n";
        printf("printf     %f\n", INFTY);
 
        std::cout << "\n-∞:\n";
        std::cout << "std::cout  " << -INFTY << "\n";
        printf("printf     %f\n", -INFTY);
 
        std::cout << "\n𝜖:\n";
        std::cout << "std::cout  " << epsilon << "\n";
        printf("printf     %f\n", epsilon);
 
        std::cout << "\n-𝜖:\n";
        std::cout << "std::cout  " << -epsilon << "\n";
        printf("printf     %f\n", -epsilon);
 
        std::cout << "\nmax:\n";
        std::cout << "std::cout  " << max << "\n";
        printf("printf     %f\n", max);
 
        std::cout << "\nmin:\n";
        std::cout << "std::cout  " << min << "\n";
        printf("printf     %f\n", min );
 
        assert(max < INFTY);
        assert(min > -INFTY);
    }

    {
        std::cout << std::string(80, '-');

        const double INFTY   = std::numeric_limits<double>::infinity();
        const double epsilon = std::numeric_limits<double>::epsilon();
        const double max     = std::numeric_limits<double>::max();
        const double min     = std::numeric_limits<double>::min();
 
        std::cout << "\n∞:\n";
        std::cout << "std::cout  " << INFTY << "\n";
        printf("printf     %f\n", INFTY);
 
        std::cout << "\n-∞:\n";
        std::cout << "std::cout  " << -INFTY << "\n";
        printf("printf     %f\n", -INFTY);
 
        std::cout << "\n𝜖:\n";
        std::cout << "std::cout  " << epsilon << "\n";
        printf("printf     %f\n", epsilon);
 
        std::cout << "\n-𝜖:\n";
        std::cout << "std::cout  " << -epsilon << "\n";
        printf("printf     %f\n", -epsilon);
 
        std::cout << "\nmax:\n";
        std::cout << "std::cout  " << max << "\n";
        printf("printf     %f\n", max);
 
        std::cout << "\nmin:\n";
        std::cout << "std::cout  " << min << "\n";
        printf("printf     %f\n", min );
 
        assert(max < INFTY);
        assert(min > -INFTY);
    }

    {
        std::cout << std::string(80, '-');

        const long double INFTY   = std::numeric_limits<long double>::infinity();
        const long double epsilon = std::numeric_limits<long double>::epsilon();
        const long double max     = std::numeric_limits<long double>::max();
        const long double min     = std::numeric_limits<long double>::min();
 
        std::cout << "\n∞:\n";
        std::cout << "std::cout  " << INFTY << "\n";
        printf("printf     %Lf\n", INFTY);
 
        std::cout << "\n-∞:\n";
        std::cout << "std::cout  " << -INFTY << "\n";
        printf("printf     %Lf\n", -INFTY);
 
        std::cout << "\n𝜖:\n";
        std::cout << "std::cout  " << epsilon << "\n";
        printf("printf     %Lf\n", epsilon);
 
        std::cout << "\n-𝜖:\n";
        std::cout << "std::cout  " << -epsilon << "\n";
        printf("printf     %Lf\n", -epsilon);
 
        std::cout << "\nmax:\n";
        std::cout << "std::cout  " << max << "\n";
        printf("printf     %Lf\n", max);
 
        std::cout << "\nmin:\n";
        std::cout << "std::cout  " << min << "\n";
        printf("printf     %Lf\n", min );
 
        assert(max < INFTY);
        assert(min > -INFTY);
    }

    return 0;
}

