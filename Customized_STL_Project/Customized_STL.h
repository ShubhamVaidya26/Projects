#include<iostream>
using namespace std;
#pragma pack(1)
#include<cstddef>


///////////////////////////////////////////////////////////////////
//                                                               //
//   structure for singly linear, singly circular,Stack & Queue  //
//                                                               //
///////////////////////////////////////////////////////////////////

template<class T>
struct SNode
{
  T Data;
  struct SNode * Next;
};

/////////////////////////////////////////////////////////////////////////////
/*
    Singly Linear linked List
    
    Containts :  InsertFirst Function
                 InsertLast  Function
                 InsertAtPos Function
               
                 DeleteFirst Function
                 DeleteLast  Function
                 DeleteAtPos Function
               
                 Display Function
                 Count   Function
                 Help    Function
                 
                 SearchFirstOcc    Function
                 SearchLastOcc     Function
                 AdditionOfNumbers Function
                 Maximum           Function
                 Minimum           Function
                 SecondMaximum     Function
                 SecondMinimum     Function
                 DisplayPerfect    Function
                 DisplayPrime      Function
*/
////////////////////////////////////////////////////////////////////////////

template<class T>
class SinglyLL
{
  public:
     struct SNode <T> * First;                
     int iCount;                 
     
     SinglyLL();                 
     
     void InsertFirst(T iNo);
     void InsertLast(T iNo);
     void InsertAtPos(T iNo,int iPos);
     
     void DeleteFirst();
     void DeleteLast();
     void DeleteAtPos(int iPos);
     
     void Display();
     void Help();
     
     int SearchFirstOcc(T iNo);
     int SearchLastOcc(T iNo);
     T AdditionOfNumbers();
     T Maximum();
     T Minimum();
     T SecondMaximum();
     T SecondMinimum();
     void DisplayPerfect();
     void DisplayPrime();
};


template<class T>
SinglyLL <T> :: SinglyLL()  
{
   First = NULL;
   iCount = 0;
}

template<class T>
void SinglyLL <T> :: InsertFirst(T iNo)
{
   struct SNode <T> * Newn = new (struct SNode <T>);
   
   Newn->Data = iNo;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
      First = Newn;
      iCount++;
   }
   else 
   {
      Newn->Next = First;
      First = Newn;
      iCount++;
   }
}

template<class T>
void SinglyLL <T> :: InsertLast(T iNo)
{
   struct SNode <T> * Newn = new (struct SNode <T>) ;
   
   Newn->Data = iNo;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
      First = Newn;
      iCount++;
   }
   else 
   {
     struct SNode <T> * Temp = First;
     
     while(Temp->Next != NULL)
     {
       Temp = Temp->Next;
     }
     Temp->Next = Newn;
     iCount++;
   }
}

template<class T>
void SinglyLL <T> :: DeleteFirst()
{
  if(First == NULL)
  {
     return ;
  }
  else if(First->Next == NULL)
  {
     delete First;
     First = NULL;
     iCount--;
  }
  else
  {
     struct SNode <T> * Temp = First;
     First = First->Next;
     delete Temp;
     iCount--;
  }
}

template<class T>
void SinglyLL <T> :: DeleteLast()
{
  if(First == NULL)
  {
     return ;
  }
  else if(First->Next == NULL)
  {
     delete First;
     First = NULL;
     iCount--;
  }
  else
  {
    struct SNode <T> * Temp = First;
    
    while(Temp->Next->Next != NULL)
    {
       Temp = Temp->Next;
    }
    
    delete Temp->Next;
    Temp->Next = NULL;
  }
}

template<class T>
void SinglyLL <T> :: Display()
{
   struct SNode <T> * Temp = First;
   cout<<"Elements in Singly Linear LinkedList are : \n";
   
   while(Temp != NULL)
   {
     cout<<"| "<<Temp->Data<<" |->";
     Temp = Temp->Next;
   }
   cout<<"NULL\n";
}

template<class T>
void SinglyLL <T> :: InsertAtPos(T iNo ,int iPos)
{
    if((iPos < 1) || (iPos > iCount+1))
    {
        cout<<"Invalid position"<<"\n";
        return;
    }

    if(iPos == 1)
    {
        InsertFirst(iNo);
    }
    else if(iPos == iCount + 1)
    {
        InsertLast(iNo);
    }
    else
    {
        struct SNode <T> * Newn = new (struct SNode <T>);

        Newn->Data = iNo;
        Newn->Next = NULL;

        struct SNode <T> * Temp = First;
        
        for(int iCnt = 1; iCnt < iPos-1; iCnt++)
        {
            Temp = Temp->Next;
        }

        Newn->Next = Temp->Next;
        Temp->Next = Newn;

        iCount++;
    }   
}

template<class T>
void SinglyLL <T> :: DeleteAtPos(int iPos)
{
  if((iPos < 1) || (iPos > iCount))
    {
        cout<<"Invalid position"<<"\n";
        return;
    }

    if(iPos == 1)
    {
        DeleteFirst();
    }
    else if(iPos == iCount)
    {
        DeleteLast();
    }
    else
    {
       struct SNode <T> * Temp1 = First;
       struct SNode <T> * Temp2 = First;
       
        for(int iCnt = 1; iCnt < iPos-1; iCnt++)
        {
            Temp1 = Temp1->Next;
        }
        Temp2 = Temp1->Next;
        
        Temp1->Next = Temp2->Next;
        delete(Temp2);
    }
}

template<class T>
int SinglyLL <T> ::  SearchFirstOcc(T iNo)
{
  int NodeCount = iCount;
  int iCnt = 0;
  int iOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iOcc = iCnt;
      break;
    }
    First = First->Next;
  }
  
  return iOcc;
}

template<class T>
int SinglyLL <T> ::  SearchLastOcc(T iNo)
{
  int NodeCount = iCount;
  int iCnt = 0;
  int iLastOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iLastOcc = iCnt;
    }
    First = First->Next;
  }
  
  return iLastOcc;
}

template<class T>
T SinglyLL <T> :: AdditionOfNumbers()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iSum = 0;
  
  for(iCnt = 1;iCnt <= NodeCount ;iCnt++)
  {
     iSum = iSum + First->Data;
     First = First->Next;
  }
  
  return iSum;
}

template<class T>
T SinglyLL <T> :: Maximum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T SinglyLL <T> :: Minimum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T SinglyLL <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T SinglyLL <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}

template<class T>
void SinglyLL <T> :: DisplayPerfect()
{
  int NodeCount = iCount;
  int iCnt = 0;
  int i = 0;
  
  cout<<"Perfect Numbers are : \n";
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
     T iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
  }
  
  cout<<"\n";
}

template<class T>
void SinglyLL <T> :: DisplayPrime()
{
   int NodeCount = iCount;
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   cout<<"Prime Numbers are : \n";
   
   for(iCnt = 1 ;iCnt <= NodeCount ; iCnt++)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
   }
 cout<<"\n";
}



template<class T>
void SinglyLL <T> :: Help()
{
   cout<<"---------------------------------------------------------------------\n";
   cout<<"        Functions Available in SinglyLL class                     \n";
   cout<<"---------------------------------------------------------------------\n";
   cout<<"InsertFirst(Data)     : Fuction to insert Data at First Position \n";
   cout<<"InsertLast(Data)      : Fuction to insert Data at Last Position \n";
   cout<<"InsertAtPos(Data,Pos) : Fuction to insert Data at Given Position \n\n";
   cout<<"DeleteFirst()         : Fuction to Delete Data of First Position \n";
   cout<<"DeleteLast()          : Fuction to Delete Data of Last Position \n";
   cout<<"DeleteAtPos(Pos)      : Fuction to Delete Data of given Position \n\n";
   
   cout<<"Display()             : Function to Display Data\n";
   cout<<"iCount Variable       : To count Number of Nodes\n\n";
   cout<<"SearchFirstOcc(Data)  : Function to obtain first Occurance of elements\n";
   cout<<"SearchLastOcc(Data)   : Function to obtain Last Occurance of elements\n";
   cout<<"AdditionOfNumbers()   : Function return Addtion of All elements\n";
   cout<<"Maximum()             : Function return Maximum Element\n";
   cout<<"Minimum()             : Function return Minimum Element\n";
   cout<<"SecondMaximum()       : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()       : Function return Second Minimum Element\n";
   cout<<"DisplayPerfect()      : Function to Display Perfect Numbers\n";
   cout<<"DisplayPrime()        : Function to Display Prime Numbers\n";
   cout<<"---------------------------------------------------------------------\n\n";
   
}

/////////////////////////////////////////////////////////////////////////////
/*
    Singly Circular linked List
    
    Containts :  InsertFirst Function
                 InsertLast  Function
                 InsertAtPos Function
               
                 DeleteFirst Function
                 DeleteLast  Function
                 DeleteAtPos Function
               
                 Display Function
                 Count   Function
                 Help    Function
                 
                 SearchFirstOcc    Function
                 SearchLastOcc     Function
                 AdditionOfNumbers Function
                 Maximum           Function
                 Minimum           Function
                 SecondMaximum     Function
                 SecondMinimum     Function
                 DisplayPerfect    Function
                 DisplayPrime      Function
*/
////////////////////////////////////////////////////////////////////////////


template <class T>
class SinglyCL
{
  public:
    struct SNode <T> * First;
    struct SNode <T> * Last;
    
    SinglyCL();
    
    void InsertFirst(T iNo);
    void InsertLast(T iNo);
    void InsertAtPos(T iNo,int iPos);
    
    void DeleteFirst();
    void DeleteLast();
    void DeleteAtPos(int iPos);
    
    void Display();
    int Count();
    void Help();
    
    int SearchFirstOcc(T iNo);
    int SearchLastOcc(T iNo);
    T AdditionOfNumbers();
    T Maximum();
    T Minimum();
    T SecondMaximum();
    T SecondMinimum();
    void DisplayPerfect();
    void DisplayPrime();
};

template <class T>
SinglyCL <T> :: SinglyCL() 
{
  First = NULL;
  Last = NULL;
}

template <class T>
void SinglyCL <T> :: InsertFirst(T iNo)
{
   struct SNode <T> *  Newn = new (struct SNode <T>);
   
   Newn->Data = iNo;
   Newn->Next = NULL;
   
   if((First == NULL) && (Last == NULL))
   {
     First = Last = Newn;
     (Last)->Next = First;
   }
   else
   {  
     Newn->Next = First;
     First = Newn;
     (Last)->Next = First; 
   }
}

template <class T>
void SinglyCL <T> :: InsertLast(T iNo)
{
  struct SNode <T> *  Newn = new (struct SNode <T>);
   
  Newn->Data = iNo;
  Newn->Next = NULL;
  
  if((First == NULL) && (Last == NULL))
  {
    First = Last = Newn;
    (Last)->Next = First;
  }
  else
  {
     (Last)->Next = Newn;
     Last = Newn;
     (Last)->Next = First;
  }
}

template <class T>
void SinglyCL <T> :: DeleteFirst()
{
   if((First == NULL) && (Last == NULL))
   {
      return;
   }
   else if (First->Next == First)
   {
      delete First;
      First = NULL;
      Last = NULL;
   }
   else
   {
      First = First->Next;
      delete Last->Next;
      Last->Next = First;
   }
}

template <class T>
void SinglyCL <T> :: DeleteLast()
{
  struct SNode <T> *  Temp = First;
  
   if((First == NULL) && (Last == NULL))
   {
      return;
   }
   else if (First->Next == First)
   {
      delete First;
      First = Last = NULL;
   }
   else
   {
      while(Temp->Next != Last)
      {
        Temp = Temp->Next;
      }
      
      delete Temp->Next;
      Last = Temp;
      Last->Next = First;
   }
}


template <class T>
void SinglyCL <T> ::  Display()
{
  struct SNode <T> *  Temp = First; 
  cout<<"Elements is Singly Circular Linkedlist are :"<<"\n";
  do
  {
    cout<<"| "<<Temp->Data<<" |->";
    Temp = Temp->Next;
  }
  while(Temp != Last->Next);
  cout<<"\n\n";
}


template <class T>
int SinglyCL <T> :: Count()
{
   struct SNode <T> * Temp = First;
   
    int iCnt = 0;
    do
    {
        iCnt++;
        Temp = Temp->Next;
    }while(Temp != Last->Next);
    return iCnt;
}

template <class T>
void SinglyCL <T> :: InsertAtPos(T iNo , int iPos)
{
  int NodeCount = Count();
  struct SNode <T> * Temp = NULL;
  struct SNode <T> * Newn = NULL;
  int iCnt = 0;
  
  if((iPos < 1) || (iPos > NodeCount+1))
  {
     cout<<"Invalid Position "<< "\n";
     return;
  }
  if(iPos == 1)
  {
    InsertFirst(iNo);
  }
  else if(iPos == NodeCount + 1)
  {
    InsertLast(iNo);
  }
  else
  {
     struct SNode <T> * Newn = new (struct SNode <T>);
     Temp = First;
     
     Newn->Data = iNo;
     Newn->Next = NULL;
     
     for(iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
     {
       Temp = Temp->Next;
     }
     
     Newn->Next = Temp->Next;
     Temp->Next = Newn;
     
  }
}

template <class T>
void SinglyCL <T> :: DeleteAtPos(int iPos)
{
  int NodeCount = Count();
  struct SNode <T> * Temp1 = First;
  struct SNode <T> * Temp2 = First;
  int iCnt = 0;
  
  if(iPos > NodeCount)
  {
     cout<<"Invalid Position "<< "\n";
     return;
  }
  if(iPos == 1)
  {
    DeleteFirst();
  }
  else if(iPos == NodeCount)
  {
    DeleteLast();
  }
  else
    {
        for(iCnt = 1; iCnt < iPos-1; iCnt++)
        {
            Temp1 = Temp1->Next;
        }   
        Temp2 = Temp1 ->Next;

        Temp1->Next = Temp2->Next;
        delete Temp2;
    }
}

template<class T>
int SinglyCL <T> ::  SearchFirstOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iOcc = iCnt;
      break;
    }
    First = First->Next;
  }
  
  return iOcc;
}

template<class T>
int SinglyCL <T> ::  SearchLastOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iLastOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iLastOcc = iCnt;
    }
    First = First->Next;
  }
  
  return iLastOcc;
}

template<class T>
T SinglyCL <T> :: AdditionOfNumbers()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iSum = 0;
  
  for(iCnt = 1;iCnt <= NodeCount ;iCnt++)
  {
     iSum = iSum + First->Data;
     First = First->Next;
  }
  
  return iSum;
}

template<class T>
T SinglyCL <T> :: Maximum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T SinglyCL <T> :: Minimum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T SinglyCL <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T SinglyCL <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}


template<class T>
void SinglyCL <T> :: DisplayPerfect()
{
  int NodeCount = Count();
  int iCnt = 0;
  int i = 0;
  
  cout<<"Perfect Numbers are : \n";
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
     int iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
  }
  
  cout<<"\n";
}

template<class T>
void SinglyCL <T> :: DisplayPrime()
{
   int NodeCount = Count();
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   cout<<"Prime Numbers are : \n";
   
   for(iCnt = 1 ;iCnt <= NodeCount ; iCnt++)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
   }
 cout<<"\n";
}


template<class T>
void SinglyCL <T> :: Help()
{
   cout<<"--------------------------------------------------------------------\n";
   cout<<"        Functions Available in SinglyCL class                     \n";
   cout<<"--------------------------------------------------------------------\n";
   cout<<"InsertFirst(Data)     : Fuction to insert Data at First Position \n";
   cout<<"InsertLast(Data)      : Fuction to insert Data at Last Position \n";
   cout<<"InsertAtPos(Data,Pos) : Fuction to insert Data at Given Position \n\n";
   cout<<"DeleteFirst()         : Fuction to Delete Data of First Position \n";
   cout<<"DeleteLast()          : Fuction to Delete Data of Last Position \n";
   cout<<"DeleteAtPos(Pos)      : Fuction to Delete Data of given Position \n\n";
   
   cout<<"Display()             : Function to Display Data\n";
   cout<<"Count()               : Function to Count Number of Nodes\n\n";
   cout<<"SearchFirstOcc(Data)  : Function return first Occurance of elements\n";
   cout<<"SearchLastOcc(Data)   : Function return Last Occurance of elements\n";
   cout<<"AdditionOfNumbers()   : Function return Addtion of All elements\n";
   cout<<"Maximum()             : Function return Maximum Element\n";
   cout<<"Minimum()             : Fumction return Minimum Element\n";
   cout<<"SecondMaximum()       : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()       : Function return Second Minimum Element\n";
   cout<<"DisplayPerfect()      : Function to Display Perfect Numbers\n";
   cout<<"DisplayPrime()        : Function to Display Prime Numbers\n";
   cout<<"--------------------------------------------------------------------\n\n";
   
}


////////////////////////////////////////////////////////////////////////
//                                                                    //
//  comman structure for Doubly linear linkedlist and Doubly circular //  
//                                                                    //
////////////////////////////////////////////////////////////////////////

template<class T>
struct Node 
{
  struct Node * Prev;
  T Data;
  struct Node * Next;
};


////////////////////////////////////////////////////////////////////////////
/*
     Doubly Linear linkedList
    
     Containts :  InsertFirst Function
                  InsertLast  Function
                  InsertAtPos Function
               
                  DeleteFirst Function
                  DeleteLast  Function
                  DeleteAtPos Function
               
                  Display Function
                  Count   Function
                  Help    Function
                  
                  SearchFirstOcc    Function
                  SearchLastOcc     Function
                  AdditionOfNumbers Function
                  Maximum           Function
                  Minimum           Function
                  SecondMaximum     Function
                  SecondMinimum     Function
                  DisplayPerfect    Function
                  DisplayPrime      Function
*/
////////////////////////////////////////////////////////////////////////////

template<class T>
class DoublyLL
{
  public:
    struct Node <T> * First;
    
    DoublyLL();
    
    void InsertFirst(T iNo);
    void InsertLast(T iNo);
    void InsertAtPos(T iNo ,int iPos);
    
    void DeleteFirst();
    void DeleteLast();
    void DeleteAtPos(int iPos);
    
    void Display();
    int Count();
    void Help();
    
    int SearchFirstOcc(T iNo);
    int SearchLastOcc(T iNo);
    T AdditionOfNumbers(); 
    T Maximum();
    T Minimum(); 
    T SecondMaximum();
    T SecondMinimum();
    void DisplayPerfect();
    void DisplayPrime();
};

template<class T>
DoublyLL <T> :: DoublyLL()     
{
   First = NULL;
}

template<class T>
void DoublyLL <T> :: InsertFirst(T iNo) 
{
   struct Node <T> * Newn = new (struct Node <T>);
   struct Node <T> * Temp = First;
   
   Newn->Prev = NULL;
   Newn->Data = iNo;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
     First = Newn;
   }
   else
   {
     Newn->Next = First;
     Temp->Prev = Newn;
     First = Newn;
   }
   
}

template<class T>
void DoublyLL <T> :: InsertLast(T iNo)  
{
   struct Node <T> * Newn = new (struct Node <T>);
   struct Node <T> * Temp = First;
   
   Newn->Prev = NULL;
   Newn->Data = iNo;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
     First = Newn;
   }
   else
   {
     while(Temp->Next != NULL)
     {
       Temp = Temp->Next;
     }  
     Temp->Next = Newn;
     Newn->Prev = Temp;
   }
   
}

template<class T>
void DoublyLL <T> :: DeleteFirst()    
{
  if(First == NULL)
  {
    cout<<"Unable To Delete as LinkedList is Empty...\n";
    return;
  }
  else if(First->Next == NULL)
  {
     delete(First);
     First = NULL;
  }
  else
  {
     struct Node <T> * Temp = First;
     
     First = First->Next;
     Temp->Next->Prev = NULL;
     Temp->Next = NULL;
     delete(Temp);
  }
}

template<class T>
void DoublyLL <T> :: DeleteLast() 
{
  if(First == NULL)
  {
    cout<<"Unable To Delete as LinkedList is Empty...\n";
    return;
  }
  else if(First->Next == NULL)
  {
     delete(First);
     First = NULL;
  }
  else
  {
     struct Node <T> * Temp1 = First;
     struct Node <T> * Temp2 = First->Next;
     
     while(Temp2->Next != NULL)
     {
         Temp1 = Temp1->Next;
         Temp2 = Temp2->Next;
     }
     
     Temp1->Next = NULL;
     Temp2->Prev = NULL;
     delete(Temp2);
  }
}

template<class T>
void DoublyLL <T> :: Display()  
{
  struct Node <T> * Temp = First;
  cout<<"Elements in Doubly Linear LinkedList are : "<<"\n";
  
  while(Temp != NULL)
  {
    cout<<"| "<<Temp->Data<<" |<->";
    Temp = Temp->Next;
  }
  cout<<"NULL\n\n";
}

template<class T>
int DoublyLL <T> :: Count()
{
   struct Node <T> * Temp = First;
   int iCnt = 0;
   
   while(Temp != NULL)
   {
     iCnt++;
     Temp = Temp->Next;
   }
   
   return iCnt; 
}

template<class T>
void DoublyLL <T> :: InsertAtPos(T iNo , int iPos)  
{
  int NodeCount = Count();
  
  struct Node <T> * Newn = new (struct Node <T>);
  struct Node <T> * Temp = First;
  
  Newn->Prev = NULL;
  Newn->Data = iNo;
  Newn->Next = NULL;
  
  if((iPos < 1) || (iPos > NodeCount+1)) 
  {
    cout<<"Invalid Position\n";
    return;
  }
  
  if(iPos == 1)
  {
    InsertFirst(iNo);
  }
  else if(iPos == NodeCount+1)
  {
    InsertLast(iNo);
  }
  else
  {
    for(int iCnt = 1; iCnt < iPos-1; iCnt++)
    {
      Temp = Temp->Next;
    }
    
    Newn->Next = Temp->Next;
    Temp->Next->Prev = Newn;
    Newn->Prev = Temp;
    Temp->Next = Newn;
  }
} 

template<class T>
void DoublyLL <T> :: DeleteAtPos(int iPos)
{
  int NodeCount = Count();
  
  if((iPos < 1)|| (iPos > NodeCount))
  {
    cout<<"Invalid Position\n";
    return;
  }
  
  if(iPos == 1)
  {
    DeleteFirst();
  }
  else if(iPos == NodeCount)
  {
    DeleteLast();
  }
  else
  {
     struct Node <T> * Temp1 = First;
     struct Node <T> * Temp2 = First->Next;
     
     for(int iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
     {
        Temp1 = Temp1->Next;
        Temp2 = Temp2->Next;
     }
     
     Temp1->Next = Temp2->Next;
     Temp2->Prev = NULL;
     Temp2->Next = NULL;
     Temp1->Next->Prev = Temp1;
     delete(Temp2);
     
  }
}

template<class T>
int DoublyLL <T> ::  SearchFirstOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iOcc = iCnt;
      break;
    }
    First = First->Next;
  }
  
  return iOcc;
}

template<class T>
int DoublyLL <T> ::  SearchLastOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iLastOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iLastOcc = iCnt;
    }
    First = First->Next;
  }
  
  return iLastOcc;
}

template<class T>
T DoublyLL <T> :: AdditionOfNumbers()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iSum = 0;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
     iSum = iSum + First->Data;
     First = First->Next;
  }
  
  return iSum;
}

template<class T>
T DoublyLL <T> :: Maximum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T DoublyLL <T> :: Minimum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T DoublyLL <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T DoublyLL <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}



template<class T>
void DoublyLL <T> :: DisplayPerfect()
{
  int NodeCount = Count();
  int iCnt = 0;
  int i = 0;
  
  cout<<"Perfect Numbers are : \n";
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
     int iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
  }
  
  cout<<"\n";
}

template<class T>
void DoublyLL <T> :: DisplayPrime()
{
   int NodeCount = Count();
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   cout<<"Prime Numbers are : \n";
   
   for(iCnt = 1 ;iCnt <= NodeCount ; iCnt++)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
   }
 cout<<"\n";
}


template<class T>
void DoublyLL <T> :: Help()
{
   cout<<"--------------------------------------------------------------------\n";
   cout<<"        Functions Available in DoublyLL class                     \n";
   cout<<"--------------------------------------------------------------------\n";
   cout<<"InsertFirst(Data)     : Fuction to insert Data at First Position \n";
   cout<<"InsertLast(Data)      : Fuction to insert Data at Last Position \n";
   cout<<"InsertAtPos(Data,Pos) : Fuction to insert Data at Given Position \n\n";
   cout<<"DeleteFirst()         : Fuction to Delete Data of First Position \n";
   cout<<"DeleteLast()          : Fuction to Delete Data of Last Position \n";
   cout<<"DeleteAtPos(Pos)      : Fuction to Delete Data of given Position \n\n";
   
   cout<<"Display()             : Function to Display Data\n";
   cout<<"Count()               : Function to count Number of Nodes\n\n";
   cout<<"SearchFirstOcc(Data)  : Function to obtain first Occurance of elements\n";
   cout<<"SearchLastOcc(Data)   : Function to obtain Last Occurance of elements\n";
   cout<<"AdditionOfNumbers()   : Function return Addtion of All elements\n";
   cout<<"Maximum()             : Function return Maximum Element\n";
   cout<<"Minimum()             : Fumction return Minimum Element\n";
   cout<<"SecondMaximum()       : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()       : Function return Second Minimum Element\n";
   cout<<"DisplayPerfect()      : Function to Display Perfect Number\n";
   cout<<"DisplayPrime()        : Function to Displat Prime Number\n";
   cout<<"--------------------------------------------------------------------\n\n";
   
}

//////////////////////////////////////////////////////////////////////////
/*
     Doubly Circular Linked List
    
     Containts :  InsertFirst Function
                  InsertLast  Function
                  InsertAtPos Function
               
                  DeleteFirst Function
                  DeleteLast  Function
                  DeleteAtPos Function
               
                  Display Function
                  Count   Function
                  Help    Function
                  
                 SearchFirstOcc    Function
                 SearchLastOcc     Function
                 AdditionOfNumbers Function
                 Maximum           Function
                 Minimum           Function
                 SecondMaximum     Function
                 SecondMinimum     Function
                 DisplayPerfect    Function
                 DisplayPrime      Function
*/
//////////////////////////////////////////////////////////////////////////

template<class T>
class DoublyCL           
{
  public:
    struct Node <T> * First ;
    struct Node <T> * Last;
    
    DoublyCL();
    
    void InsertFirst(T iNo);
    void InsertLast(T iNo);
    void InsertAtPos(T iNo , int iPos);
    
    void DeleteFirst();
    void DeleteLast();
    void DeleteAtPos(int iPos);
    
    void Display();
    int Count();
    void Help();
    
    int SearchFirstOcc(T iNo);
    int SearchLastOcc(T iNo);
    T AdditionOfNumbers();
    T Maximum();
    T Minimum();
    T SecondMaximum();
    T SecondMinimum();
    void DisplayPerfect();
    void DisplayPrime();
};

template<class T>
DoublyCL <T> :: DoublyCL()
{
  First = NULL;
  Last = NULL;
}

template<class T>
void DoublyCL <T> :: InsertFirst(T iNo)
{
  struct Node <T> * Newn = new (struct Node <T>);
  
  Newn->Prev = NULL;
  Newn->Data = iNo;
  Newn->Next = NULL;
  
  if((First == NULL) && (Last == NULL))
  {
     First = Newn;
     Last = Newn;
     Last->Next = First;
     First->Prev = Last;
  }
  else
  {
     Newn->Next = First;
     First->Prev = Newn;
     First = Newn;
     Last->Next = First;
     First->Prev = Last;
  }
}

template<class T>
void DoublyCL <T> :: InsertLast(T iNo)  
{
  struct Node <T> * Newn = new (struct Node <T>);
  
  Newn->Prev = NULL;
  Newn->Data = iNo;
  Newn->Next = NULL;
  
  if((First == NULL) && (Last == NULL))
  {
     First = Newn;
     Last = Newn;
     Last->Next = First;
     First->Prev = Last;
  }
  else
  {
     Last->Next = Newn;
     Newn->Prev = Last;
     Last = Newn;
     Last->Next = First;
     First->Prev = Last;
  }
}

template<class T>
void DoublyCL <T> :: DeleteFirst()
{
  if((First == NULL) && (Last == NULL))
  {
     cout<<"LinkedList is empty ...\n";
  }
  else if (First->Next == Last)
  {
     delete(First);
     First = NULL;
     Last = NULL;
  }
  else
  {
     First = First->Next;
     delete(First->Prev);
     First->Prev = Last;
     Last->Next = First;
  }
}

template<class T>
void DoublyCL <T> :: DeleteLast() 
{
  if((First == NULL) && (Last == NULL))
  {
     cout<<"LinkedList is empty ...\n";
  }
  else if (First->Next == Last)
  {
     delete(First);
     First = NULL;
     Last = NULL;
  }
  else
  {
     Last = Last->Prev;
     delete(First->Prev);
     Last->Next = First;
     First->Prev = Last;
  }
}

template<class T>
void DoublyCL <T> :: Display() 
{
  cout<<"Elements in Doubly Circular LinkedList are : "<<"\n";
  
  do
  {
    cout<<"| "<<First->Data<<" |<=>";
    First = First->Next;
  }
  while(First != Last->Next);
  cout<<"\n";
}

template<class T>
int DoublyCL <T> :: Count() 
{
  int iCnt = 0;
  
  do
  {
    iCnt++;
    First = First->Next;
  }
  while(First != Last->Next);
  
  return iCnt;
}

template<class T>
void DoublyCL <T> :: InsertAtPos(T iNo , int iPos) 
{
  int NodeCount = Count();
  struct Node <T> * Temp = NULL;
  
  if((iPos < 1 ) || (iPos > NodeCount+1)) 
  {
     cout<<"Invalid Position...."<<"\n";
     return;
  }
  
  if(iPos == 1)
  {
     InsertFirst(iNo);
  }
  else if (iPos == NodeCount+1)
  {
     InsertLast(iNo);
  }
  else
  {
     struct Node <T> * Newn = new (struct Node <T>);
     
     Newn->Prev = NULL;
     Newn->Data = iNo;
     Newn->Next = NULL;
     
     Temp = First;
     
     for(int iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
     { 
        Temp = Temp->Next; 
     }
     
     Newn->Next = Temp->Next;
     Temp->Next->Prev = Newn;
     Temp->Next = Newn;
     Newn->Prev = Temp;
     
  }
}

template<class T>
void DoublyCL <T> :: DeleteAtPos(int iPos) 
{
   int NodeCount = Count();
   struct Node <T> * Temp = NULL;
   
   if((iPos < 1) || (iPos > NodeCount))
   {
       cout<<"Invalid Position..."<<"\n";
       return;
   }
   
   if(iPos == 1)
   {
      DeleteFirst();
   }
   else if(iPos == NodeCount)
   {
      DeleteLast();
   }
   else
   {
      Temp = First;
      
      for(int iCnt = 1 ; iCnt < iPos-1 ; iCnt++)
      { 
         Temp = Temp->Next;
      } 
      
      Temp->Next = Temp->Next->Next;
      delete(Temp->Next->Prev);
      Temp->Next->Prev = Temp;
   }
}

template<class T>
int DoublyCL <T> ::  SearchFirstOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iOcc = iCnt;
      break;
    }
    First = First->Next;
  }
  
  return iOcc;
}

template<class T>
int DoublyCL <T> ::  SearchLastOcc(T iNo)
{
  int NodeCount = Count();
  int iCnt = 0;
  int iLastOcc = -1;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data == iNo)
    {
      iLastOcc = iCnt;
    }
    First = First->Next;
  }
  
  return iLastOcc;
}

template<class T>
T DoublyCL <T> :: AdditionOfNumbers()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iSum = 0;
  
  for(iCnt = 1;iCnt <= NodeCount ;iCnt++)
  {
     iSum = iSum + First->Data;
     First = First->Next;
  }
  
  return iSum;
}

template<class T>
T DoublyCL <T> :: Maximum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T DoublyCL <T> :: Minimum()
{
  int NodeCount = Count();
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T DoublyCL <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T DoublyCL <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}


template<class T>
void DoublyCL <T> :: DisplayPerfect()
{
  int NodeCount = Count();
  int iCnt = 0;
  int i = 0;
  
  cout<<"Perfect Numbers are : \n";
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
     int iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
  }
  
  cout<<"\n";
}

template<class T>
void DoublyCL <T> :: DisplayPrime()
{
   int NodeCount = Count();
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   cout<<"Prime Numbers are : \n";
   
   for(iCnt = 1 ;iCnt <= NodeCount ; iCnt++)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
   }
 cout<<"\n";
}


template<class T>
void DoublyCL <T> :: Help()
{
   cout<<"---------------------------------------------------------------------\n";
   cout<<"        Functions Available in DoublyCL class                     \n";
   cout<<"---------------------------------------------------------------------\n";
   cout<<"InsertFirst(Data)     : Fuction to insert Data at First Position \n";
   cout<<"InsertLast(Data)      : Fuction to insert Data at Last Position \n";
   cout<<"InsertAtPos(Data,Pos) : Fuction to insert Data at Given Position \n\n";
   cout<<"DeleteFirst()         : Fuction to Delete Data of First Position \n";
   cout<<"DeleteLast()          : Fuction to Delete Data of Last Position \n";
   cout<<"DeleteAtPos(Pos)      : Fuction to Delete Data of given Position \n\n";
   
   cout<<"Display()             : Function to Display Data\n";
   cout<<"Count()               : Function to count Number of Nodes\n\n";
   cout<<"SearchFirstOcc(Data)  : Function to obtain first Occurance of elements\n";
   cout<<"SearchLastOcc(Data)   : Function to obtain Last Occurance of elements\n";
   cout<<"AdditionOfNumbers()   : Function return Addtion of All elements\n";
   cout<<"Maximum()             : Function return Maximum Element\n";
   cout<<"Minimum()             : Fumction return Minimum Element\n";
   cout<<"SecondMaximum()       : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()       : Function return Second Minimum Element\n";
   cout<<"DisplayPerfect()      : Function to Display perfect Number\n";
   cout<<"DisplayPrime()        : Function to Displat Prime Number\n";
   cout<<"---------------------------------------------------------------------\n\n";
   
}

///////////////////////////////////////////////////////////////////////////
/*
     Stack
     
     containts : Push function
                 Pop function
                 
                 Display function
                 Help  Function
               
                 Maximum           Function
                 Minimum           Function
                 SecondMaximum     Function
                 SecondMinimum     Function
                 DisplayPerfect    Function
                 DisplayPrime      Function
*/
///////////////////////////////////////////////////////////////////////////

template<class T>
class Stack
{
   public :
     struct SNode <T> * First;
     int iCount;
     
     Stack();
     
     void Push(T No);
     void Pop(); 
     
     void Display(); 
     void Help(); 
     
     T Maximum();
     T Minimum();
     T SecondMaximum();
     T SecondMinimum();
     
     void DisplayPerfect();
     void DisplayPrime();
};

template<class T>
Stack <T> :: Stack()
{
   First == NULL;
   iCount = 0;
}

template<class T>
void Stack <T> :: Push(T No) 
{
   struct SNode <T> * Newn = new (struct SNode <T>);
   Newn->Data = No;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
      First = Newn;
   }
   else
   {
      Newn->Next = First;
      First = Newn;
   }
   iCount++;
}

template<class T>
void Stack <T> :: Pop()
{
   if(First == NULL)
   {
      cout<<"Stack is Empty\n";
   }
   else
   {
      struct SNode <T> * Temp = First;
        
      First = First->Next;
      cout<<"Poped element is : "<<Temp->Data<<"\n";
      delete(Temp);
   }
}

template<class T>
void Stack <T> :: Display()
{
   struct SNode <T> * Temp = First;
   
   if(Temp == NULL)
   {
      cout<<"Stack is Empty \n";
   }
   else
   {
      cout<<"Elements in stack are : \n";
   }
   
   
   while(Temp != NULL)
   {
      cout<<"| "<<Temp->Data<<" |"<<"\n";
      Temp = Temp->Next;
   }
}

template<class T>
T Stack <T> :: Maximum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T Stack <T> :: Minimum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T Stack <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T Stack <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}

template<class T>
void Stack <T> :: DisplayPerfect()
{
  int iCnt = 0;
  int i = 0;
  
  struct SNode <T> * Temp = First;
  
  cout<<"Perfect Numbers are : \n";
   
   while(Temp != NULL)
   {
     int iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
     Temp = Temp->Next;
  }
  
  cout<<"\n";
}

template<class T>
void Stack <T> :: DisplayPrime()
{
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   struct SNode <T> * Temp = First;
   
   cout<<"Prime Numbers are : \n";
   
   while(Temp != NULL)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
       Temp = Temp->Next;
   }
 cout<<"\n";
}


template<class T>
void Stack <T> :: Help()
{
   cout<<"-------------------------------------------------------------\n";
   cout<<"        Functions Available in Stack class           \n";
   cout<<"-------------------------------------------------------------\n";
   cout<<"Push(Data)          : Function to insert Data into Stack  \n";
   cout<<"Pop()               : Function to Delete Data from Stack \n\n";
   
   cout<<"Display()           : Function to Display Data from Stack  \n"; 
   cout<<"Maximum()           : Function to return Maximum element\n";
   cout<<"Minimum()           : Function to return Minimum element\n";  
   cout<<"SecondMaximum()     : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()     : Function return Second Minimum Element\n";
   cout<<"DisplayPerfect()    : Function to Display perfect Number\n";
   cout<<"DisplayPrime()      : Function to Displat Prime Number\n";       
   cout<<"-------------------------------------------------------------\n\n";
   
}

///////////////////////////////////////////////////////////////////////////
/*
     Queue
     
     containts : Euqueue function
                 Dequeue function
                 
                 Display function
                 Help function
                 
                 Maximum           Function
                 Minimum           Function
                 SecondMaximum     Function
                 SecondMinimum     Function
                 DisplayPerfect    Function
                 DisplayPrime      Function
*/
///////////////////////////////////////////////////////////////////////////

template<class T>
class Queue
{
  public :
    struct SNode <T> * First;
    int iCount;
    
    Queue();
    
    void Enqueue(T Data);
    void Dequeue();
    
    void Display();
    void Help();
    
    T Maximum();
    T Minimum();
    T SecondMaximum();
    T SecondMinimum();
    
    void DisplayPerfect();
    void DisplayPrime();
};

template<class T>
Queue <T> :: Queue()
{
   First = NULL;
   iCount = 0;
}

template<class T>
void Queue <T> :: Enqueue(T No)
{
   struct SNode <T> * Newn = new (struct SNode <T>);
   
   Newn->Data = No;
   Newn->Next = NULL;
   
   if(First == NULL)
   {
     First = Newn;
   }
   else
   {
      struct SNode <T> * Temp = First;
      
      while(Temp->Next != NULL)
      {
         Temp = Temp->Next;
      }
      
      Temp->Next = Newn;
   }
   
   iCount++;
}

template<class T>
void Queue <T> :: Dequeue()
{
   if(First == NULL)
   {  
      cout<<"Queue is empty\n";
   }
   else
   {
      struct SNode <T> * Temp = First;
      
      First = First->Next;
      cout<<"Dequeued elements is : "<<First->Data<<"\n";
      delete(Temp);
   }
}

template<class T>
void Queue <T> :: Display()
{
   struct SNode <T> * Temp = First;
   
   if(Temp == NULL)
   {
      cout<<"Queue is Empty\n";
      return;
   }
   else
   {
      cout<<"Elements in Queue are : \n";
   }
   
   while(Temp != NULL)
   {
     cout<<" | "<<Temp->Data;
     Temp = Temp->Next;
   }
   
   cout<<"\n";
}

template<class T>
T Queue <T> :: Maximum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMax = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data > iMax)
    {
      iMax = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMax;
}

template<class T>
T Queue <T> :: Minimum()
{
  int NodeCount = iCount;
  int iCnt = 0;
  T iMin = First->Data;
  
  for(iCnt = 1 ; iCnt <= NodeCount ; iCnt++)
  {
    if(First->Data < iMin)
    {
      iMin = First->Data;
    }
    
    First = First->Next;
  }
  
  return iMin;
}

template<class T>
T Queue <T> :: SecondMaximum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
 
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data < Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
}

template<class T>
T Queue <T> :: SecondMinimum()
{
  struct SNode <T> * Temp = First->Next;
  struct SNode <T> * Temp1 = First;
  int iCnt = 0;
  
     while(First != NULL)
     {
        Temp = First->Next;
        
         while(Temp != NULL)
         {
           if(First->Data > Temp->Data)
           {
              iCnt = First->Data;
              First->Data = Temp->Data;
              Temp->Data = iCnt;
           } 
           Temp = Temp->Next;
         }  
         
         First = First->Next;
     }
     
     return Temp1->Next->Data;
  
}

template<class T>
void Queue <T> :: DisplayPerfect()
{
  int iCnt = 0;
  int i = 0;
  
  struct SNode <T> * Temp = First;
  
  cout<<"Perfect Numbers are : \n";
   
   while(Temp != NULL)
   {
     int iSum = 0;
     
     for(i = 1 ; i <= (First->Data)/2 ; i++)
     {
        if(First->Data % i == 0)
        {
          iSum = iSum + i;
        }       
     }
     
     if(First->Data == iSum)
     {
        cout<<"  "<<iSum<<"  ";
     }
     
     First = First->Next;
     Temp = Temp->Next;
  }
  
  cout<<"\n";
}

template<class T>
void Queue <T> :: DisplayPrime()
{
   int iCnt = 0;
   int i = 0;
   int iCount = 0;
   
   struct SNode <T> * Temp = First;
   
   cout<<"Prime Numbers are : \n";
   
   while(Temp != NULL)
   {
     iCount = 0;
     
       for(i = 2; i <= (First->Data)/2 ; i++)
       {
           if(First->Data % i == 0)
           {
              iCount++;
           }           
       }
      
       if(iCount == 0)
       {
          cout<<"  "<<First->Data<<"  ";
       }
       
       First = First->Next;
       Temp = Temp->Next;
   }
 cout<<"\n";
}


template<class T>
void Queue <T> :: Help()
{
   cout<<"-----------------------------------------------------------\n";
   cout<<"        Functions Available in Queue class           \n";
   cout<<"-----------------------------------------------------------\n";
   cout<<"Enqueue(Data)      : Function to insert Data into Queue  \n";
   cout<<"Dequeue()          : Function to Delete Data from Queue \n\n";
   
   cout<<"Display()          : Function to Display Data from Queue  \n";  
   cout<<"Maximum()          : Function to return Maximum element\n";
   cout<<"Minimum()          : Function to return Minimum element\n"; 
   cout<<"SecondMaximum()    : Function return Second Maximum Element\n";
   cout<<"SecondMinimum()    : Function return Second Minimum Element\n"; 
   cout<<"DisplayPerfect()   : Function to Display perfect Number\n";
   cout<<"DisplayPrime()     : Function to Display Prime Number\n";       
   cout<<"------------------------------------------------------------\n\n";
   
}
