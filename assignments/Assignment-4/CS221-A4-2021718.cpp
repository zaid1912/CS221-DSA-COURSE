#include <iostream>
#include <fstream>
#include <list>
#include "trie.h"
using namespace std;
//globally creating a new file so that it is accessible from anywhere within this program
ofstream output_file("output.txt");
/**
 * @brief reads the file "words.txt" that contains 9340 English language words and each of these words is inserted to the tries data structure
 * 
 * @param t object of tries class
 */
void insert_words_to_trie(tries t)
{
    fstream my_file;
    my_file.open("words.txt", ios::in);
    string word;
    while (1)
    {
        my_file >> word;
        if (my_file.eof())
        {
            break;
        }
        t.insertword(word);
    }
}
/**
 * @brief each horizontal line(row) of 2D matrix is traversed(LEFT TO RIGHT) and all the words found along with their starting and ending indexs are added to the output file
 * 
 * @param t object of tries class in which the word is to be searched
 * @param matrix the 2D array - matrix of characters
 * @param r number of rows in the matrix
 * @param c number of columns in the matrix
 */
void search_horizontally(tries t, char **matrix, int r, int c)
{
    output_file << "---horizontally---\n";
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            string word = "";
            for (int k = j; k < c; k++)
            {
                word = word + matrix[i][k];
                if (t.searchword(word))
                {
                    int row = i + 1;
                    int start_col = k - word.length() + 2;
                    int end_col = k + 1;
                    output_file << word << " (" << row << ", " << start_col << ")(" << row << ", " << end_col << ")" << endl;
                }
            }
        }
    }
}
/**
 * @brief each vertical line(column) of 2D matrix is traversed(TOP TO BOTTOM) and all the words found along with their starting and ending indexs are added to the output file
 * 
 * @param t object of tries class in which the word is to be searched
 * @param matrix the 2D array - matrix of characters
 * @param r number of rows in the matrix
 * @param c number of columns in the matrix
 */

void search_vertically(tries t, char **matrix, int r, int c)
{
    output_file << "---vertically---\n";
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r; j++)
        {
            string word = "";
            for (int k = j; k < r; k++)
            {
                word = word + matrix[k][i];
                if (t.searchword(word))
                {
                    int col = i + 1;
                    int start_row = k - word.length() + 2;
                    int end_row = k + 1;
                    output_file << word << " (" << start_row << ", " << col << ")(" << end_row << ", " << col << ")" << endl;
                }
            }
        }
    }
}
/**
 * @brief each horizontal line(row) of 2D matrix is traversed(RIGHT TO LEFT) IN REVERSE ORDER and all the words found along with their starting and ending indexs are added to the output file
 * 
 * @param t object of tries class in which the word is to be searched
 * @param matrix the 2D array - matrix of characters
 * @param r number of rows in the matrix
 * @param c number of columns in the matrix
 */
void horizontally_reverse(tries t, char **matrix, int r, int c)
{
    output_file << "---horizontally backwards---\n";
    for (int i = 0; i < r; i++)
    {
        for (int j = c - 1; j >= 0; j--)
        {
            string word = "";
            for (int k = j; k >= 0; k--)
            {
                word = word + matrix[i][k];
                if (t.searchword(word))
                {
                    int row = i + 1;
                    int start_col = k + word.length();
                    int end_col = k + 1;
                    output_file << word << " (" << row << ", " << start_col << ")(" << row << ", " << end_col << ")" << endl;
                }
            }
        }
    }
}
/**
 * @brief each vertical line(column) of 2D matrix is traversed in reverse order(BOTTOM TO TOP) and all the words found along with their starting and ending indexs are added to the output file
 * 
 * @param t object of tries class in which the word is to be searched
 * @param matrix the 2D array - matrix of characters
 * @param r number of rows in the matrix
 * @param c number of columns in the matrix
 */
void vertically_backwards(tries t, char **matrix, int r, int c)
{
    output_file << "---vertically backwards---\n";
    for (int i = 0; i < c; i++)
    {
        for (int j = r - 1; j >= 0; j--)
        {
            string word = "";
            for (int k = j; k >= 0; k--)
            {
                word = word + matrix[k][i];
                if (t.searchword(word))
                {
                    int col = i + 1;
                    int start_row = k + word.length();
                    int end_row = k + 1;
                    output_file << word << " (" << start_row << ", " << col << ")(" << end_row << ", " << col << ")" << endl;
                }
            }
        }
    }
}
/**
 * @brief searched the words in list whether they are strored in the tries or not
 * 
 * @param t object of tries class and list that conatains the set of diagonally occuring characters
 */
void diagonal(tries t,list<char>l){
    string word = "";
    for(auto i:l){
        word = word+i;
    }
    if(t.searchword(word)){
        output_file<<word<<endl;
    }
}
/**
 * @brief traverses virtically through the 2D matrix of characters and stores the sets of characters occuring to a list and passes that list as a parameter to another "diagonal" function that searches for the occuring words in the tries
 * 
 * @param t object of tries class in which the word is to be searched
 * @param matrix the 2D array - matrix of characters
 * @param r number of rows in the matrix
 * @param c number of columns in the matrix
 */
void diagonally(tries t, char **matrix, int r, int c)
{
    output_file << "---diagonally---\n";
    int max_sum = r + c - 2;
    for (int sum = 0; sum <= max_sum; sum++)
    {
        list<char> diagonal_list;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (i + j - sum == 0)
                {
                    diagonal_list.push_back(matrix[i][j]);
                    diagonal(t, diagonal_list);
                }
            }
        }
    }
}

int main()
{
    /**
     * @brief PLEASE NOTE THAT, FOR TESTING PURPOSES, I SET THE MATRIX SIZE AS 4x7 BUT THIS CAN BE CHANGED IF I TAKE THE INPUT FROM THE USER BUT THAT WOULD BE VERY TIME CONSUMMING FOR THE USER TO ENTER LET'S SAY 4*7 = 28 CHARACTERS. THEREFORE, I SET IT AS 4x7 AND HAVE PROVIDED YOU WITH THE INPUT CHARACTERS. JUST COPY THE LINE BELOW (TESTING DATA) AND PASTE IT IN THE TERMINAL WHEN THE PROGRAM PROMPTS THE USER TO ENTER THE CHARACTERS TO BE STORED IN 2D MATRIX.
     * 
     */
    // test data(COPY THIS TO TERMINAL WHEN PROMPT)
    // dogxillpooltacweodeddofdrgod
    tries t;
    insert_words_to_trie(t);
    int rows = 4;
    int columns = 7;
    char **matrix = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new char[columns];
    }

    cout << "Enter the characters to be stored in matrix: ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cin >> matrix[i][j];
        }
    }
    cout << "\nprinting the stored characters(2D array of stored characters)\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    search_horizontally(t, matrix, rows, columns);
    search_vertically(t, matrix, rows, columns);
    horizontally_reverse(t, matrix, rows, columns);
    vertically_backwards(t, matrix, rows, columns);
    diagonally(t, matrix, rows, columns);
    cout<<"\nSEE THE FILE NAMED 'output.txt' TO CHECK THE EXTRACTED WORDS FROM THIS 2D MATRIX OF CHARACTERS\n\n";
}