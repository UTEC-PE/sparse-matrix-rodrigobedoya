#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

        T multiply(vector<T> v1, vector<T> v2)
        {
            T result = 0;
            for(int i = 0; i < v1.size();i++)
            {
                result += v1[i] * v2[i];
            }
            return result;
        }


    public:
        
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
                if(data == 0)
                {
                    return;
                }

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
                    if(data == 0)
                    {
                        while(currentY->down != NULL)
                        {
                            prevY = currentY;
                            currentY = currentY->down;

                            if(currentY->x == x)
                            {
                                break;
                            }
                        }
                        prevY->down = currentY->down;
                        prev->next = current->next;  
                        delete current;
                        return;                  

                    }
                    current->data = data;
                    return;
                }
                if(current->y > y)
                {
                    if(data == 0)
                    {
                        return;
                    }

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
            

            if(data == 0)
            {
                return;
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


        void remove(int x, int y)
        {
            set(x,y,0);
        }


        T operator()(int x, int y)
        {
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
                    return 0;
            }
            return 0;
        }



        Matrix<T> operator*(Matrix<T> other)
        {
            if(columns != other.rows)
            {
                throw out_of_range("different rows and columns");
            }
            
            Matrix result(rows,other.columns);
            Node<T>* tempRow = result.hRows, *current;
            
            Node<T>* tempRowM = hRows;
            for(int i = 0; i < rows;i++)
            {
                Node<T>* tempColM = other.hColumns;
                for(int j = 0; j < other.columns;j++)
                {                    
                    vector<T> v1(columns,0);
                    vector<T> v2(columns,0);

                    Node<T> *current1 = tempRowM->next;
                    while(current1 != NULL)
                    {
                        
                        v1[current1->y] = current1->data;
                        current1 = current1->next;
                    }

                    Node<T> *current2 = tempColM->down;
                    while(current2 != NULL)
                    {
                        v2[current2->x] = current2->data;
                        current2 = current2->down;
                    }                    

                    result.set(i,j,multiply(v1,v2));
                    v1.clear();v2.clear();
                    tempColM = tempColM->next;                    
                }
                tempRowM = tempRowM->down;
            }
            return result;
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

        Matrix<T> operator+(Matrix<T> other)
        {
            if(rows != other.rows || columns != other.columns)
            {
                throw out_of_range("matrixes of different size");
            }

            Matrix result(rows,columns);
            result = other;
            

            Node<T>* tempRow = hRows, *current;
            for(int i = 0; i < rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    result.set(current->x,current->y,current->data + result(current->x,current->y));
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return result;
        }

        Matrix<T> operator-(Matrix<T> other)
        {
            if(rows != other.rows || columns != other.columns)
            {
                throw out_of_range("matrixes of different size");
            }

            Matrix result(rows,columns);
            result = *this;
            

            Node<T>* tempRow = other.hRows, *current;
            for(int i = 0; i < other.rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    result.set(current->x,current->y,result(current->x,current->y) - current->data);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return result;
        }

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
            
            //delete old matrix data
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
            
            //if matrixes of different size
            if(rows != other.rows || columns != other.columns)
            {
                //delete old indexes
                Node<T> *current = hRows, *temp;
                while (current != NULL)
                {
                    temp = current;
                    current = current->down;
                    delete temp;
                }

                current = hColumns;
                while (current != NULL)
                {
                    temp = current;
                    current = current->next;
                    delete temp;
                }

                //Create new indexes
                rows = other.rows;
                columns = other.columns;

                Node<T>* row = new Node<T>(rows-1);
                for(int i = 0; i < rows-1;i++)
                {
                    Node<T>* temp = row;
                    row = new Node<T>(rows-2-i,NULL,temp);
                }
                hRows = row;

                Node<T>* column = new Node<T>(columns-1);
                for(int i = 0; i < columns-1;i++)
                {
                    Node<T>* temp = column;
                    column = new Node<T>(columns-2-i,temp);
                }
                hColumns = column;

            }

            //copy matrix data
            tempRow = other.hRows;
            for(int i = 0; i < other.rows;i++)
            {
                current = tempRow->next;
                while(current != NULL)
                {
                    set(current->x,current->y,current->data);
                    current = current->next;
                }
                tempRow = tempRow->down;
            }
            return *this;
        }

        ~Matrix()
        {  

            /*
            //delete old matrix data
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

            //delete old indexes
            current = hRows;
            while (current != NULL)
            {
                temp = current;
                current = current->down;
                delete temp;
            }

            current = hColumns;
            while (current != NULL)
            {
                temp = current;
                current = current->next;
                delete temp;
            }
            */
        }
};

#endif