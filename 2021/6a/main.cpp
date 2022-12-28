#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>

#include <QCoreApplication>
#include <QPoint>
#include <QLine>

using namespace std;
template <class T>
class csv_istream_iterator: public iterator<input_iterator_tag, T>
{
    istream * _input;
    char _delim;
    string _value;
public:
    csv_istream_iterator( char delim = ',' ): _input( 0 ), _delim( delim ) {}
    csv_istream_iterator( istream & in, char delim = ',' ): _input( &in ), _delim( delim ) { ++*this; }

    const T operator *() const {
        istringstream ss( _value );
        T value;
        ss >> value;
        return value;
    }

    istream & operator ++() {
        if( !( getline( *_input, _value, _delim ) ) )
        {
            _input = 0;
        }
        return *_input;
    }

    bool operator !=( const csv_istream_iterator & rhs ) const {
        return _input != rhs._input;
    }
};

template <>
const string csv_istream_iterator<string>::operator *() const {
    return _value;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<int8_t> input;
    vector<int> row;
    vector<string> oxygen;
    vector<string> scrubber;
    string str;
    int days = 18;
    uint64_t result = 0;

    ifstream infile("data2");
    copy( csv_istream_iterator<int>( infile ),
          csv_istream_iterator<int>(),
          insert_iterator< vector<int8_t> >( input, input.begin() ) );
    vector<int8_t> output = input;

    for (int i = 0; i <= days; ++i)
    {
        int newFish = 0;
        cout << "day: " << i << "\t " << input.size() << "\t";
        for (int8_t& fish : input)
        {
            cout << (int)fish << ",";
        }
        cout << ":   " << input.size() << endl;
        for (auto fish = input.begin(); fish != input.end(); ++fish)
        {
            *fish = *fish - 1;
            if (*fish == -1)
            {
                *fish = 6;
                newFish++;
            }
        }
        while (newFish != 0)
        {
            input.push_back(8);
            newFish--;
        }
    }


    return a.exec();
}
