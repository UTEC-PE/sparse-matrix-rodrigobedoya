#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        void test()
        {
            
        }

        T testCon(int x, int y)
        {
            if(x > rows || y > columns)
            {
                throw out_of_range("out of range");
            }

            Node<T>* tempCol = hColumns;
            
            //getting index
            while(tempCol->data != y)
            {
                tempCol = tempCol->next;
            }

            Node<T>* current = tempCol;
            while(current->down != NULL)
            {
                current = current->down;
                if(current->x == x)
                {
                    return current->data;
                }
                else if(current->x > x)
                    throw "Couldn't find value";
            }
            cout << endl << "ERRORtest: ";
            return (T)-1;
        }

        Matrix():hRows(NULL),hColumns(NULL),columns(0),rows(0){}

        Matrix(int sizeX, int sizeY):
            rows(sizeX),columns(sizeY)
        {
            Node<T>* row = new Node<T>(sizeX-1);
            for(int i = 0; i < sizeX-1;i++)
            {
                Node<T>* temp = row;
                row = new Node<T>(sizeX-2-i,NULL,temp);
            }
            hRows = row;

            Node<T>* column = new Node<T>(sizeY-1);
            for(int i = 0; i < sizeY-1;i++)
            {
                Node<T>* temp = column;
                column = new Node<T>(sizeY-2-i,temp);
            }
            hColumns = column;

            
        }

        void set(int x, int y, T data)
        {
            if(x > rows || y > columns)
            {
                throw out_of_range("out of range");
            }

            Node<T>* tempRow = hRows;
            Node<T>* tempCol = hColumns;
                

            //getting indexes
            while(tempRow->data != x)
            {
                tempRow = tempRow->down;
            }
            while(tempCol->data != y)
            {
                tempCol = tempCol->next;
            }


            Node<T>* currentY = tempCol, *prevY;
            
            if(tempRow->next == NULL)
            {

                if(tempCol->down == NULL)
                {
                    Node<T>* temp = new Node<T>(x,y,data);
                    tempRow->next = temp;
                    tempCol->down = temp;
                    return;
                }

                while(currentY->down != NULL)
                {
                    prevY = currentY;
                    currentY = currentY->down;

                    if(currentY->x > x)
                    {
                        Node<T>* new_node = new Node<T>(x,y,data,NULL,currentY);
                        prevY->down = new_node;
                        tempRow->next = new_node;
                        return;
                    }
                }
            
                Node<T>* new_node = new Node<T>(x,y,data,NULL,NULL);
                currentY->down = new_node;
                tempRow->next = new_node;
                return;
            }


            Node<T>* current = tempRow;
            Node<T>* prev;

            while(current->next != NULL)
            {
                prev = current;
                current = current->next;
                if(current->y == y)
                {
                    current->data = data;
                    return;
                }
                if(current->y > y)
                {

                    Node<T>* new_node = new Node<T>(x,y,data,current,NULL);
                    prev->next = new_node;

                    if(tempCol->down == NULL)
                    {
                        tempCol->down = new_node;
                        return;
                    }
                    
                    while(currentY->down != NULL)
                    {
                        prevY = currentY;
                        currentY = currentY->down;

                        if(currentY->x > x)
                        {
                            prevY->down = new_node;
                            new_node->down = currentY;
                            return;
                        }
                    }
                    
                    currentY->down = new_node;
                    return;

                }
            }
            
            Node<T>* new_node = new Node<T>(x,y,data,NULL,NULL);
            current->next = new_node;
            if(tempCol->down == NULL)
            {
                tempCol->down = new_node;
                return;
            }
            while(currentY->down != NULL)
            {
                prevY = currentY;
                currentY = currentY->down;

                if(currentY->x > x)
                {
                    prevY->down = new_node;
                    new_node->down = currentY;
                    return;
                }
            }
            currentY->down = new_node;
            return;
        }

        T operator()(int x, int y)
        {
            cout << testCon(x,y) << ",";
            if(x > rows || y > columns)
            {
                throw out_of_range("out of range");
            }

            Node<T>* tempRow = hRows;
            
            //getting index
            while(tempRow->data != x)
            {
                tempRow = tempRow->down;
            }

            Node<T>* current = tempRow;
            while(current->next != NULL)
            {
                current = current->next;
                if(current->y == y)
                {
                    return current->data;
                }
                else if(current->y > y)
                    throw "Couldn't find value";
            }
            cout << endl << "ERROR: ";
            return (T)-1;
        }



        Matrix<T> operator*(Matrix<T> other)
        {
            if(rows != other.rows || columns != other.columns)
            {
                throw out_of_range("matrixes of different size");
            }
            /*
            Matrix result(rows,columns);
            Node<T>* tempRow = hRows, *current;
            for(int i = 0; i < rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    result.set(current->x,current->y,current->data);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return result;*/
        }


        Matrix<T> operator*(T scalar)
        {
            Matrix result(rows,columns);
            Node<T>* tempRow = hRows, *current;
            for(int i = 0; i < rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    result.set(current->x,current->y,current->data * scalar);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return result;
        }

        Matrix<T> operator+(Matrix<T> other);
        Matrix<T> operator-(Matrix<T> other);

        Matrix<T> transposed()
        {
            Matrix result(columns,rows);
            Node<T>* tempRow = hRows, *current;
            for(int i = 0; i < rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    result.set(current->y,current->x,current->data);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return result;
        }

        Matrix<T> operator=(Matrix<T> other)
        {   
            if(rows != other.rows || columns != other.columns)
            {
                throw out_of_range("matrixes of different size");
            }

            Node<T>* tempRow = hRows, *current, *temp;
            for(int i = 0; i < rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    temp = current;
                    current = current->next;
                    delete temp;
                }
                tempRow = tempRow->down;
            }
            
            tempRow = other.hRows;
            for(int i = 0; i < other.rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    this->set(current->x,current->y,current->data);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return *this;
        }



        ~Matrix()
        {

        }
};

#endif