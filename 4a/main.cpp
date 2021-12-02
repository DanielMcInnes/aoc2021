#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#include <QCoreApplication>
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

class BingoBoard : public vector< vector<int> >
{
public:
    int boardNumber;
    vector<int> calledNumbers;
    int callNumber(const int number)
    {
        calledNumbers.push_back(number);
        if (victory())
        {
            cout << "VICTORY!!!" << endl;
            return 1;
        }
        cout << "BingoBoard: callNumber: calledNumbers.size(): " << calledNumbers.size() << endl;
        return -1;
    }
    bool victory()
    {
        int matching = 0;
        for (auto& row : *this)
        {
            matching = 0;
            for (auto number : calledNumbers)
            {
                if (find(row.begin(), row.end(), number) != row.end())
                {
                    matching++;
                    cout << "   victory(): found a match:" << number << " matching: " << matching << " boardNumber: " << boardNumber << " calledNumbers.size(): " << calledNumbers.size() << endl;
                }
            }

            if (matching == 5)
            {
                return true;
            }
        }

        for (int i = 0; i < 5; ++i)
        {
            matching = 0;
            vector<int> _column = column(i);
            for (auto number : calledNumbers)
            {
                if (find(_column.begin(), _column.end(), number) != _column.end())
                {
                    matching++;
                }
                if (matching == 5)
                {
                    return true;
                }
            }
        }
        return false;
    }

    vector<int> column(int index)
    {
        vector<int> _column;

        for (auto row : *this)
        {
            _column.push_back(row[index]);
        }
        return _column;
    }

    int score()
    {
        int retval = 0;

        for (auto& row : *this)
        {
            for (auto i : row)
            {
                if (find(calledNumbers.begin(), calledNumbers.end(), i) == calledNumbers.end())
                    retval += i;
            }
        }
        return retval;
    }

};
class BingoBoards : public vector< BingoBoard >
{
public:
    int callNumber(const int number)
    {
        int i = 0;
        for (auto& board: *this)
        {
            if (board.callNumber(number) == 1)
            {
                auto& winner = this->at(i);
                cout << "Board #" << board.boardNumber << " wins! score: " << winner.score() << " score: " << winner.score() * number << endl;


                return board.boardNumber;
            }
            i++;
        }
        return -1;
    }

};

int main(int argc, char *argv[])
{
    BingoBoard board;
    BingoBoards boards;

    QCoreApplication a(argc, argv);
    vector<int> input;
    vector<int> row;
    vector<string> oxygen;
    vector<string> scrubber;
    string str;
    int boardIndex = 0;

    {
        ifstream infile("data");
        copy( csv_istream_iterator<int>( infile ),
              csv_istream_iterator<int>(),
              insert_iterator< vector<int> >( input, input.begin() ) );

        for (auto it : input)
            cout << "it: " << it << endl;
    }

    ifstream infile("data");
    infile >> str;
    while (infile >> str )
    {
        cout << "checking... " << str <<  endl;
        if (str != "")
        {
            row.push_back(stoi(str));
            cout << "str: " << str << " stoi(str): " << stoi(str) << " row.size(): " << row.size() << endl;
            if (row.size() == 5)
            {
                board.push_back(row);
                row.clear();
                if (board.size() == 5)
                {
                    board.boardNumber = boardIndex++;
                    boards.push_back(board);
                    board.clear();
                }
            }
        }
    }
    cout << "boards.count(): " << boards.size() << endl;
    for (auto it : input)
    {
        cout << "calling: " << it << endl;
        if (boards.callNumber(it) != -1)
            return 0;
    }

    return a.exec();
}
