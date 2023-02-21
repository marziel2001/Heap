#include <iostream>
#include <string>

using namespace std;

enum HeapMode 
{
    MAX,
    MIN
};

bool StrGt(string l, string r)
{
    if (l.length() > r.length())
    {
        return true;
    }
    else if (l.length() < r.length())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < l.length(); i++)
        {
            if (l[i] != r[i])
            {
                if (l[i] > r[i])
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }
}

void Swap(string arr[], int i1, int i2)
{
    string tmp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
}
void MaxHeapify(string Array[], int ArraySize, int parentIndex)
{
    int maxIndex = parentIndex;
    int leftChild = parentIndex * 2 + 1;
    int rightChild = parentIndex * 2 + 2;

    if (leftChild < ArraySize && StrGt(Array[leftChild], Array[maxIndex]))
    {
        maxIndex = leftChild;
    }

    if (rightChild < ArraySize && StrGt(Array[rightChild], Array[maxIndex]) && (Array[leftChild] != Array[rightChild]))
    {
        maxIndex = rightChild;
    }

    if (maxIndex != parentIndex)
    {
        Swap(Array, maxIndex, parentIndex);
        MaxHeapify(Array, ArraySize, maxIndex);
        //zbudowany maksymalny kopiec
    }
}
void MinHeapify(string Array[], int ArraySize, int parentIndex)
{
    int minIndex = parentIndex;
    int leftChild = parentIndex * 2 + 1;
    int rightChild = parentIndex * 2 + 2;

    if (leftChild < ArraySize && StrGt(Array[minIndex], Array[leftChild]))
    {
        minIndex = leftChild;
    }

    if (rightChild < ArraySize && StrGt(Array[minIndex], Array[rightChild]) && (Array[leftChild] != Array[rightChild]))
    {
        minIndex = rightChild;
    }

    if (minIndex != parentIndex)
    {
        Swap(Array, minIndex, parentIndex);
        MinHeapify(Array, ArraySize, minIndex);
        //zbudowany minimalny kopiec
    }
}
void MaxHeap(string Array[], int ArraySize)
{
    // ostatni rodzic = n / 2 - 1 : od tego miejsca zaczynamy iterowanie po kopcu
    for (int i = ArraySize / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(Array, ArraySize, i);
    } // utworzylismy max kopiec
}
void MinHeap(string Array[], int ArraySize)
{
    // ostatni rodzic = n / 2 - 1 : od tego miejsca zaczynamy iterowanie po kopcu
    for (int i = ArraySize / 2 - 1; i >= 0; i--)
    {
        MinHeapify(Array, ArraySize, i);
    } // utworzylismy min kopiec
}
void PrintArray(const string* Array, const int ArraySize)
{
    for (int i = 0; i < ArraySize; i++)
    {
        cout << Array[i] << " ";
    }
}
void ExpandArray(string** array, int* size)
{
    (*size)++;
    string* newArray = new string[*size];

    for (int i = 0; i < *size - 1; i++)
    {
        newArray[i] = *(*array + i);
    } 
    newArray[*size - 1] = "0";

    delete[] * array;
    *array = newArray;
}
void DelFirst(string** array, int* size)
{
    (*size)--;
    if (*size > 0) 
    {
        string* newArray = new string[*size];
        for (int i = 0; i < *size; i++)
        {
            newArray[i] = *(*array + i);
        }
        newArray[0] = *(*array + *size);
        delete[] * array;
        *array = newArray;
    }
    else {
        *(*array) = "0";
    }
}
void CreateHeap(string heap[], int heapSize, HeapMode mode)
{
    if (heapSize > 0) 
    {
        if (mode == MAX)
        {
            MaxHeap(heap, heapSize);
        }
        else 
        {
            MinHeap(heap, heapSize);
        }
    }
}

int main()
{
    char COMMAND = 0;
    HeapMode mode = MAX;
    int ArraySize = 0;
    string* Array = nullptr;

    while (COMMAND != 'q')
    {
        cin >> COMMAND;
        if (COMMAND == '+')
        {
            string v;
            cin >> v;
            ExpandArray(&Array, &ArraySize);
            Array[ArraySize - 1] = v;
            CreateHeap(Array, ArraySize, mode);
        }
        else if (COMMAND == '-')
        {
            cout << Array[0] << "\n";
            DelFirst(&Array, &ArraySize);
            CreateHeap(Array, ArraySize, mode);
        }
        else if (COMMAND == 'p')
        {
            PrintArray(Array, ArraySize);
            cout << "\n";
        }
        else if (COMMAND == 'r')
        {
            ArraySize = 0;

            int n;
            cin >> n;
            while (n > 0) 
            {
                string x;
                cin >> x;
                ExpandArray(&Array, &ArraySize);
                Array[ArraySize - 1] = x;
                n--;
            }
            CreateHeap(Array, ArraySize, mode);
        }
        else if (COMMAND == 's')
        {
            if (mode == MAX)
            {
                mode = MIN;
            }
            else if (mode == MIN)
            {
                mode = MAX;
            }
            CreateHeap(Array, ArraySize, mode);
        }
    }
    return 0;
}
